#ifndef _TASK_H_
#define _TASK_H_

#include "Stims.h"
#include "Exoskeleton.h"

#include <list>
#include <iterator>

namespace a1
{
	class Task
	{
		private:
			std::string tName;
			std::list<Stimulation*> taskStims;
		public:
			Task();
			Task(std::string);
			Task(const Task&);
			Task& operator=(const Task&);
			Task(Task&&);
			Task&& operator=(Task&&);
			Task& operator+=(Stimulation*);
			~Task() {};
			Stimulation* operator[](unsigned short) const;
			std::string delStim(const std::string);
			std::string getTaskName();
			void dump(std::ostream& os) const;
			void execute(std::ostream&) const;
	};
}


#endif