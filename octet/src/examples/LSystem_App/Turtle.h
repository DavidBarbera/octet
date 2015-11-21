#include "LSystem.h"
#include <stdio.h>

#define PI 3.1415926535897932384626433832795028841971693993751


namespace octet {
	class Turtle : public resource {
	  public:

		struct  TurtleState {
		vec3 position;
		float angle;
	    };

		struct TurtleVertex {
			vec3 position;
		};
	
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

		void moveForward(TurtleState *fromstate, float length) {
			vec3 p = fromstate->position;
			float a = fromstate->angle;


			vec3 toState = p + vec3(length*cos((a + 90)*PI / 180), length*sin((a + 90)*PI / 180), 0);
			float toAngle = a;
			//toState = p + vec3(2 * length*cos((a + 90)*PI / 180), 2 * length*sin((a + 90)*PI / 180), 0);
			//give back next state
			fromstate->position = toState;
		    fromstate->angle = toAngle;

			push_line(p, toState);
			//return fromstate;
		}
		
		void turnLeft(TurtleState *fromstate, float alpha) {
			fromstate->angle = fromstate->angle + alpha;		
		}

		void turnRight(TurtleState *fromstate, float alpha) {
			fromstate->angle = fromstate->angle - alpha;
		}

		void generate_turtle_geometry(lsystem_* lsys, unsigned int n) {
			initTurtle();
			TurtleState* currentstate = new TurtleState;
			currentstate->position = State[0]->position;
			currentstate->angle = State[0]->angle;

			float length = 0.5f;
			float thickness = 0.1f;
			float scale = 0.4f;
			float factor = 1;
			float distance = length;
			float thickbrush = thickness;
			unsigned int max = lsys->iteration[n].size();
			float angle = lsys->get_angle();

			for (unsigned int j = 1; j < n; j++) factor = factor * scale; //calculating reduction factor according to iteration

			for (unsigned int i = 0; i < max; i++) {
				switch (lsys->iteration[n][i]) {
				case 'F':
					moveForward(currentstate, factor*distance);
					break;
				case '+':
					turnRight(currentstate,angle);
					break;
				case '-':
					turnLeft(currentstate,angle);
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
		 delete currentstate;
		} //generate_turtle_geometry

		void initTurtle() {
			TurtleState* tstate = new TurtleState;
			tstate->position = vec3(0,0,0);
			tstate->angle = 0;
			State.push_back(tstate);
		}//initTurtle

		TurtleState* newstate(TurtleState* turtlestate) {
			TurtleState* current = new TurtleState;
			current->position = turtlestate->position;
			current->position = turtlestate->angle;
			return current;
	};

}