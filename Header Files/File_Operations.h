/*
 * File_Operations.h
 *
 *  Created on: Jan 23, 2014
 *      Author: nicolas.husser
 */


#ifndef FILE_OPERATIONS_H_
#define FILE_OPERATIONS_H_

#include <string>
#include <vector>

std::vector<std::string> readFileName(std::ifstream & INPUT_F);
std::vector<std::string> readDocument(std::ifstream & INPUT_F);


#endif /* FILE_OPERATIONS_H_ */
