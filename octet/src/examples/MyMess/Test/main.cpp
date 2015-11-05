////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
// Testing how to make new projects with octet
//
// Always keep track of octet.h, add ../../ as needed
// your project will be a class of octet

#define OCTET_BULLET 1

#include "../../../octet.h"

#include "Test.h"

/// Create a box with octet
int main(int argc, char **argv) {
  // set up the platform.
  octet::app::init_all(argc, argv);

  // our application.
  octet::Test app(argc, argv);
  app.init();

  // open windows
  octet::app::run_all_apps();
}


