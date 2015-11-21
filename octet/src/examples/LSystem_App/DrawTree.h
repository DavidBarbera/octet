#pragma once

#include "Turtle.h"

namespace octet {
	class DrawTree {
		float brush;
		
	public:
		//dynarray<TurtleVertex*>  lines;

		DrawTree() {
			brush = 0.1f;
		}
	/*	DrawTree(Turtle* turtle, float thickness) {
			brush = thickness;
			lines = turtle->TurtleLines;
		}*/
		/*void draw_tree() {
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLineWidth(brush);
			glBegin(GL_LINES);

			for (int i = 0; i < lines.size(); i++) {
					glColor3f(1,0,0);
					glVertex3f(lines[i]->position.x(),
						lines[i]->position.y(),
						lines[i]->position.z() );
				}
			
			glEnd();
		}
		*/


	};

}