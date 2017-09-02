#include "Stimulation.h"
#include "Stims.h"
#include "Exoskeleton.h"

namespace a1
{
	Stimulation::Stimulation()
	{
		type.clear();
	}

	Stimulation::Stimulation(const std::string& str)
	{
		if(!str.empty())
		{
			type = str; //shallow copy
		}
		else
		{
			throw std::string("The Stimulation type name has been corrupted in the file.");
		}
	}

	std::string Stimulation::getType() const
	{
		return type; //when being used by derived classes
	}
}