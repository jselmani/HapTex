#include "Stims.h"

namespace a1
{
	Stims::Stims() : Stimulation() //SES
	{
		stimName.clear();
		intensity = 0;
		freq = 0;
		duration = 0;
	}

	Stims::Stims(std::string& t_, std::string& sName, sLoc l_, unsigned short inten, unsigned short freq_, unsigned short dur_) : Stimulation(t_)
	{
		if(!sName.empty() && (inten >= 0 && inten <= 100) && freq_ >= 0 && dur_ >= 0) //validate
		{
			stimName = sName;
			location = l_;
			intensity = inten;
			freq = freq_;
			duration = dur_;
		}
		else
		{
			throw std::string("The Stims data has been corrupted in the file.");
		}
	}

	std::string Stims::getStim() const
	{
		return stimName;
	}

	void Stims::display(std::ostream& os) const
	{
		std::cout << stimName << std::endl;
		os << stimName << std::endl;
		std::cout << "     Type = " << getType() << std::endl;
		os << "     Type = " << getType() << std::endl;
		std::cout << "     Location = ";
		os << "     Location = ";
		if (location == abs)
		{
			std::cout << "abs" << std::endl;
			os << "abs" << std::endl;
		}
		else if (location == front)
		{
			std::cout << "front" << std::endl;
			os << "front" << std::endl;
		}
		else if (location == back)
		{
			std::cout << "back" << std::endl;
			os << "back" << std::endl;
		}
		else
		{
			std::cout << "traps" << std::endl;
			os << "traps" << std::endl;
		}
		std::cout << "     Intensity = " << intensity << std::endl;
		os << "     Intensity = " << intensity << std::endl;
		std::cout << "     Frequency = " << freq << std::endl;
		os << "     Frequency = " << freq << std::endl;
		std::cout << "     Duration = " << duration << std::endl;
		os << "     Duration = " << duration << std::endl;
		std::cout << std::endl;
		os << std::endl;
	}
}