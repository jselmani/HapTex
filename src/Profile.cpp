#include "Profile.h"

namespace a1
{
	Profile::Profile(const char* in, std::ofstream& os, ARAIG_Sensors& araig)
	{
		std::ifstream file(in, std::ios::in);
		ofs = &os;
		if (file.fail())
		{
			throw std::string("Could not open the profile configuration.  Please check your file for errors.");
		}
		else
		{
			std::getline(file, sFName, ',');
			std::getline(file, sLName, ',');
			file >> sNum;
			file.ignore();
			std::getline(file, iFName, ',');
			std::getline(file, iLName, ',');
			file >> iNum;
			file.ignore();
			file >> calibrate.max;
			file.ignore();
			file >> calibrate.min;
			file.ignore();

			while (!file.eof())
			{
				std::string tmp;
				std::getline(file, tmp);
				try{
					ToRun.push_back(new Task(araig.getTask(tmp)));
				}
				catch (std::string msg)
				{
					std::cerr << msg << std::endl;
				}
			}
		}
		file.close();
	}

	Profile::~Profile()
	{
		ToRun.~deque();
		Completed.~vector();

		for (unsigned short i = 0; i < ToRun.size(); i++)
		{
			ToRun[i] = nullptr;
		}
		for (unsigned short i = 0; i < Completed.size(); i++)
		{
			Completed[i] = nullptr;
		}
	}

	void Profile::displayToRun(std::ostream& os) const
	{
		std::cout << "Tasks To Run" << std::endl;
		std::cout << "============" << std::endl << std::endl;
		std::cout << "Student Name: " << sFName << " " << sLName << std::endl;
		std::cout << "Student ID  : " << sNum << std::endl;
		os << "Tasks To Run" << std::endl;
		os << "============" << std::endl << std::endl;
		os << "Student Name: " << sFName << " " << sLName << std::endl;
		os << "Student ID  : " << sNum << std::endl;

		for (unsigned short i = 0; i < ToRun.size(); i++)
		{
			ToRun[i]->dump(os);
		}
	}

	void Profile::displayCompleted(std::ostream& os) const
	{
		std::cout << "Completed Tasks" << std::endl;
		std::cout << "===============" << std::endl << std::endl;
		std::cout << "Student Name: " << sFName << " " << sLName << std::endl;
		std::cout << "Student ID  : " << sNum << std::endl;
		std::cout << "MAX = " << calibrate.max << std::endl;
		std::cout << "MIN = " << calibrate.min << std::endl;
		os << "Completed Tasks" << std::endl;
		os << "===============" << std::endl << std::endl;
		os << "Student Name: " << sFName << " " << sLName << std::endl;
		os << "Student ID  : " << sNum << std::endl;
		os << "MAX = " << calibrate.max << std::endl;
		os << "MIN = " << calibrate.min << std::endl;

		for (int i = 0; i < Completed.size(); i++)
		{
			Completed[i]->dump(os);
		}
		std::cout << std::endl;
		os << std::endl;
	}

	void Profile::displayNext(std::ostream& os) const
	{
		os << "Next Task" << std::endl;
		os << "=========" << std::endl << std::endl;
		std::cout << "Next Task" << std::endl;
		std::cout << "=========" << std::endl << std::endl;
		ToRun[0]->execute(os);
	}

	void Profile::displayPrev(std::ostream& os) const
	{
		os << "Previous Task" << std::endl;
		os << "=============" << std::endl;
		std::cout << "Previous Task" << std::endl;
		std::cout << "=============" << std::endl;
		Completed.back()->dump(os);
		std::cout << std::endl;
		os << std::endl;
	}

