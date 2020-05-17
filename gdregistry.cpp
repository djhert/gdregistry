#include "gdregistry.hpp"

namespace godot {

// Create an empty instance on init
GDRegistry *GDRegistry::_instance = nullptr;

// Destructor that clears the std::vector
GDRegistry::~GDRegistry() {
	_gens.clear();
}

bool GDRegistry::_regSort(const reg &a, const reg &b) {
	return a.priority > b.priority;
}

// instance() will return the static instance of the Registry
GDRegistry *GDRegistry::instance() {
	if (!_instance)
		_instance = new GDRegistry;

	return _instance;
}

// Run will run all of the functions in the Registry
void GDRegistry::Run() {
	// Make sure that an instance exists
	instance();
	// Sort the _gens vector based on highest priority
	std::sort(_instance->_gens.begin(), _instance->_gens.end(), _regSort);
	for (auto &&x : _instance->_gens) {
		// Call each register_class<TYPE>
		x.f();
	}
#ifndef _DEBUG
	// IF in production, let's just delete our _instance as it is no longer needed
	delete _instance;
#endif
}

} // namespace godot

// Native Init function defined by Godot
extern "C" void GDN_EXPORT godot_gdnative_init(godot_gdnative_init_options *o) {
	godot::Godot::gdnative_init(o);
}

// Native Terminate function defined by Godot
extern "C" void GDN_EXPORT godot_gdnative_terminate(godot_gdnative_terminate_options *o) {
	godot::Godot::gdnative_terminate(o);
}

// GDNative entry point defined by Godot, runs the Registry
extern "C" void GDN_EXPORT godot_nativescript_init(void *handle) {
	godot::Godot::nativescript_init(handle);
	godot::GDRegistry::Run();
}