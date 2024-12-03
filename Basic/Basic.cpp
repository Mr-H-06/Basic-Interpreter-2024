/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BASIC interpreter.
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.hpp"
#include "parser.hpp"
#include "program.hpp"
#include "Utils/error.hpp"
#include "Utils/tokenScanner.hpp"
#include "Utils/strlib.hpp"


/* Function prototypes */

void processLine(std::string line, Program &program, EvalState &state);

/* Main program */

int main() {
    //freopen("D:\\c++code\\code\\bigger.in","r",stdin);
    //freopen("D:\\c++code\\code\\out.out","w",stdout);
    freopen("/mnt/c/Users/hejia/Desktop/Basic-Interpreter-2024/Test/trace99.txt","r",stdin);
    EvalState state;   // 存变量 和 值
    Program program;   // 存代码
    //cout << "Stub implementation of BASIC" << endl;
    while (true) {
        try {
            std::string input;
            getline(std::cin, input);
            if (input.empty())
                continue;
            processLine(input, program, state);
        } catch (ErrorException &ex) {
            std::cout << ex.getMessage() << std::endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version of
 * implementation, the program reads a line, parses it as an expression,
 * and then prints the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(std::string line, Program &program, EvalState &state) {
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    //todo
    std::string read = scanner.nextToken();
    if ('0' <= read[0] && read[0] <= '9') {
        int linenumber = stringToInteger(read);
        program.addSourceLine(linenumber, line);
        if (scanner.hasMoreTokens()) {
            read = scanner.nextToken();
            if (read == "INPUT") {
            } else if (read == "LET") {
            } else if (read == "PRINT") {
            } else if (read == "END") {
            } else if (read == "GOTO") {
            } else if (read == "REM") {
            } else if (read == "IF") {
            } else {
                error("SYNTAX ERROR");
            }
        } else {
            program.removeSourceLine(linenumber);
        }
    } else {
        Statement *output;
        if (read == "RUN") {
            output = new RunStatement;
            output->execute(state, program);
        } else if (read == "LIST") {   //
            output = new ListStatement;
            output->execute(state, program);\
        } else if (read == "CLEAR") {   //
            program.clear();
            state.Clear();
        } else if (read == "QUIT") {   //
            exit(0);
        } else if (read == "HELP") {   //
            std::cout << "There is nothing actually.\n";
        } else if (read == "INPUT") {
            output = new InputStatement(line);
            output->execute(state,program);\
        } else if (read == "LET") {   //
            output = new LetStatement(line);
            output->execute(state, program);/*
            std::string name = scanner.nextToken();
            if (scanner.nextToken() != "=") {
                error("SYNTAX ERROR");
            }
            state.setValue(name, parseExp(scanner)->eval(state));
            */
        } else if (read == "PRINT") {   //
            output = new PrintStatement(parseExp(scanner));
            output->execute(state, program);
            //Expression *parse = parseExp(scanner);
            //std::cout << parse->eval(state) << std::endl;
        } else {
            error("SYNTAX ERROR");
        }
    }
}