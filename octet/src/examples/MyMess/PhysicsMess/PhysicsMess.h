////////////////////////////////////////////////////////////////////////////////
//
// testing assumptions
//

#include <iostream>
#include <fstream>
#include <vector>

#define FILE "../../../examples/MyMess/PhysicsMess/file.csv"
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
			mat.translate(0, 15, 0);
			app_scene->add_shape(mat, new mesh_sphere(vec3(0, 0, 0), 1), colorX, true);
			//another sphere
			mat.loadIdentity();
			mat.translate(3, 7, 0);
			app_scene->add_shape(mat, new mesh_sphere(vec3(0, 0, 0), 2), blue, true);

			mat.loadIdentity();
			mat.translate(0, 4, 0);
			app_scene->add_shape(mat, new mesh_box(vec3(1.5, 1.5, 0.25)), red, true);

			mat.loadIdentity();
			mat.translate(2, 6, 0);
			app_scene->add_shape(mat, new mesh_cylinder(zcylinder(vec3(0, 0, 0), 1, 4)), blue, true);

			// ground
			mat.loadIdentity();
			mat.translate(0, -1, 0);
			app_scene->add_shape(mat, new mesh_box(vec3(200, 1, 200)), green, false);

			app_scene->add_Hinge();
			app_scene->add_Spring();
			
			//read_file();
			
	//constraints
			//whatever
			// app_scene->world->getGravity;



		}
		struct Object {
			int id;
			char shape[25];
			vec3 dimension;
			vec3 position;
			vec3 color;
					};
		int read_file(){
			//std::vector<std::string> names;
			//std::vector<Object> objects[20];
			Object object;

			std::ifstream is(FILE);
			//printf("hello hey");
			if (is.bad()) return 1;


			// store the line here
			char buffer[2048];
			char field[25];

			// loop over lines
			
			while (!is.eof()) {
				is.getline(buffer, sizeof(buffer));
				//printf("\n%s\n",buffer);
				

				// loop over columns
				char *b = buffer;
				int i = 0;
				for (int col = 0;col<=10; col++) {
					char *e = b;
						
					while (*e != 0 && *e != ';') {
						field[i]=b[i];
						++e; i++;
					}
					field[i] = '\0';
					// now b -> e contains the chars in a column
					switch (col) {
						case 0:      //names.emplace_back(b, e);
							
						object.id = atoi(field);
						printf("%i\n", object.id);
						break;
						case 1: 
							strcpy(object.shape, field);
							printf("%s\n", object.shape);
							break;
						default:
							break;
							
					}

					if (*e != ',') break;
					b = e + 1;
				}
				// add shapes here
				}
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
