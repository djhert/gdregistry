#ifndef _GDNATIVEDEF_H_
#define _GDNATIVEDEF_H_

#if __has_include(<version.hpp>)
#define _VERSIONED
#include <version.hpp>
#endif

namespace godot {

#define GDCLASS(T, G)                \
	GODOT_CLASS(T, G)                \
private:                             \
	static bool _reg;                \
                                     \
public:                              \
	T(){};                           \
	~T();                            \
	static void _register_methods(); \
	void _init();

#define GDCLASS_PARENT(T, G)         \
	GODOT_CLASS(T, G)                \
private:                             \
	static bool _reg;                \
                                     \
public:                              \
	T(){};                           \
	~T();                            \
	static void _register_methods(); \
	virtual void _init();

#define GDCLASS_CHILD(T, U) \
	GODOT_SUBCLASS(T, U)    \
private:                    \
	static bool _reg;       \
                            \
public:                     \
	T(){};                  \
	~T();                   \
	static void _register_methods();

// Macros for easy additons to GDRegistry
#define _GDREG_1(T) \
	bool T::_reg = godot::GDRegistry::Register<T>();

#define _GDREG_2(T, P) \
	bool T::_reg = godot::GDRegistry::Register<T>(P);

#define _GDREGMACRO(_1, _2, _GDMAC, ...) _GDMAC

// GDREGISTER is a macro for easy addition to GDRegistry
// Can accept 1 or 2 parameters
// GDREGISTER(TYPE) -- Sets priority 0
// GDREGISTER(TYPE, PRIORITY) -- Sets priority to value
#define GDREGISTER(...)                          \
	_GDREGMACRO(__VA_ARGS__, _GDREG_2, _GDREG_1) \
	(__VA_ARGS__)

////////// Tool Registry
#define _GDREGT_1(T) \
	bool T::_reg = godot::GDRegistry::RegisterTool<T>();

#define _GDREGT_2(T, P) \
	bool T::_reg = godot::GDRegistry::RegisterTool<T>(P);

#define _GDREGTMACRO(_1, _2, _GDTMAC, ...) _GDTMAC

// GDREGISTERTOOL is a macro for easy addition to GDRegistry
// Can accept 1 or 2 parameters
// GDREGISTERTOOL(TYPE) -- Sets priority 10
// GDREGISTERTOOL(TYPE, PRIORITY) -- Sets priority to value
#define GDREGISTERTOOL(...)                         \
	_GDREGTMACRO(__VA_ARGS__, _GDREGT_2, _GDREGT_1) \
	(__VA_ARGS__)

} // namespace godot
#endif
