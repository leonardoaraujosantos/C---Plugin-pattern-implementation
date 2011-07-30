#pragma once
/*
Pure abstract class (Interface) used to declare a plugin
*/

class IPlugin
{
public:
	//returns the name of the concrete plugin
	virtual const char* Get_Name () const = 0;

	//does the actual data processing
	virtual void Process_Data () = 0;
};
