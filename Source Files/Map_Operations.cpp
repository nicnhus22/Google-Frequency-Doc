/*
 * Main.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#include "Map_Operations.h"
#include "String_Operations.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

typedef unordered_map<string, int>::iterator MAP_ITER;

/*
 *	This method takes a vector<string> containing the words of every file and returns
 *	an unordered_map<string, int> where the key is the string and the value its frequency
 *	and also adds it to the master map
 */
std::unordered_map <std::string, int> getFrequency(const std::vector<std::string> & FILE_CONTENT, std::unordered_map<std::string, int> & MASTER){

	unordered_map <string, int> MAP;

	// Iterate through the current file being copied and push_back all the words in the
	// DOCUMENTS_ALL vector and in the MAP to compute their frequency
	for(vector<string>::size_type j = 0; j != FILE_CONTENT.size(); ++j){
			
		string TEMP = FILE_CONTENT[j];
		
		// String operations
		stripPunct(TEMP); // Remove any punctuation to get only the words
		transform(TEMP.begin(), TEMP.end(), TEMP.begin(), ::tolower); // Put every word to lower case
					
		unordered_map<string, int>::const_iterator MAP_IT = MAP.find(TEMP); // Create iterator to know if the Key is in the MAP or not
		unordered_map<string, int>::const_iterator MAP_MASTER_IT = MASTER.find(TEMP); // Create iterator to know if the Key is in the MASTER_MAP or not

		if ( MAP_IT == MAP.end() ){ // If not in the MAP add it without incrementing
			MAP[TEMP] = 1;
		}else{ // If it is in the MAP then increment and add it
			MAP[TEMP] = MAP[TEMP]+1;		  
		}

		if ( MAP_MASTER_IT == MASTER.end() ){ // If not in the MASTER add it without incrementing
			MASTER[TEMP] = 1;
		}else{ // If it is in the MAP then increment and add it
			MASTER[TEMP] = MASTER[TEMP]+1;		  
		}
	}

	return MAP;

}




/*
 *	This method takes a vector<string> containing the words of every file and returns
 *	an unordered_map<string, int> where the key is the string and the value its frequency
 */
std::unordered_map <std::string, int> getQueryFrequency(const std::vector<std::string> & FILE_CONTENT){

	unordered_map <string, int> MAP;

	// Iterate through the current file being copied and push_back all the words in the
	// DOCUMENTS_ALL vector and in the MAP to compute their frequency
	for(vector<string>::size_type j = 0; j != FILE_CONTENT.size(); ++j){
			
		string TEMP = FILE_CONTENT[j];
		
		// String operations
		stripPunct(TEMP); // Remove any punctuation to get only the words
		transform(TEMP.begin(), TEMP.end(), TEMP.begin(), ::tolower); // Put every word to lower case
					
		unordered_map<string, int>::const_iterator MAP_IT = MAP.find(TEMP); // Create iterator to know if the Key is in the MAP or not

		if ( MAP_IT == MAP.end() ){ // If not in the MAP add it without incrementing
			MAP[TEMP] = 1;
		}else{ // If it is in the MAP then increment and add it
			MAP[TEMP] = MAP[TEMP]+1;		  
		}
	}

	return MAP;

}


/* 
 *	This function takes a MAP and compares it with the MASTER_MAP to create the vector of frequency for a
 *	given document: Output is an unordered_map<string, int> in relation with the master_map
 */
unordered_map <string, int> computeVector(const unordered_map <string, int> & FILE_MAP, const unordered_map<string, int> & MASTER_MAP){

	unordered_map<string, int> FILE_VECTOR;

	FILE_VECTOR.insert(MASTER_MAP.begin(), MASTER_MAP.end()); // Make a copy of the master map

	// cout << "(" ;
	for(MAP_ITER IT = FILE_VECTOR.begin(); IT != FILE_VECTOR.end(); ++IT){ 
		
		unordered_map<string, int>::const_iterator FILE_IT = FILE_MAP.find(IT->first);

		string KEY = IT->first; // Get the first key pointed by the iterator
		
		if(FILE_IT == FILE_MAP.end()){ // If the word is not there then set it to zero
			FILE_VECTOR.at(KEY) = 0;
		}else{ // Else set it to the file frequency
			FILE_VECTOR.at(KEY) = FILE_MAP.at(KEY);
		}
		
		// cout << FILE_VECTOR[KEY] << ", ";

	}

	// cout << ")" << endl;;


	return FILE_VECTOR;

}




