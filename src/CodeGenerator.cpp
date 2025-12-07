#include "CodeGenerator.hpp"
#include <sstream>

std::string CodeGenerator::newTemp() {
    std::stringstream ss;
    ss << "t" << nextTemp++;
    return ss.str();
}

std::string CodeGenerator::newLabel() {
    std::stringstream ss;
    ss << "L" << nextLabel++;
    return ss.str();
}

void CodeGenerator::reset() {
    nextTemp = 0;
    nextLabel = 0;
}
