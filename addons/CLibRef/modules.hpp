// include the required addons directly from CLib
#include "\tc\CLib\addons\CLib\ModuleMacros.hpp"
#include "macros.hpp"

// This file is kind of the CLib-correspondant to the standard CfgFunctions - though it got way more features
// concerning both: security and debuggabilty (e.g. full stack-traces).
// Every "module" represents a folder inside this mod and all FNC(someName) correspond
// to a file called fn_someName.sqf in that module-folder
class CfgCLibModules {
	// This is the name of this mod as can be used to refer to it via the Clib-framework
	// casing does not matter (all names are being transformed to lower-cases)
	// The name should be given via the PREFIX macro in order to be able to use the FUNC macro to
	// refer to functions defined here. Everything else will lead to confusion.
    class PREFIX {
		// Specify the absolute path of the root of all listed modules below
		// this is determined by the used PBO-prefix
        path = "rvn\clibref\addons\clibref";
		
		// list the dependencies of this mod inside the CLib-framework (that is either Clib itself or any
		// mod that builds upon it). Dependencies are always references to modules inside another mod
		// in the form "ModName/ModuleName"
		// All dependencies specified here are simply appended to each module's dependencies.
		// Dependencies in CLib are used to determine which code-fragments need to be sent to the client.
		// If a dependency can not be met, an error message will be written to the respective RPT file.
		// All dependencies are matched case-insensitively
		dependency[] = {};
		
		// the module-names are also case-insensitive
		MODULE(PerFrame) {
			// The dependency-array specifies on which components inside the CLib-framework this particular
			// module is dependent.
			dependency[] = {"CLib/PerFrame", "Clib/Events"};
			// Declares a new function in this module. It is expected to correspond to
			// a file fn_clientInit.sqf inside the folder PFH (as this is the module's name).
			// This is actually a special function as this is an entry point (see at the bottom of this file)
			FNC(clientInit);
		};
		
		MODULE(Events) {
			dependency[] = {"CLib/Events"};
			
			FNC(clientInit);
		}
    };
};

///////////////////////////// ENTRY POINTS /////////////////////////////
// Entry points are special functions that get called automatically at some point. This means that
// they serve as the entry to the code-execution of any mod. An entry point in standard SQF is the init.sqf
// CLib has its own entry points (which are more sophisticated than standard Arma'sb_type
// Entry points are determined based on the name of a given function. All entry points are called as soon as possible (that
// is after the CLib-framework and all dependencies of the respective module has been initialized). The following entry points exist:
// - FNC(clientInit) This function gets called on any client (not the server nor a HC) [condition: hasInterface]
// - FNC(serverInit) This function gets called on the server (not on any client ar any HC) [doncition: isServer]
// - FNC(hcInit) This function gets called on every headless client (HC) (not on any client nor the server) [condition: !isServer && !hasInterface]
// - FNC(init) This function gets called on every machine (including all clients, the server and all HCs) [no condition]
// Note that the global init-entry point gets called before the more specialized ones.
// Further details: https://github.com/TaktiCool/CLib/blob/master/addons/CLib/Core/Autoload/fn_callModules.sqf


// Furhter details on how the module-loading and handling is being handled can be found
// in CLib's source code: https://github.com/TaktiCool/CLib/blob/master/addons/CLib/Core/Compile/fn_readAllModules.sqf
// Or in all detail: https://github.com/TaktiCool/CLib/blob/master/addons/CLib/Core/Compile/ in combination with
// https://github.com/TaktiCool/CLib/blob/master/addons/CLib/Core/Autoload
