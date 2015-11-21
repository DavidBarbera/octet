// the LSystem itself
#include <stdio.h>
//#include "Turtle.h"

#define _RULE_ "F[+F]F[-F]F"
#define _W_ "F"
#define _N_ 5
#define _ANGLE_ 25

namespace octet {
	class  LSystem : public octet::resource {

		char rule[5][255];
		char word[255];
		//dynarray<char*> word_ptr;
		unsigned int max_iterations;
		float angle;
	public:
		float get_angle() {
			return angle;
		}
		// It will be initialized with a file, once tested
		dynarray<dynarray<char>> iteration;
		//dynarray<dynarray<char*>> iteration_ptr;
		LSystem() {}

		void init() {
			strcpy(rule[0], _RULE_);
			strcpy(word, _W_);
			max_iterations = _N_;
			angle = _ANGLE_;

			iteration.resize(max_iterations);

			iteration[0].reserve(strlen(word));
			for (int i = 0; i < strlen(word); ++i)
				iteration[0].push_back(word[i]);
			//debug
			printf("\n");
			for (unsigned int i = 0; i < iteration[0].size(); ++i)
				printf("%c", iteration[0][i]);
			printf("\n%i\n", iteration[0].size());

			// generating all iterations
			int k = 0; //debug
			int l = 0; //debug
			int rule_length = strlen(rule[0]);
			for (unsigned int n = 1; n < max_iterations; ++n) {
				unsigned int space = space_needed(0, n - 1);
				printf("\n%i\n", space); //debug
				unsigned int prev_iteration_length = iteration[n - 1].size();
				iteration[n].reserve(space);
				for (unsigned int i = 0; i < prev_iteration_length; ++i) {
					if (iteration[n - 1][i] == 'F') {

						for (int j = 0; j < rule_length; ++j) {
							iteration[n].push_back(rule[0][j]); ++k;
							printf("%c", rule[0][j]); //debug
						}//for j
					}
					else {
						iteration[n].push_back(iteration[n - 1][i]); ++k; ++l;
						printf("%c", iteration[n - 1][i]); //debug
					} //if-else
				} //for i
				printf("\niteration:%i, size:%i, k=%i, l=%i\n rule_length:%i\n", n, iteration[n].size(), k, l, rule_length); //debug
			} //for n

		} //init()

		int space_needed(int num_rule, int prev_iteration) {
			unsigned int size_rule = strlen(rule[num_rule]);
			unsigned int replaceable_symbols_in_prev_iteration = 0;
			unsigned int total_symbols_in_prev_iteration = iteration[prev_iteration].size();

			for (unsigned int i = 0; i < total_symbols_in_prev_iteration; ++i)
				if (iteration[prev_iteration][i] == 'F') replaceable_symbols_in_prev_iteration++;


			return (size_rule*replaceable_symbols_in_prev_iteration + total_symbols_in_prev_iteration - replaceable_symbols_in_prev_iteration);
		} //space_needed()

	};

}