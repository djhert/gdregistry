# ![Godot](https://raw.githubusercontent.com/hlfstr/gdnative-project/master/icon.png) GDNative Registry
**...and other helpful GDNative stuff too!**

## Usage
This project is meant to be used with the build setup here: **[gdnative-project](https://github.com/hlfstr/gdnative-project)**

The included CMake file inherits many properties from that setup, including the location of the `godot-cpp` bindings.  Please see that repository for a nice (in my opinion) setup for GDNative development.  The rest assumes you are using the above.

Include this as a `git subtree` in your `source/include` folder.

```sh
$ git subtree add --prefix=source/include/gdregistry https://github.com/hlfstr/gdregistry master
```

From there, issue a build the standard way and GDRegistry will be built!

### How it works

GDNative Registry (GDRegistry) is a singleton that allows you to store the **_register_class_** and **_register_tool_class_** function calls for your custom GDNative classes that you use.  Normally, Godot requires you to list all of the functions in the **_godot_nativescript_init()_**; however this can be cumbersome when you have many classes that you need to register.  Using this to register a class you only need to have a `static bool` defined in your C++ class and initialize it the following way in your `.cpp` file:

```c++
bool classname::boolean = godot::GDRegistry::Register<classname>();
```

The included `gdlib.cpp` file will setup GDNative for you, as well as run the registrations when Godot starts.  This means just include this and work on **YOUR** code.

#### Priority 

Registration order does matter in Godot, so **GDRegistry** also allows each **_Register_** function an optional **priority** parameter.  Objects added to **GDRegistry** are registered in order of higher priority.  By default, **_Register_** issues a priority of **0** and **_RegisterTool_** issues a priority of **10**.

**Example:**
Say you have 2 classes: **GDParent** and **GDChild**;  **GDChild** is a subclass of **GDParent**

In order to have this register properly, **GDParent** must be registered first.  The following is proper usage:
```c++
// In `gdparent.cpp`
// Assign GDParent with a priority of 1 to ensure it is registered first
bool classname::_reg = godot::GDRegistry::Register<GDParent>(1);
// GDREGISTER(GDParent, 1) -- instead of above is also acceptable (see below)

// In `gdchild.cpp`
// With no given priority GDChild defaults to priority 0
bool classname::_reg = godot::GDRegistry::Register<GDChild>();
// GDREGISTER(GDChild) -- instead of above is also acceptable (see below)
```

**NOTE:** The priority does not strictly need to be 1 and 0; as long as the parent class has a higher priority than all child classes it is valid. Child classes can have the same registration priority. 

### The other stuff

Also included are some macros to help with shortening some of the "redundant" GDNative code.  These are meant to be used in your class definitions.

```c++
GDCLASS(classname, godotclass)
```
* Fills in the `GODOT_CLASS` define
* Defines and implements a default constructor as `{}`
    * The constructor is redundant for a class made for Godot as the `_init()` function should be used instead to ensure that the object is setup internally. 
* Defines the destructor
* Defines the `static void _register_methods()` function
* Defines the `void _init()` function
* Defines the `bool _reg` variable for use with GDRegistry as a `private` variable.

```c++
GDCLASS_PARENT(classname, godotclass)
```
* Extension of GDCLASS
* Sets up the class to be a parent class by defining `_init()` as virtual

```c++
GDCLASS_CHILD(childclass, parentclass)
```
* Extension of GDCLASS_PARENT
* `GODOT_SUBCLASS` is used instead of `GODOT_CLASS`
* `_init()` is **NOT** defined and by default the parent class's `_init()` is run.
    * If desired, `_init()` can be an `override` in the class and the parent `_init()` function can be called manually as needed

```c++
GDREGISTER(classname)
GDREGISTER(classname, priority)
```
* Shortcut to register the class, to be used in the `*.cpp` file for the class.  
* Expands to: 
`bool classname::_reg = godot::GDRegistry::Register<classname>();`

```c++
GDREGISTERTOOL(classname)
GDREGISTERTOOL(classname, priority)
```
* Shortcut to register the class as a  tool in the Editor, to be used in the `*.cpp` file for the class. 
* Expands to: 
`bool classname::_reg = godot::GDRegistry::RegisterTool<classname>();`

**NOTE:** The above `GDREGISTER` Macros assume that the name of the static boolean registry variable is `_reg`.  Using  the above `GDCLASS` Macro, or any of the variants, defines this for you.

### Versioning

If `GDRegistry` is used in conjunction with **[gdnative-project](https://github.com/hlfstr/gdnative-project)**, it also exposes the versioning mechanism to your code.  See **[Versioning](https://github.com/hlfstr/gdnative-project#versioning)** for more information