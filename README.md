# ![Godot](https://raw.githubusercontent.com/hlfstr/gdnative-project/master/icon.png) GDNative Registry
**...and other helpful GDNative stuff too!**

## Usage
Include this project in your source tree for your GDNative project and compile it with your source. 

#### Example:

Include this as a `git` submodule in a subdirectory of your source tree, example: 

```bash
$ git submodule add https://github.com/hlfstr/gdutil source/include/gdutil
```
**File Tree:**
```
project-name/
├── project/ # Godot project
└── source/
    ├── include/ # Source that needs to be compiled with the library 
    |   └── gdregistry # GDNative Registry!
    └── # C++ GDNative Source goes here
```

For an easy-to-use setup, see my other project which includes this: **[gdnative-project](https://github.com/hlfstr/gdnative-project)**

### How it works

GDNative Registry (gdregistry) is a Singleton that allows you to store the **_register_class_** function calls for your custom GDNative classes that you will run.  Normally, Godot requires you to list all of the functions in the **_godot_nativescript_init_** function that you will be using.  This can be cumbersome when you have many classes that you need to register.  Using this, to register a class you need to have a `static bool` defined in your C++ class and initialize it the following way in your `.cpp` file:

```c++
bool classname::_reg = godot::GDRegistry::Register<classname>();
```

The included `gdlib.cpp` file will setup GDNative for you, as well as run the Registrations when Godot starts.  This means just include this project and work on YOUR code!

#### The other stuff

Also included are some `#define` to help with shortening some of the "redundant" GDNative code.  

```c++
GDCLASS(classname, godotclass)
```
* Fills in the `GODOT_CLASS` define
* Defines and implements a default constructor (the constructor is never used in GDNative)
* Defines the deconstructor
* Defines the `_register_methods()` function
* Defines the `_init()` function
* Defines the `_reg` bool for use with gdregistry

```c++
GDCLASS_PARENT(classname, godotclass)
```
* Fills in the `GODOT_CLASS` define
* Defines and implements a default constructor (the constructor is never used in GDNative)
* Defines the deconstructor
* Defines the `_register_methods()` function
* Defines the `_init()` function
* Defines the `_reg` bool for use with gdregistry
* Sets up the class to be a "parent class" by defining `virtual void Init()`

```c++
GDCLASS_CHILD(childclass, parentclass)
```
* Fills in the `GODOT_CLASS` define
* Defines and implements a default constructor (the constructor is never used in GDNative)
* Defines the deconstructor
* Defines the `_register_methods()` function
* Defines the `_init()` function and implements it to run the parent `_init()` function.
    * To have the child class run an `init`, override the `Init()` function from the parent class and be sure the parent's `_init()` function calls `Init()`
* Defines the `_reg` bool for use with gdregistry

```c++
GDREGISTER(classname)
```
* Shortcut to register the class, to be used in the `*.cpp` file for the class.  The same as the `bool classname::_reg = godot::GDRegistry::Register<classname>();`
