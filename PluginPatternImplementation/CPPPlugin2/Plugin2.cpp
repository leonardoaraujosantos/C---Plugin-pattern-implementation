#include "Plugin2.h"

const char* Plugin2::Get_Name() const
{
	return "Plugin2";
}

void Plugin2::Process_Data()
{
	for (int i = 0; i < 3; i++)
	{		
		std::cout << "Plugin 2 is processing...." << std::endl;		
	}

	std::cout << "Plugin 2 processing done" << std::endl;
}
