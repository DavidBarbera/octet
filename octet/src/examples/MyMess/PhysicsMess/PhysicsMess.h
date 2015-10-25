////////////////////////////////////////////////////////////////////////////////
//
// testing assumptions
//
namespace octet {
	/// Scene containing a box with octet.
	class PhysicsMess : public app {
		// scene for drawing box
		ref<visual_scene> app_scene;

	public:
		PhysicsMess(int argc, char **argv) : app(argc, argv) {
		}

		~PhysicsMess() {
		}

		/// this is called once OpenGL is initialized
		void app_init() {
			app_scene = new visual_scene();
			app_scene->create_default_camera_and_lights();
			app_scene->get_camera_instance(0)->get_node()->translate(vec3(0, 4, 0));

			material *red = new material(vec4(1, 0, 0, 1));
			material *green = new material(vec4(0, 1, 0, 1));
			material *blue = new material(vec4(0, 0, 1, 1));
			//different color
			material *colorX = new material(vec4(0, 1, 1, 1));

			mat4t mat;
			mat.translate(-1, 7, 0);
			app_scene->add_shape(mat, new mesh_sphere(vec3(2, 3, 2), 2), colorX, true);
			//another sphere
			mat.loadIdentity();
			mat.translate(0, 5, 0);
			app_scene->add_shape(mat, new mesh_sphere(vec3(2, 2, 2), 2), blue, true);

			mat.loadIdentity();
			mat.translate(0, 5, 0);
			app_scene->add_shape_ndHinge(mat, new mesh_box(vec3(1.5, 1.5, 0.25)), red, true);

			mat.loadIdentity();
			mat.translate(3, 6, 0);
			app_scene->add_shape(mat, new mesh_cylinder(zcylinder(vec3(0, 0, 0), 2, 4)), blue, true);

			// ground
			mat.loadIdentity();
			mat.translate(0, -1, 0);
			app_scene->add_shape(mat, new mesh_box(vec3(200, 1, 200)), green, false);

	//constraints

			// app_scene->world->getGravity;



		}

		/// this is called to draw the world
		void draw_world(int x, int y, int w, int h) {
			int vx = 0, vy = 0;
			get_viewport_size(vx, vy);
			app_scene->begin_render(vx, vy);

			// update matrices. assume 30 fps.
			app_scene->update(1.0f / 30);

			// draw the scene
			app_scene->render((float)vx / vy);
		}
	};
}
