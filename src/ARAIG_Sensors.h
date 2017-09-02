#ifndef _ARAIG_H_
#define _ARAIG_H_

#include <memory>
#include "Task.h"

namespace a1
{

	class ARAIG_Sensors
	{
	private:
		Stimulation** stimList;
		Task* taskList;
		unsigned short countStims;
		unsigned short countTasks;
	public:
		ARAIG_Sensors(std::string, std::string);
		~ARAIG_Sensors();
		void readStims(std::ifstream&);
		void readTasks(std::ifstream&);
		void dumpStims(std::ostream& os) const;
		void dumpTasks(std::ostream& os) const;
		Task& getTask(std::string) const;
	};
}

#endif