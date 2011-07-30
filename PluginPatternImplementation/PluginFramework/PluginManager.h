#pragma once
/*
	Class used to manage all visible plugins in some directory 
*/

#include <string>
#include <vector>

// Boost funcions to filesystem
#include <boost/filesystem.hpp>

// Header of abstract plugin
#include "IPlugin.h"

// Functions for loading libraries
#ifdef WIN32
  #include <Windows.h>
#else
  #include <dlfcn.h>
#endif

class PluginManager
{
public:	
	PluginManager(std::string pExt, std::string pDir);
	~PluginManager(void);
private:
	std::string mPluginExtension;
	std::string mPluginDirectory;
	int mVecIndex;
	std::vector< std::string > mPluginFileNameList;
	
	void checkPluginDir();
	void loadPlugins();
};

// Typedef for our plugin signature (our plugins must implement those 2 functions at least)
typedef IPlugin* (*PLUGIN_FACTORY)(); 
typedef void (*PLUGIN_CLEANUP)(IPlugin*); 
