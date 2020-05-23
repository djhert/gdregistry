#ifndef _GDREGISTRY_HPP_
#define _GDREGISTRY_HPP_

#include <Godot.hpp>
#include <algorithm>
#include <memory>
#include <vector>

#include "gdnativedef.hpp"

namespace godot {

class GDRegistry {

private:
	// reg is the storage class to hold the functions
	struct reg {
		void (*f)();
		int priority;
	};
	// _regSort is used as the sorting function for the Vector
	static bool _regSort(const reg &a, const reg &b);

public:
	// Register will place the object in the Registry
	// It stores a pointer to the godot::register_class function to initialize the class
	// Should be used in a static context in the class that uses it
	// Optional priority parameter specifies order of registration, highest to lowest
	// Default priority of 0
	template <typename T>
	static bool Register(const int &priority = 0) {
		GDRegistry::instance()->_gens.push_back({ godot::register_class<T>, priority });
		return true;
	};

	// RegisterTool will place the object in the Registry
	// It stores a pointer to the godot::register_tool_class function to initialize the class.
	// Should be used in a static context in the class that uses it
	// Optional priority parameter specifies order of registration, highest to lowest
	// Default priority of 10
	template <typename T>
	static bool RegisterTool(const int &priority = 10) {
		GDRegistry::instance()->_gens.push_back({ godot::register_tool_class<T>, priority });
		return true;
	};

	// Run should only be called once on init, but will not cause an issue if called again
	static void Run();

private:
	// Follow the Singleton pattern
	GDRegistry(){};
	GDRegistry(const GDRegistry &){};
	~GDRegistry();

	// static instances for the Singleton
	static GDRegistry *instance();
	static GDRegistry *_instance;

	// std::vector of reg struct
	std::vector<reg> _gens;
};

} // namespace godot
#endif
