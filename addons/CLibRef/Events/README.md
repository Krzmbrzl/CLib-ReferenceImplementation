# Events
In this module the event system of CLib shall be introduced. CLib's Event-system at its core consists of an `addEventHandler` function and various functions for triggering/emitting events.
Each event is identified by a unique String - the event name.

## The functions

### AddEventHandler
The `addEventHandler` has the following syntax:
```
GVAR(handlerID) = [<EventName>, <EventCode>, <CodeArguments>] call CFUNC(addEventHandler);
```
- `<EventName>` is the unqiue event name.
- `<EventCode>` is the code that should get executed whenever an event of the respective `<EventID>` gets triggered on this machine.
- `<CodeArguments>` optionally are the arguments that will be passed to the `<EventCode>` once it gets executed. They will be accessible via `_this select 1` inside the `<EventCode>`. the default is `[]`.

This function returns an integer number that is the unique ID of the just added Event**Handler** (to be differentiated form the evnt itself that is being identified by its name).

### removeEventHandler
If you want to remove an existing EventHandler, you can use the `removeEventHandler` function:
```
private _success = [<EventName>, <HandlerID>] call CFUNC(removeEventHandler);
```
- `<EventName>` is the name of the event the handler has been assigned to.
- `<HandlerID>` is the unique integer ID of the handler as returned by `addEventHandler`.

This function returns a boolean value indicating whether the removal of the EventHandler was successful.

### Triggering an event
For triggering an event the following functions are available:
- `CFUNC(localEvent)`
- `CFUNC(globalEvent)`
- `CFUNC(targetEvent)`
- `CFUNC(serverEvent)`

**Local Events:** A local event is an event that will never leave the client that it has been triggered on. In other word: No other client (nor the server/HC) will ever know that this event
has been emitted on this machine. It will always be local to this machine. The syntax for emitting local event is
```
[<EventName>, <Parameters>] call CFUNC(localEvent);
```
- `<EventName>` is the identifying name of the event that should be triggered.
- `<Parameters>` is an optional argument. These are the parameters that will be accessible the in the EventHandler's code via `_this select 0`.

**Global Events:** A global event will be broadcast over the network to every machine in it (including server and HC). It can also be marked as
persistent so that once triggered it will also fire on any client connecting to the game later on (as soon as that client has properly connected).
The syntax for triggering global events is basically the same as for local events:
```
[<EventName>, <Parameters>, <Persistent>] call CFUNC(globalEvent);
```
- `<EventName>` is the identifying name of the event that should be triggered.
- `<Parameters>` is an optional argument. These are the parameters that will be accessible the in the EventHandler's code via `_this select 0`. The default is `[]`.
- `<Persistent>` is an optional boolean flag indicating whether the triggered event should be persistent. Teh default is `false`.

**Target Events:** A targeted event is an event that gets triggered on a specific target machine (e.g. the server or a specific (remote) client).
To trigger a targeted event one has to use the following syntax:
```
[<EventName>, <Target>, <Parameters>] call CFUNC(targetEvent);
```
- `<EventName>` is the identifying name of the event that should be triggered.
- `<Target>` is one of these types: <Array, Group, Number, Object, Side, String>. If this is an array, it is considered to be an array of the other types. Thiwsw will result in this event being executed on all specified targets.
If this is a group, the event will be triggered on all machines whose players are members of that group. If this is a number, it will be interpreted in the same way as the target option for the `remoteExec` SQF command.
If this is an Object, this event will be triggered on the machine that owns the given object (determined via the `owner` SQF command). If this is a side, the event will be triggered on all machines whose players are members of
the given side. Finally if this is a String, it can either be a String representation of the different sides in which case it will be treated as if the respective side had been supplied. Alternatively it can be a class inside
`CfgVehicles` in which case this method behaves as if a list of all `missionObjects` of that class had been supplied. If none of the before matches, the UIDs of all players is ebing checkd and if one matches, the event will be
triggered on this player's machine.
- `<Parameters>` is an optional argument. These are the parameters that will be accessible the in the EventHandler's code via `_this select 0`. The default is `[]`.

**Server Events:** A server event is a shortcut for a target event that targets the server. It is therefore equivalent of a target event with a target of `2`.
Its syntax is
```
[<EventName>, <Parameters>] call CFUNC(serverEvent);
```
- `<EventName>` is the identifying name of the event that should be triggered.
- `<Parameters>` is an optional argument. These are the parameters that will be accessible the in the EventHandler's code via `_this select 0`. The default is `[]`.


## Available events
There is a list of events that are available by default in the [CLib wiki](https://github.com/TaktiCool/CLib/wiki/Events).

If you wish to "define" a new event it is as simple as thinking of a new _unique_ event name (it must not be used by any other framework that
gets loaded simultaneously - unless of course it has the same meaning). Once that is done, one can use one of the functions to triggere these events
in certain cases. In order to make use of custom events "created" in this way, one simply has to add an EventHandler that listens to events with
that name. And that's it. There's nothing mroe to it.


## The EventCode
Code supplied for any EventHandler will have access to a `_this` varible. This variable can be decomposed in the following way:
```
_this params ["_eventArgs", "_handlerArgs"];
```
 If decomposed in this way, `_eventArgs` will be the list of parameters that have been supplied while triggering the event (the ones that have
 been passed to e.g. the `localEvent` function).
 `_handlerArgs` on the other hand will be the list of parameters that have been supplied on the creation of the EventHandler (the ones that have
 been passed to the `addEventHandler` function).

The code inside an EventHandler shouldn't perform any heavy processing as the code for all handlers that have been added for that particular
event will conecutively be executed in a single frame. In the worst case this could lead to (micro) freezes whenever that event is being triggered).
