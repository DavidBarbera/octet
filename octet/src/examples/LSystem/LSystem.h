////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.

#include <stdio.h>

#define PRODUCTION "F[+F]F[-F]F"
#define ANGLE 45
#define PI 3.1415926535897932384626433832795028841971693993751
#define RANGLE ANGLE*PI/180

namespace octet {
  /// Scene containing a box with octet.
	class LSystem : public app {
		// scene for drawing box
		ref<visual_scene> app_scene;

		//- mouse_look mouse_look_helper;
		ref<camera_instance> the_camera;
		mouse_ball mcamera;

		// helper for drawing text
		ref<text_overlay> overlay;
		// text mesh object for overlay.
		ref<mesh_text> text;

		dynarray<ref<scene_node>> branches;

		float halflength=2;
		float thickness = 0.10f;

	public:
		/// this is called when we construct the class before everything is initialised.
		LSystem(int argc, char **argv) : app(argc, argv) {
		}

		void tests() {

			material *bark = new material(vec4(0.686f, 0.3412f, 0, 1));
			material *bark2 = new material(vec4(0.627f, 0.3803f, 0.0549f, 1));
			mat4t mat;
			mat.loadIdentity();
			mat.rotate(90.0f, 1, 0, 0);
			mesh_cylinder *branch = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			mesh_cylinder *branch2 = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			scene_node *node = new scene_node();
			scene_node *node2 = new scene_node();
			app_scene->add_child(node);
			app_scene->add_child(node2);
			app_scene->add_mesh_instance(new mesh_instance(node, branch, bark));
			app_scene->add_mesh_instance(new mesh_instance(node2, branch2, bark2));

			//position the branches
			node = app_scene->get_mesh_instance(0)->get_node();


			node2 = app_scene->get_mesh_instance(1)->get_node();



			node2->translate(vec3(halflength*cos((ANGLE + 90)*PI / 180), halflength + halflength*sin((ANGLE + 90)*PI / 180), 0));
			node2->rotate(ANGLE, vec3(0, 0, 1));

			mesh_cylinder *branch3 = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			scene_node *node3 = new scene_node();
			app_scene->add_child(node3);
			app_scene->add_mesh_instance(new mesh_instance(node3, branch3, bark));
			node3 = app_scene->get_mesh_instance(2)->get_node();

			node3->translate(vec3(0, 2 * halflength, 0));

			mesh_cylinder *branch4 = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			scene_node *node4 = new scene_node();
			app_scene->add_child(node4);
			app_scene->add_mesh_instance(new mesh_instance(node4, branch4, bark));
			node4 = app_scene->get_mesh_instance(3)->get_node();

			node4->translate(vec3(halflength*cos((-1 * ANGLE + 90)*PI / 180), 3 * halflength + halflength*sin((-1 * ANGLE + 90)*PI / 180), 0));
			node4->rotate(-1 * ANGLE, vec3(0, 0, 1));

			mesh_cylinder *branch5 = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			scene_node *node5 = new scene_node();
			app_scene->add_child(node5);
			app_scene->add_mesh_instance(new mesh_instance(node5, branch5, bark));
			node5 = app_scene->get_mesh_instance(4)->get_node();

			node5->translate(vec3(0, 4 * halflength, 0));
					
		}//tests
		
		void turtlemoveforward()
		void oneIteration() {
			char Turtlecommands[25];
			
			strcpy(Turtlecommands, PRODUCTION);

			int max = sizeof(Turtlecommands);

			for (int i = 0; i < max; i++) {
				switch (Turtlecommands[i]) {
				case 'F':
					turtlemoveforward();
					break;
				case '+':
				case '-':
				case'[' :
				case']':


				}

			}//for

		}//oneIteration
			/// this is called once OpenGL is initialized
		void app_init() {
			//-	mouse_look_helper.init(this, 200.0f / 360.0f, false);
			mcamera.init(this, 1, 100);

			app_scene = new visual_scene();
			app_scene->create_default_camera_and_lights();

			the_camera = app_scene->get_camera_instance(0);
			the_camera->get_node()->translate(vec3(0, 4, 0));
			the_camera->set_far_plane(10000);
			//the_camera->set_near_plane(0.001);

			//tests();
			
			oneIteration();

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

			scene_node *camera = the_camera->get_node();
			//mat4t &camera = camera_node->access_nodeToParent();
			//- mouse_look_helper.update(camera_to_world);

			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);

			// tumble the branch  (there is only one mesh instance)
			scene_node *node = app_scene->get_mesh_instance(1)->get_node();
			// node->rotate(1, vec3(0, 0, 1));
			// node->rotate(1, vec3(1, 1, 0));
			//vec3 pos = node->get_position();




			// write some text to the overlay
			char buf[3][256];
			 mat4t &mx = node->access_nodeToParent();

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

			//Move the camera with the mouse
			mcamera.update(app_scene->get_camera_instance(0)->get_node()->access_nodeToParent());





		}
  };
}
