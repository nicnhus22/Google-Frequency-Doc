#include "Math_Operations.h"

#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

/*
 *	This function computes the dot product of two vectors
 */
double scalar_product(const std::unordered_map<std::string, int> & a, const std::unordered_map<std::string, int> & b){

    if( a.size() != b.size() ) // error check
    {
        puts( "Error a's size not equal to b's size" ) ;
        return -1 ;  // not defined
    }


	vector<int> VALUE_A, VALUE_B;

	for(unordered_map<std::string, int>::const_iterator IT_A = a.begin(), IT_B = b.begin(); IT_A != a.end(), IT_B != b.end(); ++IT_A, ++IT_B ) {
    	VALUE_A.push_back( IT_A->second );
		VALUE_B.push_back( IT_B->second );
    }

    return inner_product(begin(VALUE_A), end(VALUE_A), begin(VALUE_B), 0.0);

}


/*
 *	Sum the square of the vector to then sqrt() it
 */
double sumSquares(const std::vector<int> & v)
{
    double result = 0.0;
    for(unsigned int i = 0; i < v.size(); ++i)
        result += (v[i] * v[i]);
    return result;
}


/*
 *	This function computes the multiplaction of the norm of two vectors
 */
double multiplyNorms(const std::unordered_map<std::string, int> & a, const std::unordered_map<std::string, int> & b){

    if( a.size() != b.size() ) // error check
    {
        puts( "Error a's size not equal to b's size" ) ;
        return -1 ;  // not defined
    }

	vector<int> VALUE_A, VALUE_B;

	for(unordered_map<std::string, int>::const_iterator IT_A = a.begin(), IT_B = b.begin(); IT_A != a.end(), IT_B != b.end(); ++IT_A, ++IT_B ) {
    	VALUE_A.push_back( IT_A->second );
		VALUE_B.push_back( IT_B->second );
    }

	double RESULT = sqrt(sumSquares(VALUE_A))*sqrt(sumSquares(VALUE_B)); // Compute actual norm multiplication

    return RESULT;

}