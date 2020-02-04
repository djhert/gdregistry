#include <Godot.hpp>

#include "gdregistry.hpp"

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