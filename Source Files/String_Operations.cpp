#include <string>
#include <algorithm>
#include <vector>


using namespace std;

/*
 *	Small functions to modify strings
 */

// Trim the line to avoid erros
void trimLine(string & LINE) {
	LINE.erase(remove(LINE.begin(), LINE.end(), '\t'), LINE.end());
	LINE.erase(remove(LINE.begin(), LINE.end(), ' '), LINE.end());
}

// Returns true if it is not a punctuation character
int not_punct(char c) {
    return !ispunct((unsigned char) c);
}

// Remove all punctation characters
void stripPunct(string & str) {

	if(!(str.find("+") || str.find("-") || str.find("*"))){
		string::iterator itr = find_if( str.begin(), str.end(), not_punct);

		str.erase( str.begin(), itr);

		string::reverse_iterator ritr = find_if( str.rbegin(), str.rend(), not_punct);

		str.erase( ritr.base(), str.end());
	}
    
}

/*
 *	Put the query words into a vector of strings
 */
vector<string> queryToVector(string & QUERY){
	string NEXT;
	vector<string> RESULT;

	// For each character in the string
    for (string::const_iterator it = QUERY.begin(); it != QUERY.end(); it++) {
        // If we've hit the terminal character which is a space : ' '
        if (*it == ' ') {
            // If we have some characters accumulated
            if (!NEXT.empty()) {
                // Add them to the result vector
                RESULT.push_back(NEXT);
                NEXT.clear();
            }
        } else {
            // Accumulate the next character into the sequence
            NEXT += *it;
        }
    }

    if (!NEXT.empty())
         RESULT.push_back(NEXT);

    return RESULT;

}