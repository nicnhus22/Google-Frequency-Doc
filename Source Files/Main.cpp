/*
 * Main.cpp
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#include "String_Operations.h"
#include "Math_Operations.h"
#include "File_Operations.h"
#include "Map_Operations.h"

#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <unordered_map>
#include <map>
#include <regex>
#include <algorithm>
#include <complex> 
#include <functional>

using namespace std;

typedef vector<string> string_vector;

int main(){

	// Open Input FIle Stream
	ifstream ifs("file_names.txt");
	// Vector that holds name
	string_vector FILES_NAME = readFileName(ifs);
	// Store the query of the user
	string USER_QUERY;
	// Store the user query in a vector
	string_vector QUERY_VECTOR;
	// Store the scalar product of each document vector with the query vector
	vector<double> SCALAR_PRODS;
	// Store the multiplication of the norm of each document vector and the query
	vector<double> NORM_PRODS;
	// Store the score of each document in multimap in case there are more than one identical score
	multimap<double, string> DOC_SCORE;
	// Store the number of documents to be displayed, thos that have the highest score
	multimap<double, string>::size_type NTH_SCORE;

	// Hold the vectors containing the vector of words of each document
	vector<string_vector> DOCUMENTS_HOLDER;
	// Hold the words of every single documents
	unordered_map <string, int> MASTER_MAP;
	// Create vector that holds the map for every file
	vector<unordered_map <string, int>> MAP_HOLDER;
	// Create vector that frequency vector for every file
	vector<unordered_map <string, int>> VECTOR_HOLDER;
	// Store the query of the user with each words in a vector
	unordered_map<string, int> QUERY_WORDS_MAP;

	// Iterate through all the files and push their content inside the DOCUMENTS_HOLDER
	// with the index of the current file
	for(string_vector::size_type i = 0; i != FILES_NAME.size(); ++i){
		
		ifstream IN_FILE(FILES_NAME[i].c_str()); // Open current file

		if(IN_FILE){ // If the file exists and can be found, then process
			DOCUMENTS_HOLDER.push_back(readDocument(IN_FILE)); // Put the content of the files in the DOCUMENTS_HOLDER[i]
			MAP_HOLDER.push_back(getFrequency(DOCUMENTS_HOLDER[i], MASTER_MAP)); // Create the map to get the frequency of each word in the current file
		}else { // Else, if the file doesnt exist or cannot be found then erase it from FILE_NAME vector
			cout << "The file " << FILES_NAME[i] << " doesn't exist or cannot be found, please verify the file name." << endl;
			FILES_NAME.erase(FILES_NAME.begin()+i); // Remove the current file name from the vector
			--i; // Decrement i so that you avoid starting the vector at 1
		}	
	}

	// Iterate trhough all the Maps of each file and push it's corresponding vector in the
	// VECTOR_HOLDER to get the vector compared to the MASTER_MAP
	for(vector<unordered_map <string, int>>::size_type i=0; i!= MAP_HOLDER.size(); ++i){
		VECTOR_HOLDER.push_back(computeVector(MAP_HOLDER[i], MASTER_MAP));
	}

	// Get the user query with a check if the query is empty or contains special
	// characters only
	while(true) {
		cout << "Please enter a query (words with a space in between): " << endl;
		getline(cin,USER_QUERY);
		if(regex_search (USER_QUERY, regex("[a-zA-Z]")))
			break;
		else
			cout << "The query is empty or contains special characters only, cannot proceed." << endl;
	}

	QUERY_VECTOR    = queryToVector(USER_QUERY); // Put the query in form of a vector
	QUERY_WORDS_MAP = getQueryFrequency(QUERY_VECTOR); // Get the frequency of the words in the vector
	QUERY_WORDS_MAP = computeVector(QUERY_WORDS_MAP, MASTER_MAP); // Get the vector compared to the MASTER_MAP


	// Iterate through all the vectors of each document and compute dot product with the QUERY_VECTOR also 
	// multiplication of the norm of the document vector with the query vector
	for(vector<unordered_map <string, int>>::size_type i=0; i!= VECTOR_HOLDER.size(); ++i){
		double TEMP_DOT = scalar_product(QUERY_WORDS_MAP, VECTOR_HOLDER[i]); // Get the scalar product
		SCALAR_PRODS.push_back(TEMP_DOT);
		double TEMP_NORM = multiplyNorms(QUERY_WORDS_MAP, VECTOR_HOLDER[i]); // Multiply the norm of the two vectors
		NORM_PRODS.push_back(TEMP_NORM);
	}
	
	// Iterate through all the vectors and compute the ratio of the scalar product and the multiplication
	// of the vectors' norms. Then add it to a Map so that the elements are sorted.
	for(vector<double>::size_type IT = 0; IT != SCALAR_PRODS.size(); ++IT){
		double RATIO;

		if(SCALAR_PRODS[IT] == 0 && NORM_PRODS[IT] == 0) // Avoid division by zero error and other check to be sure
			RATIO = 0;
		else
			RATIO = SCALAR_PRODS[IT]/NORM_PRODS[IT];
		DOC_SCORE.insert(pair<double, string>(RATIO,FILES_NAME[IT]));
	}

	cout << "\nHow many documents do you want to display? " ;
	cin  >> NTH_SCORE;
	cout << endl;
	if(NTH_SCORE > DOC_SCORE.size()){
		NTH_SCORE = DOC_SCORE.size();
		cout << "You entered a number greater than the number of files. We'll display everything." << endl;
	}else if(NTH_SCORE <= 0){
		NTH_SCORE = DOC_SCORE.size();
		cout << "You entered a number less than or equal 0. We'll display everything." << endl;
	}


	int CTR = 0;
	// Display the final created map reversed so that the highest ranking comes first.
	for (std::multimap<double,string>::reverse_iterator IT = DOC_SCORE.rbegin(); IT != DOC_SCORE.rend(); ++IT){
		if(CTR == NTH_SCORE) // Display only the requested number of documents' score
			break;
		cout << (CTR+1) << ". Document \'" << IT->second << "\' has " << (IT->first)*100 << "% match." << endl;
		CTR++;
	}

	string DEBUG;
	cin >> DEBUG;

	return 0;
}








