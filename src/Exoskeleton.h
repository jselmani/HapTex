#ifndef _EXOSKELETON_H_
#define _EXOSKELETON_H_
#include "Stimulation.h"

namespace a1
{

	class Exoskeleton : public Stimulation
	{
	private:
		std::string exoName;
		unsigned short intensity;
		unsigned short duration;
	public:
		void display(std::ostream&) const;
		std::string getStim() const;
		Exoskeleton();
		Exoskeleton(std::string&, std::string&, unsigned short, unsigned short);
		~Exoskeleton(){};
	};
}

#endif