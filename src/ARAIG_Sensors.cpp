#include "ARAIG_Sensors.h"

namespace a1
{	
	ARAIG_Sensors::ARAIG_Sensors(std::string s, std::string t)
	{

		std::ifstream file1(s); //create ifstream objects to construct files
		std::ifstream file2(t);
		readStims(file1); //call functions to read files
		readTasks(file2);

	}

	ARAIG_Sensors::~ARAIG_Sensors()
	{
		delete [] stimList; //may have potential memory leak --> ask Elliot
		stimList = nullptr;
		delete [] taskList;
		taskList = nullptr;
	}

	void ARAIG_Sensors::readStims(std::ifstream& in)
	{
		countStims = 0;
		std::string tmp;
		unsigned short i = 0;
		
		if (in && in.is_open())
		{
			while (!in.eof()) //loop through the file and count how many objects must be created
			{
				std::getline(in, tmp);
				countStims++; //incrememt by 1
			}

			countStims--; //reads EOF, subtract 1

			stimList = new Stimulation*[countStims]; //allocate memory based on how many objects are created
			//using Stimulation** because we must point to Stimulation, which then points to a derived class

			in.clear(); //clear EOF
			in.seekg(0, in.beg); //set cursor to beginning of file

			while (!in.eof())
			{
				std::string t_;
				unsigned short inten;
				unsigned short dur_;

				std::getline(in, tmp, '\n');

				if (tmp[0] == 's' || tmp[0] == 'S')
				{
					std::string sName;
					sLoc l_;
					unsigned short freq_;

					unsigned short pos1 = tmp.find(',', 0);
					unsigned short pos2 = tmp.find(',', (pos1 + 1));
					unsigned short pos3 = tmp.find(',', (pos2 + 1));
					unsigned short pos4 = tmp.find(',', (pos3 + 1));
					unsigned short pos5 = tmp.find(',', (pos4 + 1));

					t_ = tmp.substr(0, pos1++);
					sName = tmp.substr((pos1), ((pos2++) - pos1));

					if (tmp.substr(pos2, (pos3 - pos2)) == "abs")
					{
						l_ = abs;
					}
					else if (tmp.substr(pos2, (pos3 - pos2)) == "front")
					{
						l_ = front;
					}
					else if (tmp.substr(pos2, (pos3 - pos2)) == "back")
					{
						l_ = back;
					}
					else if (tmp.substr(pos2, (pos3 - pos2)) == "traps")
					{
						l_ = traps;
					}
					else
					{
						throw std::string("The stimulation location is invalid. Please check the file.");
					}

					inten = stoi(tmp.substr(++pos3, (pos4 - pos3))); //use string to int to turn a parsed string into an integral number
					freq_ = stoi(tmp.substr(++pos4, (pos5 - pos4)));
					dur_ = stoi(tmp.substr(++pos5));

					stimList[i] = new Stims(t_, sName, l_, inten, freq_, dur_); //set the location at i to a new Stims object
					i++; //increment by 1, variable is in local scope of the function, not the loop
				}
				else if (tmp[0] == 'e' || tmp[0] == 'E')
				{
					std::string eName;

					unsigned short pos1 = tmp.find(',', 0);
					unsigned short pos2 = tmp.find(',', pos1 + 1);
					unsigned short pos3 = tmp.find(',', pos2 + 1);

					t_ = tmp.substr(0, pos1);
					eName = tmp.substr(++pos1, (pos2 - pos1));
					inten = stoi(tmp.substr(++pos2, (pos3 - pos2)));
					dur_ = stoi(tmp.substr(++pos3));

					stimList[i] = new Exoskeleton(t_, eName, inten, dur_);
					i++; //increment by 1, see above comment
				}
			}
		}

		in.close();
	}

	void ARAIG_Sensors::readTasks(std::ifstream& in)
	{
		countTasks = 0;
		std::string tmp;
		unsigned short i = 0;

		if (in && in.is_open())
		{
			while (!in.eof())
			{
				std::getline(in, tmp); //grab the line
				
				if (tmp.find("TASK") != std::string::npos)
				{
					countTasks++;
				}
			}

			taskList = new Task[countTasks]; //allocate memory for the size of the array

			in.clear();
			in.seekg(0, in.beg);

			while (std::getline(in, tmp))
			{
				unsigned short pos = tmp.find("TASK,"); //use find to locate the word Task

				if (pos == 0) //only locates the first letter, which is at location 0
				{
					for (unsigned short x = 0; x < 5; x++) //loop until 5 to erase TASK, now we have the name
					{
						tmp.erase(tmp.begin() + pos);
					}
					
					taskList[i++] = Task(tmp);
				}
				else
				{
					for (unsigned short x = 0; x < countStims; x++)
					{
						if (stimList[x]->getStim() == tmp)
						{
							taskList[i - 1] += stimList[x];
						}
					}
				}
				
			}

			in.close();
		}

	}

	void ARAIG_Sensors::dumpStims(std::ostream& os) const
	{
		for (unsigned short i = 0; i < countStims; i++)
		{
			stimList[i]->display(os); //dump all Stimulation objects that were allocated in memory as per spec
		}
	}

	void ARAIG_Sensors::dumpTasks(std::ostream& os) const
	{
		for (unsigned short i = 0; i < countTasks; i++)
		{
			taskList[i].dump(os); //dump all tasks to ensure that the array is storing the information
		}
	}

	Task& ARAIG_Sensors::getTask(std::string tmp) const
	{	
		unsigned short i = 0;
		for (; i < countTasks; i++)
		{
			if (taskList[i].getTaskName() == tmp)
			{
				return taskList[i];
				break;
			}
		}
		throw std::string("The Task does not exist.");
	}

}