#include "Exoskeleton.h"

namespace a1
{
	Exoskeleton::Exoskeleton() : Stimulation() //SES
	{
		exoName.clear();
		intensity = 0;
		duration = 0;
	}

	Exoskeleton::Exoskeleton(std::string& t_, std::string& eName, unsigned short inten, unsigned short dur_) : Stimulation(t_)
	{
		if(!eName.empty() && (inten >= 0 && inten <= 100) && dur_ >= 0) //validate
		{	
			exoName = eName;
			intensity = inten;
			duration = dur_;
		}
		else
		{
			throw std::string("The Exoskeleton data has been corrupted in the file.");
		}
	}

	std::string Exoskeleton::getStim() const
	{
		return exoName;
	}

	void Exoskeleton::display(std::ostream& os) const
	{
		std::cout << exoName << std::endl;
		os << exoName << std::endl;
		std::cout << "     Type = " << getType() << std::endl;
		os << "     Type = " << getType() << std::endl;
		std::cout << "     Intensity = " << intensity << std::endl;
		os << "     Intensity = " << intensity << std::endl;
		std::cout << "     Duration = " << duration << std::endl;
		os << "     Duration = " << duration << std::endl;
		std::cout << std::endl;
		os << std::endl;
	}
}