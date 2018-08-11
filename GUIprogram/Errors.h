#pragma once

#include <string>

extern void fatalError(std::string errorString); //extern says that the function is defined somewhere else.
//extern is used when the function is not linked with a scope resolution operator like in classes