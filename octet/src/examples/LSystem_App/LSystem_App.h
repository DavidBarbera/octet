////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.
//
#pragma once

#include "LSystem.h"
#include "Turtle2.h"
//#include "DrawTree.h"


namespace octet {
  /// Scene containing a box with octet.
  class LSystem_App : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;
	LSystem* lsystem1;
	Turtle* turtle1;
  public:
    /// this is called when we construct the class before everything is initialised.
    LSystem_App(int argc, char **argv) : app(argc, argv) {
    }



    /// this is called once OpenGL is initialized
    void app_init() {
      app_scene =  new visual_scene();
      app_scene->create_default_camera_and_lights();


	      lsystem1= new LSystem;
		  lsystem1->load_file("Tree3.ls");
		  lsystem1->init();
           turtle1 = new Turtle;
		 turtle1->generate_geometry( lsystem1, 4 );
		  //turtle1->draw_tree();
		 
		//  DrawTree* tree1 = new DrawTree;
		 // tree1->draw_tree(turtle1);
		 

    }
	

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

	  
      // update matrices. assume 30 fps.
      app_scene->update(1.0f/30);

      // draw the scene
      app_scene->render((float)vx / vy);
	  //turtle1->generate_geometry(lsystem1, 3);
	  turtle1->draw_tree();
	//  turtle1->draw_tree();
    }
  };
}
