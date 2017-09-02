#ifndef _STIMS_H_
#define _STIMS_H_
#include "Stimulation.h"

namespace a1
{
	enum sLoc {abs, front, back, traps};

	class Stims : public Stimulation
	{
	private:
		std::string stimName;
		sLoc location;
		unsigned short intensity;
		unsigned short freq;
		unsigned short duration;
	public:
		void display(std::ostream&) const;
		std::string getStim() const;
		Stims();
		Stims(std::string&, std::string&, sLoc, unsigned short, unsigned short, unsigned short);
		~Stims(){};
	};
}

#endif