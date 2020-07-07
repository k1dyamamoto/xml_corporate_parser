#ifndef XMLPARSER_H
#define XMLPARSER_H

#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include "objects.h"
#include "commands.h"

void read_xml(const std::string &input_file, std::vector<Department*> &tree);
void writexml(const std::string &output_file, const std::vector<Department*> &tree);


#endif
