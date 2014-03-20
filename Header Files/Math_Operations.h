/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */

#ifndef MATHS_OPERATIONS_H_
#define MATHS_OPERATIONS_H_

#include <string>
#include <unordered_map>
#include <vector>

double scalar_product(const std::unordered_map<std::string, int> & a, const std::unordered_map<std::string, int> & b);
double multiplyNorms(const std::unordered_map<std::string, int> & a, const std::unordered_map<std::string, int> & b);

#endif /* MATHS_OPERATIONS_H_ */