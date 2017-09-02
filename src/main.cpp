#include <iostream>
#include <string>
#include "Profile.h"

using namespace a1;

int main(int argc, char** argv) {
	if (argc != 5) {
		std::cerr << argv[0] << ": incorrect number of arguments\n";
		std::cerr << "Usage: " << argv[0] << " file_name\n";
		return 1;
	}

	std::ofstream out;
	try{
		out.open("JielSelmanovskiOutput.txt", std::ofstream::out | std::ofstream::trunc);
		ARAIG_Sensors araig(argv[1], argv[2]);
		Profile chloe(argv[3], out, araig);
		chloe.run();
	}
	catch (std::string msg)
	{
		std::cerr << msg << std::endl;
	}

	out.close();
}