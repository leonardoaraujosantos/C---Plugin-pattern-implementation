#include "Plugin1.h"

const char* Plugin1::Get_Name() const
{
	return "Plugin1";
}

void Plugin1::Process_Data()
{
	for (int i = 0; i < 3; i++)
	{		
		std::cout << "Plugin 1 is processing...." << std::endl;
	}

	std::cout << "Plugin 1 processing done" << std::endl;
}
