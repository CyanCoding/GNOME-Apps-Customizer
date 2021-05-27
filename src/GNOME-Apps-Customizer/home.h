#ifndef HOME_H
#define HOME_H

#include <iostream>
#include <vector>
#include <map>
#include "iniparser/iniparser.h"

std::vector<std::string> locateDesktopFiles(std::string homeDir);

std::map<std::string, std::string> getDesktopFileDetails(std::string path);


#endif // HOME_H
