/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */


#ifndef STRING_OPERATIONS_H_
#define STRING_OPERATIONS_H_

#include <string>
#include <vector>

std::vector<std::string> queryToVector(std::string & QUERY);
void stripPunct(std::string & str);
void trimLine(std::string & LINE);
int not_punct(char c);


#endif /* STRING_OPERATIONS_H_ */
