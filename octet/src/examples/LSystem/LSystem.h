////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.

#include <stdio.h>

#define PRODUCTION "F[+F]F[-F]F"
#define DELTA 25.7


namespace octet {
  /// Scene containing a box with octet.
  class LSystem : public app {
    // scene for drawing box
    ref<visual_scene> app_scene;
	mouse_look mouse_look_helper;
	ref<camera_instance> the_camera;
	// helper for drawing text
	ref<text_overlay> overlay;

	// text mesh object for overlay.
	ref<mesh_text> text;
  public:
    /// this is called when we construct the class before everything is initialised.
    LSystem(int argc, char **argv) : app(argc, argv) {
    }

    /// this is called once OpenGL is initialized
    void app_init() {
		mouse_look_helper.init(this, 200.0f / 360.0f, false);
      app_scene =  new visual_scene();
      app_scene->create_default_camera_and_lights();
	  the_camera = app_scene->get_camera_instance(0);
	  the_camera->get_node()->translate(vec3(0, 4, 0));
	  the_camera->set_far_plane(10000);

      material *red = new material(vec4(1, 0, 0, 1));
      mesh_box *box = new mesh_box(vec3(0.1f,4.0f,0.1f));
      scene_node *node = new scene_node();
      app_scene->add_child(node);
      app_scene->add_mesh_instance(new mesh_instance(node, box, red));
	 // printf("%s", PRODUCTION);

	 // vec3 pos= app_scene->get_mesh_instance(0)->get_node()->get_position();

	  //printf("( %i , %i , %i )", pos.x(), pos().y(), pos.()z);

	  // create the overlay
	  overlay = new text_overlay();

	  // get the default font.
	  bitmap_font *font = overlay->get_default_font();

	  // create a box containing text (in pixels)
	  aabb bb(vec3(64.5f, -200.0f, 0.0f), vec3(256, 64, 0));
	  text = new mesh_text(font, "", &bb);

	  // add the mesh to the overlay.
	  overlay->add_mesh_text(text);

    }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {
      int vx = 0, vy = 0;
      get_viewport_size(vx, vy);
      app_scene->begin_render(vx, vy);

	  scene_node *camera_node = the_camera->get_node();
	  mat4t &camera_to_world = camera_node->access_nodeToParent();
	  mouse_look_helper.update(camera_to_world);

      // update matrices. assume 30 fps.
      app_scene->update(1.0f/30);

      // draw the scene
      app_scene->render((float)vx / vy);

      // tumble the box  (there is only one mesh instance)
      scene_node *node = app_scene->get_mesh_instance(0)->get_node();
      node->rotate(1, vec3(1, 0, 0));
     // node->rotate(1, vec3(1, 1, 0));


	 // write some text to the overlay
	  char buf[3][256];
	  const mat4t &mx = node->access_nodeToParent();

	  text->clear();

	  text->format(
		  "matrix x: %s\n"
		  "matrix y: %s\n"
		  "matrix z: %s\n",
		  mx.x().toString(buf[0], sizeof(buf[0])),
		  mx.y().toString(buf[1], sizeof(buf[1])),
		  mx.z().toString(buf[2], sizeof(buf[2]))
		  );

	  // convert it to a mesh.
	  text->update();

	  // draw the text overlay
	  overlay->render(vx, vy);


	}
  };
}
