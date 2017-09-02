#ifndef _STIMULATION_H_
#define _STIMULATION_H_
#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

namespace a1
{

	class Stimulation
	{
		private:
			std::string type; //declare type of class name that derives it
		protected:
			Stimulation();
			Stimulation(const std::string&);
		public:
			virtual void display(std::ostream&) const = 0; 
			virtual std::string getStim() const = 0;
			std::string getType() const;  //return type of class that will be created for writing to console/file
	};
}

#endif