#pragma once

#include "..//PluginFramework//IPlugin.h"

#include <iostream>
#include <string>

class Plugin2 : public IPlugin
{
public:
	//returns the name of the concrete plugin
	const char* Get_Name() const;
	virtual void Process_Data();
};

// Our signature functions used also to create our Plugin class instance
extern "C"
{
	// Plugin factory function
	__declspec(dllexport) IPlugin* Create_Plugin ()
	{
		//allocate a new object and return it
		return new Plugin2 ();
	}

	// Plugin cleanup function
	__declspec(dllexport) void Release_Plugin (IPlugin* p_plugin)
	{
		//we allocated in the factory with new, delete the passed object
		delete p_plugin;
	}

}
