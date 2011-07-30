#include "PluginManager.h"


PluginManager::~PluginManager(void)
{
}

PluginManager::PluginManager(std::string pExt, std::string pDir) : mPluginExtension(pExt), mPluginDirectory(pDir)
{
	// Check for valid directory plugins and populate list of valid ones.
	checkPluginDir();

	// Load all valid plugins
	loadPlugins();
}

void PluginManager::checkPluginDir()
{
	if ( (boost::filesystem::exists(mPluginDirectory)) && (boost::filesystem::is_directory(mPluginDirectory)) )
	{
		typedef std::vector<boost::filesystem::path> vec;
		vec v;

		copy(boost::filesystem::directory_iterator(mPluginDirectory), boost::filesystem::directory_iterator(), back_inserter(v));
		// Sort direcotry iterator...
		sort(v.begin(), v.end());

		// Iterate through directory in search of valid plugins
		for (vec::const_iterator it(v.begin()), it_end(v.end()); it != it_end; ++it)
		{
			boost::filesystem::path p = *it;
			// Skip if it's not a file
			if (!boost::filesystem::is_regular_file(p)) continue;
			
			// Skip if extension is invalid
			if (boost::filesystem::extension(p) == mPluginExtension)
			{				
				// Adciona na lista de imagens...
				mPluginFileNameList.push_back(p.string());
			}
		}
	}
	else
	{
		throw std::exception("Invalid directory");
	}

	if (mPluginFileNameList.size() == 0)
	{
		throw std::exception("No plugins found");
	}
}

void PluginManager::loadPlugins()
{
	// Iterate through each plugin loading it
	for (std::vector<std::string>::iterator it = mPluginFileNameList.begin(); it != mPluginFileNameList.end(); it++)
	{		
		void * handle = NULL;
		std::string plugName = *it;
		
		// Way that libraries are loaded is dependent of OS (Windows(LoadLibraryA), Linux(dlopen))
		handle = ::LoadLibraryA (plugName.c_str());

		if (handle)
		{
			// Way that library simbols are loaded is dependent of the OS (Windows(GetProcAddress), Linux(dlsym))
			PLUGIN_FACTORY p_factory_function = (PLUGIN_FACTORY) ::GetProcAddress ((HMODULE) handle, "Create_Plugin");
			PLUGIN_CLEANUP p_cleanup_function = (PLUGIN_CLEANUP) ::GetProcAddress ((HMODULE) handle, "Release_Plugin");

			if (p_factory_function != NULL && p_cleanup_function != NULL)
			{
				// Call our library factory to create our plugin instance
				IPlugin* p_plugin = (*p_factory_function) ();

				// Just to debug show our plugin name
				std::cout << "Plugin=" << p_plugin->Get_Name() << " loaded " << std::endl;

				// Call our plugin code
				p_plugin->Process_Data();

				// Nice now clean our plugin instance by calling our plugin clean function
				(*p_cleanup_function)(p_plugin);
			}
			else
			{
				throw std::exception("Could not find plugin signature");
			}
		}
		else
		{
			throw std::exception("Could not open Plugin");
		}
	}
}
