#pragma once

#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>
#define RED "\033[31m"
#define GREEN "\033[92m"
#define RESET "\033[0m"
#define CYAN "\033[96m"

void parseTheFile(std::string file, std::map<unsigned long, double>& mydbz);
void loadData(std::map<unsigned long, double>& mydb);
