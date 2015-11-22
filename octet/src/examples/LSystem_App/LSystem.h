// the LSystem itself
#pragma once

#include <stdio.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

//#include "Turtle.h"

#define _RULE_ "F[+F]F[-F]F"

#define _W_ "F"
#define _N_ 3
#define _ANGLE_ 25.7
#define _NUM_RULES_ 1

#define _MAX_ 10

namespace octet {
	class LSystem : public resource {

		char rule[_MAX_][255];
		char coded_rule[_MAX_][255];
		char axiom[255];
		char coded_axiom[255];
		char symbol[_MAX_][255];

		unsigned int num_symbols;
		unsigned int num_rules;
		bool coding_done;

		unsigned int max_iterations;
		float angle;
		float length;
		float thickness;
		
	public:
	/*	LSystem() {
			strcpy(rule[0], _RULE_);
			strcpy(axiom, _W_);
			max_iterations = _N_ + 1;
			angle = _ANGLE_;
			num_rules = _NUM_RULES_;
		}*/
	
		// It will be initialized with a file, once tested
		char coded_symbol[_MAX_][255];
		dynarray<dynarray<char>> iteration;
		LSystem() {
			coding_done = 0;
		}

		
		void recode_wording() {
			//Any symbol-word will be re-coded into a single character to ease computations.
			// ex: 'plant' or 'internode', will become '0' and '1' char, in order of appearance in the file.
			// Axiom, rules and any iteration will use this coding as well. Rest of the symbols like +, -
			// [,],$,&,^,\,/ are simple enough so they are kept the same.
			//in order of insertion from the file, each symbol will get a number in char format
			for (int i = 0; i < num_symbols; i++) {
				itoa(i, coded_symbol[i], 2);
				printf(" %s ", coded_symbol[i]);
			}
			//Easier to use std::string library of tools to find and replace strings within strings.
			// Conversion of our arrays of chars to strings:
			std::vector<std::string> strRules;
			std::vector<std::string> strSymbols;
			std::vector<std::string> strCodedSymbols;
			std::string strAxiom (axiom);
			for (int i = 0; i < num_rules; i++) strRules.push_back(rule[i]);
			for (int i = 0; i < num_symbols; i++) {
				strSymbols.push_back(symbol[i]);
				strCodedSymbols.push_back(coded_symbol[i]);
			}

			//re-code rules
			for (int i = 0; i < num_rules; i++) { 
				for (int j = 0; j < num_symbols; j++) {
					for (int k = 0; k < strRules[i].length(); k++) {
						if (strRules[i].find(strSymbols[j], strSymbols[j].length()) != -1) {
							strRules[i].replace(strRules[i].find(strSymbols[j]), strSymbols[j].length(), strCodedSymbols[j]);
						}
				    }
				}
			}

			//re-code axiom
			if (strAxiom.length() == 1) {
				for (int j = 0; j < num_symbols; j++) {
					if (strAxiom[0] == strSymbols[j][0]) {
						strAxiom = strCodedSymbols[j];
					}
				}
			}
			else {
				for (int j = 0; j < num_symbols; j++) {
					for (int k = 0; k < strAxiom.length(); k++) {
						if (strAxiom.find(strSymbols[j], strSymbols[j].length()) != -1) {
							strAxiom.replace(strAxiom.find(strSymbols[j]), strSymbols[j].length(), strCodedSymbols[j]);
						}
					}
				}
			}
			//debug
			for (int i = 0; i < num_symbols; i++) std::cout << "\n\n" << strCodedSymbols[i] << " " << strSymbols[i];
			std::cout << "\n" << strAxiom << "\n";
			for (int i = 0; i < num_rules; i++) std::cout << strRules[i] << "\n";
			//convert back from strings into arrays of chars this time with all re-coded:
			int j = 0;
			for (int i = 0; i < num_rules; i++) {
				strncpy(coded_rule[i], strRules[i].c_str(), sizeof(coded_rule[i]));
				coded_rule[i][sizeof(coded_rule[i]) - 1] = 0;
				printf("\n%s %i", coded_rule[i], strRules[i].length());//debug
			}
			for (int i = 0; i < num_symbols; i++) {
				strncpy(coded_symbol[i], strCodedSymbols[i].c_str(), sizeof(coded_symbol[i]));
				coded_symbol[i][sizeof(coded_symbol[i]) - 1] = 0;
				printf("\n%s %i", coded_symbol[i], strCodedSymbols[i].length());//debug
			}
			//re-coded axiom was stored as an extra rule
			strncpy(coded_axiom, strAxiom.c_str(), sizeof(coded_axiom));
			coded_axiom[sizeof(coded_axiom) - 1] = 0;
			printf("\n%s %i", coded_axiom, strAxiom.length()); //debug

			coding_done = 1; //so we don't have to re-code again for the same lsystem
		}//recode_wording

