/*
 * File_Operations.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#include "File_Operations.h"
#include "String_Operations.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <regex>

using namespace std;

typedef vector<string> string_vector;


/*
 *	End of small string functions
 */


vector<string> readFileName(ifstream & INPUT_F){

	string TEMP_LINE;
	string_vector WORDS;

	// Read the file line by line until there is no more
	// Store the line is a vector<string> to keep track of it
	while(getline(INPUT_F, TEMP_LINE)){
		// Trim file name to avoid errors
		trimLine(TEMP_LINE);
		WORDS.push_back(TEMP_LINE);
	}
	INPUT_F.close();

	return WORDS;
}

vector<string> readDocument(ifstream & INPUT_F){

	string WORD;
	string_vector WORDS;

	// Read the file word by word until there is no more
	// Store the words is a vector<string> to keep track of it
	while(INPUT_F >> WORD){
		WORDS.push_back(WORD);
	}
	INPUT_F.close();

	return WORDS;

}


