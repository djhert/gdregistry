#include "GDRegistry.hpp"

namespace godot {

// Create an empty instance on init
GDRegistry *GDRegistry::_instance = nullptr;

// Destructor that clears the std::vector
GDRegistry::~GDRegistry() {
	_gens.clear();
}

// instance() will return the static instance of the Registry
GDRegistry *GDRegistry::instance() {
	if (!_instance) {
		_instance = new GDRegistry;
	}
	return _instance;
}

// Run will run all of the functions in the Registry
void GDRegistry::Run() {
	// Make sure that an instance exists
	instance();
	for (auto &&x : _instance->_gens) {
		// Call each register_class(TYPE)
		x();
	}
	// After it's run, we don't need this object anymore and really
	// it shouldn't be called again.
	// If it is, then the Register function will instance a new object
	delete _instance;
}

} // namespace godot