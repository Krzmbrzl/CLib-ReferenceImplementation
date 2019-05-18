#include "macros.hpp"
class CfgPatches {
    class PREFIX {
        units[] = {};
        weapons[] = {};
        requiredVersion = 1.70;
        author = "Raven";
        authors[] = {"Raven"};
        authorUrl = "";
        version = QUOTE(VERSION);
        versionStr = QUOTE(VERSION);
        versionAr[] = {VERSION_AR};
        requiredAddons[] = {"CLib"}; // mark dependency on the CLib-mod
    };
};

// include modules-file that holds the CLib-spec of all files/functions in this mod
#include "modules.hpp"

// note the absence of a CfgFunctions. This one is replaced by the CLib modules
