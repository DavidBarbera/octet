// the LSystem itself
#pragma once
#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>

//#include "Turtle.h"

#define _RULE_ "F[+F]F[-F]F"

#define _W_ "F"
#define _N_ 3
#define _ANGLE_ 25.7
#define _NUM_RULES_ 1

namespace octet {
	class LSystem : public resource {

		char rule[5][255];
		char word[255];
		char symbol[5][255];
		//dynarray<char*> word_ptr;
		unsigned int max_iterations;
		float angle;
		unsigned int num_symbols;
		unsigned int num_rules;
	public:
	/*	LSystem() {
			strcpy(rule[0], _RULE_);
			strcpy(word, _W_);
			max_iterations = _N_ + 1;
			angle = _ANGLE_;
			num_rules = _NUM_RULES_;
		}*/
	
		// It will be initialized with a file, once tested
		dynarray<dynarray<char>> iteration;
		//LSystem() {}

	

		void init() {
		/*	strcpy(rule[0], _RULE_);
			strcpy(word, _W_);
			max_iterations = _N_+1;
			angle = _ANGLE_;*/

			iteration.resize(max_iterations+1);

			iteration[0].reserve((unsigned int)strlen(word));
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
			unsigned int rule_length = strlen(rule[0]);
			for (unsigned int n = 1; n <= max_iterations; ++n) {
				unsigned int space = space_needed(0, n - 1);
				printf("\n%i\n", (int)space); //debug
				unsigned int prev_iteration_length = iteration[n - 1].size();
				iteration[n].reserve(space);
				for (unsigned int i = 0; i < prev_iteration_length; ++i) {
					if (iteration[n - 1][i] == 'F') {

						for (unsigned int j = 0; j < rule_length; ++j) {
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

		unsigned int space_needed(int num_rule, int prev_iteration) {
			unsigned int size_rule = strlen(rule[num_rule]);
			unsigned int replaceable_symbols_in_prev_iteration = 0;
			unsigned int total_symbols_in_prev_iteration = iteration[prev_iteration].size();

			for (unsigned int i = 0; i < total_symbols_in_prev_iteration; ++i)
				if (iteration[prev_iteration][i] == 'F') replaceable_symbols_in_prev_iteration++;


			return (size_rule*replaceable_symbols_in_prev_iteration + total_symbols_in_prev_iteration - replaceable_symbols_in_prev_iteration);
		} //space_needed()

		unsigned int get_max_iteration() {
			return max_iterations;
		}

		float get_angle() {
			return angle;
		}

		bool load_file(string filename) {
			//std::ifstream is("../../assets/LSystems/Tree1.ls");
			std::ifstream is(filename);

			if (is.bad()) return 1;

			// store the line here
			char buffer[255];
			int commandcount = 0;
			int fieldcount = 0;

			// loop over lines
			while (!is.eof()) {
				is.getline(buffer, sizeof(buffer));
				switch (commandcount) {
				case 0:
					commandcount++;
					break;
				case 1:
					max_iterations = atoi(buffer);
					commandcount++;
					break;
				case 2:
					commandcount++;
					break;
				case 3:
					angle = atof(buffer);
					commandcount++;
					break;
				case 4:
					commandcount++;
					break;
				case 5:
					if (fieldcount == 0) {
						num_symbols = atoi(buffer);
						fieldcount = num_symbols;
					} 
					commandcount++;
					break;
				case 6:
					strcpy(symbol[num_symbols - fieldcount], buffer);
					if (fieldcount > 1) {
						commandcount--;
						fieldcount--;
					} else if (fieldcount == 1) fieldcount = 0;
					commandcount++;
					break;
				case 7:
					commandcount++;
					break;
				case 8:
					strcpy(word, buffer);
					commandcount++;
					break;
				case 9:
					commandcount++;
					break;
				case 10:
					if (fieldcount == 0) {
						num_rules = atoi(buffer);
						fieldcount = num_rules;
					}
					commandcount++;
					break;
				case 11:
					strcpy(rule[num_rules - fieldcount], buffer);
					if (fieldcount > 1) {
						commandcount--;
						fieldcount--;
					}
					else if (fieldcount == 1) fieldcount = 0;
					commandcount++;
					break;
				}// switch for reading formatted file *.ls  
				printf("%s", buffer);
			}
			printf("\n%i  %f\n", max_iterations, angle);
			for (int i = 0; i < num_symbols; i++) printf("%s ", symbol[i]);
			printf("\n%s\n", word);
			for (int i = 0; i < num_rules; i++) printf("%s ", rule[i]);
			printf("\n");

			return 0;
		}

	};

}