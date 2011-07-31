#include "..\\PluginFramework\\PluginManager.h"

#include <boost/program_options.hpp>
namespace po = boost::program_options;


int main(int ac, char* av[])
{
	std::string plugDir;
	std::string plugExt;

	try
	{
		// Parse program options
		po::options_description desc("Allowed options");
		desc.add_options()            
			("help,h", "produce help message")
			("directory,d", po::value<std::string>(&plugDir)->default_value("."),"Plugins directory.")
			("extension,e", po::value<std::string>(&plugExt)->default_value(".dll"),"Plugins extension")			
        ;
		po::variables_map vm;        
        po::store(po::parse_command_line(ac, av, desc), vm);
        po::notify(vm);
		
		if (vm.count("help")) 
		{
			std::cout << desc << std::endl;
            return 1;
        }

		if (vm.count("directory"))
        {            
			std::cout << "Plugin directory: " << vm["directory"].as<std::string>() << std::endl;			
        }

		if (vm.count("extension"))
        {            
			std::cout << "Plugin directory: " << vm["extension"].as<std::string>() << std::endl;			
        }

		// Initialize plugin manager
		PluginManager pm(plugExt, plugDir);

		IPlugin* plugin = pm.getPlugin("Plugin1");
		plugin->Process_Data();

		plugin = pm.getPlugin("Plugin2");
		plugin->Process_Data();

		plugin = pm.getPlugin("Plugin3");
		plugin->Process_Data();
	}
	catch(std::exception &e)
	{		
		std::cerr << "Exception detected" << std::endl;
		std::cerr << e.what() << std::endl;
	}

	return 0;
}