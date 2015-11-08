/////////////////////////////////////////////////////////////////////////////////////////////
// a messi project to test assumptions

#pragma warning(disable : 4267)
#define OCTET_BULLET 1

#include "../../../octet.h"

#include "PhysicsMess.h"

/// Create a box with octet
int main(int argc, char **argv) {
	// set up the platform.
	octet::app::init_all(argc, argv);

	// our application.
	octet::PhysicsMess app(argc, argv);
	app.init();

	// open windows
	octet::app::run_all_apps();
}