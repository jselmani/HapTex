#include "Task.h"

namespace a1
{
	Task::Task()
	{
		//std::cout << "Entering default constructor..." << std::endl;
		tName.clear();
		taskStims.clear();
	}

	Task::Task(std::string name) //to instantiate an object with just a name
	{
		tName = name;
		taskStims.clear();
	}

	Task::Task(const Task& src)
	{
		//std::cout << "Entering copy constructor..." << std::endl;
		tName = src.tName;
		taskStims = std::list<Stimulation*>(src.taskStims);
	}

	Task& Task::operator=(const Task& src)
	{
		//std::cout << "Entering copy assignment..." << std::endl;
		if(this != &src)
		{
			tName = src.tName;
			taskStims = std::list<Stimulation*>(src.taskStims);
		}
		else
		{
			tName.clear();
			taskStims.clear();
		}

		return *this;
	}

	Task::Task(Task&& src)
	{
		//std::cout << "Entering move constructor..." << std::endl;
		tName = src.tName;
		taskStims = std::list<Stimulation*>(src.taskStims);
		src.tName.clear();
		src.taskStims.clear();
	}

	Task&& Task::operator=(Task&& src)
	{
		//std::cout << "Entering move assignment..." << std::endl;
		if(this != &src)
		{
			tName = src.tName;
			taskStims = std::list<Stimulation*>(src.taskStims);
			src.tName.clear();
			src.taskStims.clear();
		}
		else
		{
			tName.clear();
			taskStims.clear();
		}

		return std::move(*this);
	}

	Task& Task::operator+=(Stimulation* src)
	{
		taskStims.push_back(src);
		return *this;
	}

	Stimulation* Task::operator[](unsigned short i) const
	{
		if(taskStims.size() > i)
		{
			auto search = taskStims.begin();
			std::advance(search, i); //advances iter to location of i to find object
			return *search;
		}
		else
		{
			throw std::string("Element requested is not in the task list.");
			return nullptr;
		}
	}

	std::string Task::delStim(const std::string name_)
	{
		//std::cout << "Deleting Stimulation " << name_ << std::endl;
		for (auto i = taskStims.begin(); i != taskStims.end(); i++)
		{
			if ((*i)->getStim() == name_)
			{
				taskStims.erase(i);
				return name_;
				break; //break to ensure that the linked list stays chained together
			}
		}
		throw std::string("Please ensure that the stimulation name is spelt EXACTLY how it is displayed above.");
	}

	std::string Task::getTaskName()
	{
		return tName;
	}

	void Task::dump(std::ostream& os) const
	{
		std::cout << std::endl << "TASK: " << tName << std::endl;
		os << std::endl << "TASK: " << tName << std::endl;

		for (auto i = taskStims.begin(); i != taskStims.end(); i++)
		{
			std::cout << (*i)->getStim() << std::endl;
			os << (*i)->getStim() << std::endl;

			//using (*i)-> because we are pointing to a Stimulation object that is derived from Stimulation
			//this is absolutely crucial as we are performing a double dereference
		}
	}

	void Task::execute(std::ostream& os) const
	{
		std::cout << "TASK: " << tName << std::endl;
		os << "TASK: " << tName << std::endl;

		for (auto i = taskStims.begin(); i != taskStims.end(); i++)
		{
			(*i)->display(os); //see dump
		}
	}
}