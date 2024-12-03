/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include "program.hpp"



Program::Program() = default;

Program::~Program() = default;

void Program::clear() {
    // Replace this stub with your own code
    //todo
    number.clear();
    linecode.clear();
}

void Program::addSourceLine(int lineNumber, const std::string &line) {
    // Replace this stub with your own code
    //todo
    number.insert(lineNumber);
    linecode[lineNumber] = line;
}

void Program::removeSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
    linecode.erase(lineNumber);
    number.erase(lineNumber);
}

std::string Program::getSourceLine(int lineNumber) {
    // Replace this stub with your own code
    //todo
    if (number.count(lineNumber)) return linecode[lineNumber];
    return "";
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    //todo
    auto ins = number.find(lineNumber);
    if (ins != number.end()) {

    }
}

//void Program::removeSourceLine(int lineNumber) {

Statement *Program::getParsedStatement(int lineNumber) {
   // Replace this stub with your own code
   //todo
}

int Program::getFirstLineNumber() {
    // Replace this stub with your own code
    //todo
    if (number.empty()) return -1;
    return *number.begin();
}

int Program::getNextLineNumber(int lineNumber) {
    // Replace this stub with your own code
    //todo
    auto x = number.find(lineNumber);
    ++x;
    if (x != number.end()) return *x;
    return -1;
}

//more func to add
//todo

std::string Program::getline(int lineNumber) {
    return linecode[lineNumber];
}
bool Program::checkline(int lineNumber) {
    return number.find(lineNumber) != number.end();
}




