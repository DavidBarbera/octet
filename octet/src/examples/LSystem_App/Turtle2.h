#pragma once

#include "LSystem.h"
#include <stdio.h>

#define PI  3.1415926535897932384626433832795028841971693993751
#define RAD 0.01745329251f
#define BOTTOM_SCREEN -14

namespace octet {

	class Turtle : public resource {
	public:
		struct  TurtleState {
			vec3 position;
			float angle;
		};

		struct TurtleVertex : public resource {
			vec3 position;
		};

		TurtleState currentstate;
		dynarray<TurtleState> State;
		dynarray<vec3> TurtleLines; // paired vertices, a pair of vertices for each line



		void remember_line(vec3 v0, vec3 v1) {
			TurtleLines.push_back(v0);
			TurtleLines.push_back(v1);

		}

		void draw_line(vec3 v0, vec3 v1) {
			glBegin(GL_LINES);
			glColor3f(1.0, 1.0, 1.0);
			glVertex3f(v0.x(), v0.y(), v0.z());
			glVertex3f(v1.x(), v1.y(), v1.z());
			glEnd();
		}

		void moveForward(float length) {
			vec3 p = currentstate.position;
			float a = currentstate.angle;

			float x = length*(cos((a+90)*PI / 180));
			float y = length*(sin((a+90)*PI / 180));
			float z = 0.0f;


			vec3 toState = p + vec3(x, y, z);
			float toAngle = a;
			currentstate.position = toState;
			currentstate.angle = toAngle;

		    remember_line(p, toState);
		}

		void turnLeft(float alpha) {
			currentstate.angle = currentstate.angle + alpha;
		}

		void turnRight(float alpha) {
			currentstate.angle = currentstate.angle - alpha;
		}

		void generate_geometry(LSystem* lsys, unsigned int n) {
			State.reset();
			TurtleLines.reset();
			initTurtle();
			currentstate.position = State[0].position;
			currentstate.angle = State[0].angle;

			float angle = lsys->get_angle();
			float length = lsys->get_length();
			float thickness = lsys->get_thickness();

			float scale = 0.4f;
			float factor = 1;

			unsigned int max = lsys->iteration[n].size();

			char wordsymbol;

			for (unsigned int j = 1; j < n; j++) factor = factor * scale; //calculating reduction factor according to iteration


			for (unsigned int i = 0; i < max; i++) {
				wordsymbol = lsys->iteration[n][i];
				switch (wordsymbol) {
				//case '1':
				case '0':
					moveForward( factor*length );
					break;
				case '+':
					turnLeft( angle );
					break;
				case '-':
					turnRight(angle);
					break;
				case'[':
					State.push_back(currentstate);
					break;
				case']':
					currentstate.position = State.back().position;
					currentstate.angle = State.back().angle;
					State.pop_back();
					break;
				} //switch
			} //for
		} //generate_turtle_geometry

		void initTurtle() {
			TurtleState currentstate;
			currentstate.position= vec3(0, BOTTOM_SCREEN, 0);
			currentstate.angle = 0;
			State.push_back(currentstate);
		}//initTurtle


		void draw_tree() {
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLineWidth(0.1f);
			glBegin(GL_LINES);

			for (unsigned int i = 0; i < TurtleLines.size(); i++) {
				glColor3f(1.f, 0.f, 0.f);
				glVertex3f(TurtleLines[i].x(), TurtleLines[i].y(), TurtleLines[i].z());
			}

			glEnd();
		}

	};
}