#pragma once

#include "LSystem.h"
#include <stdio.h>

#define PI  3.1415926535897932384626433832795028841971693993751
#define RAD 0.01745329251f

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
	    
		//TurtleState* currentstate;
		//TurtleVertex* tvertex;
		dynarray<TurtleState*> State;
		dynarray<TurtleVertex*> TurtleLines; // paired vertices, a pair of vertices for each line

	
	
		void push_line(vec3 v0, vec3 v1) {
		    TurtleVertex* vertex = new TurtleVertex;
			vertex->position = v0;
			TurtleLines.push_back(vertex);
			vertex = new TurtleVertex;
			vertex->position = v1;
			TurtleLines.push_back(vertex);

		}

		void draw_line(vec3 v0, vec3 v1) {
			glBegin(GL_LINES);
			  glColor3f(1.0, 1.0, 1.0);
			  glVertex3f(v0.x(),v0.y(),v0.z());
			  glVertex3f(v1.x(), v1.y(), v1.z());
			glEnd();
		}

		void moveForward(TurtleState *fromstate, float length) {
			vec3 p = fromstate->position;
			float a = fromstate->angle;
			float x = length*cos((a)*PI/180);
			float y = length*sin((a)*PI/180);
			float z = 0.0f;

			 
			//vec3 toState = p + vec3((float)(length*cos((a + 90)*PI / 180)), (float)(length*sin((a + 90)*PI / 180)), 0.0f);
			vec3 toState = p + vec3(x, y, z);
			float toAngle = a;
			//toState = p + vec3(2 * length*cos((a + 90)*PI / 180), 2 * length*sin((a + 90)*PI / 180), 0);
			//give back next state
			fromstate->position = toState;
			fromstate->angle = toAngle;

		//	push_line(p, toState);
		/*	TurtleVertex* vertex = new TurtleVertex;
			vertex->position = toState;
			TurtleLines.push_back(vertex);
			vertex = new TurtleVertex;
			vertex->position = v1;
			TurtleLines.push_back(vertex);*/

			//draw_line(p, toState);
			//return fromstate;
		}

		void turnLeft(TurtleState *fromstate, float alpha) {
			fromstate->angle = fromstate->angle + alpha;
		}

		void turnRight(TurtleState *fromstate, float alpha) {
			fromstate->angle = fromstate->angle - alpha;
		}

		void generate_geometry(LSystem* lsys, unsigned int n) {
			State.reset();
			TurtleLines.reset();
			initTurtle();
			TurtleState* currentstate = new TurtleState;
			currentstate->position = State[0]->position;
			currentstate->angle = State[0]->angle;

			float length = 5.0f;
			float thickness = 0.5f;
			float scale = 0.4f;
			float factor = 1;
			float distance = length;
			float thickbrush = thickness;
			unsigned int max = lsys->iteration[n].size();
			float angle = lsys->get_angle();
			char symbol;

			for (unsigned int j = 1; j < n; j++) factor = factor * scale; //calculating reduction factor according to iteration

	/*		glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLineWidth(thickness);*/

			for (unsigned int i = 0; i < max; i++) {
				symbol = lsys->iteration[n][i];
				switch (symbol) {
				case 'F':
					moveForward(currentstate, length);
					break;
				case '+':
					turnRight(currentstate, angle);
					break;
				case '-':
					turnLeft(currentstate, angle);
					break;
				case'[':
					State.push_back(newstate(currentstate));
					break;
				case']':
					currentstate->position = State.back()->position;
					currentstate->angle = State.back()->angle;
					State.pop_back();
					break;
				} //switch
			} //for
			//delete currentstate;
		} //generate_turtle_geometry

		void initTurtle() {
			TurtleState* tstate = new TurtleState;
			tstate->position = vec3(0, 0, 0);
			tstate->angle = 90;

		/*	TurtleState tstate;
			tstate.position= vec3(0, 0, 0);
			tstate.angle = 0;
			State.reset();*/
			State.push_back(tstate);
		}//initTurtle

		TurtleState* newstate(TurtleState* turtlestate) {
			TurtleState* current = new TurtleState;
			current->position = turtlestate->position;
			current->position = turtlestate->angle;
			return current;
		}


		void draw_tree() {
			glClearColor(0, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glLineWidth(0.1f);
			glBegin(GL_LINES);

			for (unsigned int i = 0; i < TurtleLines.size(); i++) {
				glColor3f(1.f, 0.f, 0.f);
				glVertex3f(TurtleLines[i]->position.x(),TurtleLines[i]->position.y(),TurtleLines[i]->position.z());
			}

			glEnd();
		}

	};
}