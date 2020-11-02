#include "gdregistry.hpp"

namespace godot {

// Destructor that clears the std::vector
GDRegistry::~GDRegistry() {
	_gens.clear();
}

bool GDRegistry::_regSort(const reg &a, const reg &b) {
	return a.priority > b.priority;
}

// instance() will return the static instance of the Registry
GDRegistry &GDRegistry::instance() {
	static GDRegistry _instance;
	return _instance;
}

// Run will run all of the functions in the Registry
void GDRegistry::Run() {
	// Make sure that an instance exists
	instance();
	// Sort the _gens vector based on highest priority
	std::sort(instance()._gens.begin(), instance()._gens.end(), _regSort);
	for (auto &&x : instance()._gens) {
		// Call each register_class<TYPE>
		x.f();
	}
}

} // namespace godot