	void Profile::flightInfo() const
	{
		std::cout << "Student Name: " << sFName << " " << sLName << std::endl;
		std::cout << "Student ID  : " << sNum << std::endl;
		std::cout << "Instructor Name: " << iFName << " " << iLName << std::endl;
		std::cout << "Instructor ID  : " << iNum << std::endl;
		std::cout << "Available Tasks:" << std::endl << std::endl;

		for (auto i = 0; i < ToRun.size(); i++)
		{
			std::cout << ToRun[i]->getTaskName() << std::endl;
		}

		std::cout << std::endl;
		std::cout << "Calibrating ARAIG to a maximum intensity of " << calibrate.max << std::endl;
		std::cout << "and a minimum intensity of " << calibrate.min << std::endl << std::endl;
		char enter;
		std::cout << "Press any LETTER to continue..." << std::endl;
		std::cin >> enter;
		std::cout << std::endl << std::endl;
	}

	void Profile::flightPlan()
	{
		unsigned short option = -1;
		unsigned short x = 1;
		unsigned short count = 0;
		do{
			std::cout << std::endl;
			std::cout << "  Choose how to proceed  " << std::endl;
			std::cout << "=========================" << std::endl;
			std::cout << "1 - View Next Task" << std::endl;
			std::cout << "2 - View Previous Task" << std::endl;
			std::cout << "3 - View Tasks To Run" << std::endl;
			std::cout << "4 - View Completed Tasks" << std::endl;
			std::cout << "5 - Delete A Stimulation" << std::endl;
			std::cout << "6 - Initiate Flight Plan" << std::endl;
			std::cout << "0 - Back To Main Menu" << std::endl;
			std::cout << "> ";
			std::cin >> option;
			std::cin.clear();
			std::cin.ignore();

			if (!std::cin.fail())
			{
				if (option >= 0 && option <= 6)
				{
					switch (option)
					{
					case 0:
					{
							  std::cin.clear();
							  x = 0;
							  std::cout << std::endl;
							  break;
					}
					case 1:
					{
							  if (!ToRun.empty())
							  {
								  std::cout << std::endl;
								  displayNext(*ofs);
							  }
							  else
							  {
								  std::cout << "\nTasks are completed OR no Tasks available." << std::endl;
							  }
							  break;
					}
					case 2:
					{
							  if (count > 0)
							  {
								  std::cout << std::endl;
								  displayPrev(*ofs);
							  }
							  else
							  {
								  std::cout << "\nNo previous tasks." << std::endl;
							  }
							  break;
					}
					case 3:
					{
							  if (!ToRun.empty())
							  {
								  std::cout << std::endl;
								  displayToRun(*ofs);
							  }
							  else
							  {
								  std::cout << "\nNo tasks available." << std::endl;
							  }
							  break;
					}
					case 4:
					{
							  if (!Completed.empty())
							  {
								  std::cout << std::endl;
								  displayCompleted(*ofs);
							  }
							  else
							  {
								  std::cout << "\nNo tasks have been completed." << std::endl;
							  }
							  break;
					}
					case 5:
					{
							  std::string task, stim, comp;
							  *ofs << "Delete A Stimulation" << std::endl;
							  *ofs << "====================" << std::endl << std::endl;
							  std::cout << "Delete A Stimulation" << std::endl;
							  std::cout << "====================" << std::endl << std::endl;
							  for (unsigned short i = 0; i < ToRun.size(); i++) //list available tasks
							  {
								  ToRun[i]->dump(*ofs);
							  }
							  *ofs << std::endl;
							  std::cout << std::endl;
							  *ofs << "Please choose an available task from the list:" << std::endl;
							  *ofs << "> ";
							  std::cout << "Please choose an available task from the list:" << std::endl;
							  std::cout << "> ";
							  std::cin >> task;
							  std::cout << std::endl;
							  try{
								  for (unsigned short i = 0; i < ToRun.size(); i++) //loop through to locate task and set Task object to located task
								  {
									  comp = ToRun[i]->getTaskName();
									  if (task == comp)
									  {
										  ToRun[i]->dump(*ofs);
										  *ofs << std::endl;
										  std::cout << std::endl;
										  *ofs << "Please choose an available stimulation from the list:" << std::endl;
										  std::cout << "Please choose an available stimulation from the list:" << std::endl;
										  *ofs << "> ";
										  std::cout << "> ";
										  std::cin >> stim;
										  ToRun[i]->delStim(stim);
										  *ofs << std::endl;
										  std::cout << std::endl;
										  ToRun[i]->dump(*ofs);
										  *ofs << std::endl;
										  std::cout << std::endl;
										  *ofs << stim << " successfully deleted." << std::endl;
										  std::cout << stim << " successfully deleted." << std::endl;
										  break;
									  }
								  }
								  if (task != comp)
									throw std::string("Please ensure that the Task name is spelt EXACTLY the same as in the list above.");
							  }
							  catch (std::string msg)
							  {
								  std::cerr << msg << std::endl;
							  }
							  break;
					}
					case 6:
					{
							std::string decision;
							std::cout << std::endl << "Begin Flight Simulation" << std::endl;
							std::cout << "=======================" << std::endl << std::endl;
							*ofs << std::endl << "Begin Flight Simulation" << std::endl;
							*ofs << "=======================" << std::endl << std::endl;

							while (!ToRun.empty())
							{
								if (ToRun[0]) //if ToRun at location 0 exists, keep running
								{
									ToRun[0]->execute(*ofs);
									Completed.push_back(std::move(ToRun[0]));
								}
								ToRun.pop_front();
								count++;

								std::cout << "Would you like to initiate the next task? (Y/N) > ";
								std::cin >> decision;
								if (decision == "n" || decision == "N")
								{
									std::cout << std::endl;
									break;
								}
								else if (decision == "y" || decision == "Y")
								{
									continue;
								}
								else if (decision != "y" || decision != "Y")
								{
									std::cout << std::endl << "===INVALID INPUT===   Please input Y or N next time\n\n";
									break;
								}
								std::cout << std::endl << std::endl;
							}
							if (ToRun.empty())
							{
								std::cout << "Simulation complete." << std::endl;
								*ofs << "Simulation complete." << std::endl;
							}
							break;
					}
					}
				}
			}
		} while (x == 1);
	}

