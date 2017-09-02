#ifndef _PROFILE_H_
#define _PROFILE_H_
#include "ARAIG_Sensors.h"
#include <vector>
#include <queue>

namespace a1
{
	class Profile
	{
		private:
			std::string sFName, sLName; //student first name
			unsigned int sNum, iNum; //ID numbers
			std::string iFName, iLName; //flight instructor
			std::ofstream* ofs; //reference to an ofstream object
			struct cal
			{
				unsigned short min;
				unsigned short max;
			} calibrate;
			std::deque<Task*> ToRun;
			std::vector<Task*> Completed;
		public:
			Profile(const char*, std::ofstream&, ARAIG_Sensors&);
			~Profile();
			void displayToRun(std::ostream&) const;
			void displayCompleted(std::ostream&) const;
			void displayNext(std::ostream&) const;
			void displayPrev(std::ostream&) const;
			void flightInfo() const;
			void flightPlan();
			int run();
			int menu();
	};
}

#endif