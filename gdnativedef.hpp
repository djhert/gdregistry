#ifndef _GDNATIVEDEF_H_
#define _GDNATIVEDEF_H_

namespace godot {

#define GDCLASS(T, G)                \
	GODOT_CLASS(T, G)                \
public:                              \
	T(){};                           \
	~T();                            \
	static void _register_methods(); \
	void _init();                    \
                                     \
private:                             \
	static bool _reg;

#define GDCLASS_PARENT(T, G)         \
	GODOT_CLASS(T, G)                \
public:                              \
	T(){};                           \
	~T();                            \
	static void _register_methods(); \
	void _init();                    \
	virtual void Init();             \
                                     \
private:                             \
	static bool _reg;

#define GDCLASS_CHILD(T, U)          \
	GODOT_CLASS(T, U)                \
public:                              \
	T(){};                           \
	~T();                            \
	static void _register_methods(); \
	void _init() { U::_init(); };    \
                                     \
private:                             \
	static bool _reg;

#define GDREGISTER(T) \
	bool T::_reg = godot::GDRegistry::Register<T>();

} // namespace godot
#endif