	int Profile::run()
	{
		unsigned short choice;

		do{
			choice = menu();
			
			switch (choice)
			{
				case 1:
				{
					flightPlan();
					break;
				}
				case 2:
				{
					flightInfo();
					break;
				}
				case 3:
				{
					char exit;
					std::cout << "Thank you for using ARAIG." << std::endl;
					std::cout << "We're glad you didn't throw up on our very expensive flight suit!" << std::endl;
					std::cout << "Goodbye!" << std::endl;
					std::cin >> exit;
					break;
				}
				default:
				{
					std::cout << "---INVALID SELECTION---" << std::endl;
					std::cout << "Please input a valid number." << std::endl;
				}
			}

		} while (choice != 3);

		return 0;
	}

	int Profile::menu()
	{
		unsigned short valid = 0;

		std::cout << "ARAIG (As Real As It Gets) Flight Simulation Suit" << std::endl;
		std::cout << "=================================================" << std::endl;
		std::cout << "1 - Flight Simulator" << std::endl;
		std::cout << "2 - Student/Instructor Information & Flight Plan" << std::endl;
		std::cout << "3 - Exit Program" << std::endl;
		std::cout << "> ";
		std::cin >> valid;
		std::cout << std::endl;
		std::cin.clear();
		std::cin.ignore();

		if (!std::cin.fail()) //make sure that the user inputs the correct input
		{
			if (valid >= 1 && valid <= 3)
			{
				switch (valid)
				{
					case 1:
					{
						valid = 1;
						break;
					}
					case 2:
					{
						valid = 2;
						break;
					}
					case 3:
					{
						valid = 3;
						break;
					}
				}
			}
		}

		return valid;
	}
}