		void init() {
		/*	strcpy(rule[0], _RULE_);
			strcpy(axiom, _W_);
			max_iterations = _N_+1;
			angle = _ANGLE_;*/
			
			iteration.resize(max_iterations+1);

			iteration[0].reserve((unsigned int)strlen(axiom));
			for (int i = 0; i < strlen(axiom); ++i)
				iteration[0].push_back(axiom[i]);
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
				//parsing symbols in previous iteration and matching them with corresponding rules
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

		void init2() {

			if (coding_done == 0) {
				recode_wording();
			}

			iteration.resize(max_iterations + 1);

			iteration[0].reserve((unsigned int)strlen(axiom));
			for (int i = 0; i < strlen(coded_axiom); ++i)
				iteration[0].push_back(coded_axiom[i]);
			//debug
			printf("\n");
			for (unsigned int i = 0; i < iteration[0].size(); ++i)
				printf("%c", iteration[0][i]);
			printf("\niteration: 0 size: %i\n", iteration[0].size());
			printf("---------\n");
			// generating all iterations
			int m = 0; //debug
			int n = 0; //debug
			unsigned int rule_length = strlen(coded_rule[0]);
			for (unsigned int n = 1; n <= max_iterations; ++n) {
				unsigned int space = space_needed2(n - 1);
				//printf("\n%i\n", (int)space); //debug
				unsigned int prev_iteration_length = iteration[n - 1].size();
				iteration[n].reserve(space);
				//parsing symbols in previous iteration and matching them with corresponding rules
				int match; //keep track if there is a match for a rule-symbol substitution
				for (unsigned int i = 0; i < prev_iteration_length; ++i) {
					int match = 0; // initialize to no match
					for (int j = 0; j < num_symbols; j++) {
						if (iteration[n - 1][i] == coded_symbol[j][0]) {
							match = 1; // yes match
							rule_length = strlen(coded_rule[j]);
							for (unsigned int k = 0; k < rule_length; ++k) {
								iteration[n].push_back(coded_rule[j][k]); //++m;
								printf("%c", coded_rule[j][k]); //debug
							}//for k
							//printf("\n rule[%i] length: %i", j, rule_length); //debug
						} //if-with match
					} //for j
					if (match == 0) { // match==0 meaning the symbol wasn't meant to be replaced by a rule but a turtle instruction('+','-','/'...)
							iteration[n].push_back(iteration[n - 1][i]); //++m; ++n;
							printf("%c", iteration[n - 1][i]); //debug
					} //if-with no match
				} //for i
				printf("\niteration:%i, size:%i, space:%i\n\n", n, iteration[n].size(),(int)space); //debug
			} //for n

		} //init2()

		unsigned int space_needed2( int prev_iteration ) {
			unsigned int replaceable_symbol_in_prev_iteration[_MAX_];
			unsigned int total_symbols_in_prev_iteration = iteration[prev_iteration].size();
			
			for (int i = 0; i < _MAX_; i++) replaceable_symbol_in_prev_iteration[i] = 0;

			for (unsigned int i = 0; i < total_symbols_in_prev_iteration; ++i) {
				for (int j = 0; j < num_symbols; j++) {
					if (iteration[prev_iteration][i] == coded_symbol[j][0]) {
						replaceable_symbol_in_prev_iteration[j] = replaceable_symbol_in_prev_iteration[j] + 1;
					}
				}
			}

			//assuming each symbol has one single rule. File must comply with order to match 1st symbol with 1st rule, 2nd symbol with 2nd rule, and so on.
			unsigned int size_when_all_rules_substituted = 0;
			unsigned int total_replaceables = 0;
			for (int i = 0; i < num_symbols; i++) {
				size_when_all_rules_substituted = strlen(coded_rule[i])*replaceable_symbol_in_prev_iteration[i] + size_when_all_rules_substituted;
				total_replaceables = replaceable_symbol_in_prev_iteration[i] + total_replaceables;
			}

			return (size_when_all_rules_substituted + total_symbols_in_prev_iteration - total_replaceables);
		} //space_needed()

		unsigned int space_needed(int num_rule, int prev_iteration) {
			unsigned int size_rule = strlen(rule[num_rule]);
			unsigned int replaceable_symbols_in_prev_iteration = 0;
			unsigned int total_symbols_in_prev_iteration = iteration[prev_iteration].size();

			for (unsigned int i = 0; i < total_symbols_in_prev_iteration; ++i)
				if (iteration[prev_iteration][i] == 'F') replaceable_symbols_in_prev_iteration++;


			return (size_rule*replaceable_symbols_in_prev_iteration + total_symbols_in_prev_iteration - replaceable_symbols_in_prev_iteration);
		} //space_needed()


		// get methods for iterations, angle, length , thickness
		unsigned int get_max_iteration() {
			return max_iterations;
		}

		float get_angle() {
			return angle;
		}

		float get_length() {
			return length;
		}

		float get_thickness() {
			return thickness;
		}

		//set methods for iterations, angle, length, thickness
		// iterations may need init() again
		void set_max_iteration(unsigned int n) {
			if (max_iterations < n) {
				max_iterations = n;
				init2();
			} 
		}

		void set_angle(float alpha) {
			 angle = alpha;
		}

		void set_length(float l) {
			 length = l;
		}

		void set_thickness(float t) {
			 thickness = t;
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
					length = atof(buffer);
					commandcount++;
					break;
				case 6:
					commandcount++;
					break;
				case 7:
					thickness = atof(buffer);
					commandcount++;
					break;
				case 8:
					commandcount++;
					break;
				case 9:
					if (fieldcount == 0) {
						num_symbols = atoi(buffer);
						fieldcount = num_symbols;
					} 
					commandcount++;
					break;
				case 10:
					strcpy(symbol[num_symbols - fieldcount], buffer);
					if (fieldcount > 1) {
						commandcount--;
						fieldcount--;
					} else if (fieldcount == 1) fieldcount = 0;
					commandcount++;
					break;
				case 11:
					commandcount++;
					break;
				case 12:
					strcpy(axiom, buffer);
					commandcount++;
					break;
				case 13:
					commandcount++;
					break;
				case 14:
					if (fieldcount == 0) {
						num_rules = atoi(buffer);
						fieldcount = num_rules;
					}
					commandcount++;
					break;
				case 15:
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
			printf("\n%i  %f %f %f\n", max_iterations, angle, length, thickness);
			for (int i = 0; i < num_symbols; i++) printf("%s ", symbol[i]);
			printf("\n%s\n", axiom);
			for (int i = 0; i < num_rules; i++) printf("%s \n", rule[i]);
			printf("\n");

			return 0;
		}

	};

}