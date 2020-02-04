#ifndef _GDREGISTRY_HPP_
#define _GDREGISTRY_HPP_

#include <Godot.hpp>
#include <vector>

namespace godot {

class GDRegistry {
public:
	// Register is a Template Function that will place the object in the Registry
	// It stores a pointer to the godot::register_class function to initialize
	// the class.  Should be used in a static context in the class that uses it
	template <typename T>
	static bool Register() {
		GDRegistry::instance()->_gens.push_back(godot::register_class<T>);
		return true;
	};

	// Run should only be called once on init, but will not cause an issue if called again
	static void Run();

private:
	// Follow the Singleton pattern
	GDRegistry(){};
	GDRegistry(const GDNRegistry &){};
	~GDRegistry();

	// static instances for the Singleton
	static GDRegistry *instance();
	static GDRegistry *_instance;

	// std::vector of void functions
	std::vector<void (*)()> _gens;
};

} // namespace godot
#endif
