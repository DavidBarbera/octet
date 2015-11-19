////////////////////////////////////////////////////////////////////////////////
//
// (C) Andy Thomason 2012-2014
//
// Modular Framework for OpenGLES2 rendering on multiple platforms.

#include <stdio.h>
#include <sstream>

#include "_lsystem.h"
//#include "Turtle.h"

#define PRODUCTION "F[+F]F[-F]F"
#define PRODUCTION2 "F[+F]F[-F]F[F]"
#define ANGLE 25.7
#define PI 3.1415926535897932384626433832795028841971693993751
#define RANGLE ANGLE*PI/180

namespace octet {
	class TurtleState {
		vec3 position;
		float angle;
	public:

		vec3 pos() {
			return position;
		}
		float ang() {
			return angle;
		}
		void setpostition(vec3 xyz) {
			position = xyz;
		}
		void setangle(float alpha) {
			angle = alpha;
		}
		void setstate(vec3 xyz, float alpha) {
			position = xyz;
			angle = alpha;
		}
	};

  /// Scene containing a box with octet.
	class LSystem : public app {

	
		dynarray<TurtleState*> state;

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
		/*	TurtleState* init = new TurtleState;
			init->setstate(vec3(0, 0, 0), 90);
			state.push_back(init);*/

			

			//tests();
			initTurtle();
			oneIteration();
			//turtlemoveforward(0);

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

		void tests() {

			material *bark = new material(vec4(0.686f, 0.3412f, 0, 1));
			
			mat4t mat;
			mat.loadIdentity();
			mat.rotate(90.0f, 1, 0, 0);
		    mesh_cylinder *branch = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)), mat);
			
			scene_node *node = new scene_node();
			
			app_scene->add_child(node);
			
			app_scene->add_mesh_instance(new mesh_instance(node, branch, bark));
			

		material *bark2 = new material(vec4(0.627f, 0.3803f, 0.0549f, 1));
			mesh_cylinder *branch2 = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thickness, halflength)),mat);
			scene_node *node2 = new scene_node();
			app_scene->add_child(node2);
			app_scene->add_mesh_instance(new mesh_instance(node2, branch2, bark2));
		//	node2->rotate(90, vec3(0, 1, 0));
			

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
		
		void turtlemoveforward(TurtleState *fromstate, float length, float thick) {
			material *bark = new material(vec4(0.686f, 0.3412f, 0, 1));
			mat4t mat;
			mat.loadIdentity();
			mat.rotate(90.0f, 1, 0, 0);
			mesh_cylinder *branch = new mesh_cylinder((zcylinder(vec3(0, 0, 0), thick, length)), mat);
			scene_node *node = new scene_node();
			app_scene->add_child(node);
			app_scene->add_mesh_instance(new mesh_instance(node, branch, bark));

			vec3 p = fromstate->pos();
			float a = fromstate->ang();

			vec3 toState = p + vec3(length*cos((a+90)*PI/ 180),length*sin((a+90)*PI / 180), 0);
				float toAngle = a;
				node->translate(toState);
				node->rotate(toAngle, vec3(0, 0, 1));

				toState = p + vec3(2*length*cos((a + 90)*PI / 180), 2*length*sin((a + 90)*PI / 180), 0);
				//give back next state
				fromstate->setstate(toState, toAngle);
				/*TurtleState* endstate = new TurtleState;
				endstate->setstate(toState, toAngle);
				state.push_back(endstate);*/
				//return fromstate;
		}

		TurtleState* newstate(TurtleState* turtlestate) {
			TurtleState* current = new TurtleState;
			current->setstate(turtlestate->pos(),turtlestate->ang());
			return current;
		}

		void iterate() {
			char rule[25];
			strcpy(rule, PRODUCTION);


		}
	void oneIteration() {
			TurtleState* currentstate = new TurtleState;
			currentstate->setstate(state[0]->pos(),state[0]->ang());
			
			_lsystem *ls1 = new _lsystem;
			ls1->init();
			float scale = 0.4f;
			float factor = 1;
			float distance = halflength;
			float thickbrush = thickness;
			unsigned int n = 3; ///////////
			unsigned int max = ls1->iteration[n].size();
			for (unsigned int j = 1; j < n; j++) factor = factor * scale; //calculating reduction factor according to iteration
			
			for (unsigned int i = 0; i < max; i++) {
				switch (ls1->iteration[n][i]) {
				case 'F':
				   turtlemoveforward(currentstate, factor*distance, 2.5f*factor*thickbrush);
					break;
				case '+':
					currentstate->setangle(currentstate->ang() + ANGLE);
					break;
				case '-':
					currentstate->setangle(currentstate->ang() - ANGLE);
					break;
				case'[':
					state.push_back(newstate(currentstate));
					break;
				case']':
					currentstate->setstate(state.back()->pos(), state.back()->ang());
					state.pop_back();
					break;
				} //switch
		    } //for

			//delete currentstate;
		} //oneIteration
		
		void initTurtle() {
			TurtleState* tstate = new TurtleState;
			tstate->setstate(vec3(0,-1*halflength, 0),0);
			state.push_back(tstate);
		}//initTurtle
		

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
			scene_node *node = app_scene->get_mesh_instance(0)->get_node();
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
