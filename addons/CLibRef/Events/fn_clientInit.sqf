// Include the macro-file from the module-root
#include "macros.hpp"

/**
 * CLibRef - clientInit
 * 
 * Author: Raven
 * 
 * Description:
 * Initializes the CLibRef Events module on the client-side. This example will add various event handlers
 * for demonstration purposes. It will also demonstrate how to "create" a custom event.
 * More precisely a hint will be shown whenever the map is being opened/closed. Furthermore another hint will
 * will be shown whenever the player opens his/her inventory, or changes the current weapon.
 * 
 * Parameter(s):
 * 0: None <Any>
 * 
 * Return Value:
 * None <Any>
 * 
 */

// Define a new, custom event name. These kind of things should always be done via the preprocessor in case those names have to
// change at some point. Normally it would be advisable to include the framework's name into the event name in order to minimize
// the chance of name-collisions with other frameworks.
// Also it normally is best to define the event strings in an external file that can be included everywhere where those names are
// required. This avoids typing errors in the event framework and facilitates refactoring (a lot!)
#define MY_EVENT "MyEvent"

// add the EventHandler for the map opening/closing
// This is a standard CLib event. Refer to https://github.com/TaktiCool/CLib/wiki/Events for more information
["visibleMapChanged", {
	// Decompose the provided arguments (via the _this variable) into its respective parts
	_this params ["_eventArgs", "_handlerArgs"];
	
	// Show a hint also containing the decomposed parameters passed to this handler
	hint format ["Map visibility just changed. Handler args: %1 Event args: %2", _handlerArgs, _eventArgs];
}, ["MyHandlerArg"]] call CFUNC(addEventHandler);
// See https://github.com/TaktiCool/CLib/blob/master/addons/CLib/Events/fn_addEventHandler.sqf for more information on the addEventHandler function



// Add EventHandler for custom Event - aka the "new" Event
[MY_EVENT, {
	// Decompose the provided arguments (via the _this variable) into its respective parts
	_this params ["_eventArgs", "_handlerArgs"];
	
	// Show a hint that the custom event has been triggered - also include decomposed parameters that have been passed to
	// this handler
	hint format ["Custom event has just been triggered. Handler args: %1 Event args: %2", _handlerArgs, _eventArgs];
},[]] call CFUNC(addEventHandler);


// Note that if we left the code as it is to this point our custom event would never be triggered. Adding the EventHandler is still valid
// though and won't throw any errors (though it would be quite useless).
// In order to trigger the custom event we are going to fire local events if the player's current weapon changes or if he/she
// opens his/her inventory (for both of those events there exist pre-defined events in Clib. See https://github.com/TaktiCool/CLib/wiki/Events).

["currentWeaponChanged", {
	// Decompose the provided arguments (via the _this variable) into its respective parts
	_this params ["_eventArgs", "_handlerArgs"];
	
	// trigger our custom event locally
	[MY_EVENT, [_eventArgs]] call CFUNC(localEvent);
},[]] call CFUNC(addEventHandler);

["InventoryOpened", {
	// Decompose the provided arguments (via the _this variable) into its respective parts
	_this params ["_eventArgs", "_handlerArgs"];
	
	// trigger our custom event locally
	[MY_EVENT, [_eventArgs]] call CFUNC(localEvent);
},[]] call CFUNC(addEventHandler);



