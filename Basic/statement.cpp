/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include "statement.hpp"


/* Implementation of the Statement class */

int stringToInt(std::string str);

Statement::Statement() = default;

Statement::~Statement() = default;

//todo
//Statement
bool Statement::check(std::string name) {
    for (int i = 0; i < 13; ++i) {
        if (name == illegal[i]) return false;
        bool repeat = false;
        for (int j = 0; j <= static_cast<int> (name.size()) - static_cast<int> (illegal[i].size()); ++j) {
            repeat = true;
            for (int k = 0; k < illegal[i].size(); ++k) {
                if (name[j + k] != illegal[i][k]) {
                    repeat = false;
                    break;
                }
            }
            if (repeat) return false;
        }
    }
    return true;
}

//PrintStatement
PrintStatement::PrintStatement(Expression *parse) : parse(parse) {}
PrintStatement::~PrintStatement() {
    delete parse;
}
void PrintStatement::execute(EvalState &state, Program &program) {
    std::cout << parse->eval(state) << std::endl;
}


//InputStatement
InputStatement::InputStatement(std::string input) : input(input){}
InputStatement::~InputStatement() {}
void InputStatement::execute(EvalState &state, Program &program) {
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.scanNumbers();
    scan.setInput(input);
    scan.nextToken();
    std::string name = scan.nextToken();
    if (scan.hasMoreTokens() || !check(name)) {
        error("SYNTAX ERROR");
    } else {
        std::string read;
        int n;
        while (true) {
            try {
                std::cin >> read;
                n = stringToInteger(read);
                break;
            } catch (ErrorException& error) {
                std::cout << "INVALID NUMBER\n";
            }
        }
        state.setValue(name, n);
    }
}


//LetState
LetStatement::LetStatement(std::string input) : input(input) {}
LetStatement::~LetStatement() {}
void LetStatement::execute(EvalState &state, Program &program) {
    TokenScanner scan;
    scan.ignoreWhitespace();
    scan.scanNumbers();
    scan.setInput(input);
    scan.nextToken();
    std::string name = scan.nextToken();
    if (scan.nextToken() != "=" || !check(name)) {
        error("SYNTAX ERROR");
    } else {
        state.setValue(name, parseExp(scan)->eval(state));
    }
}


//RunStatement
RunStatement::RunStatement() {}
RunStatement::~RunStatement() {};
void RunStatement::execute(EvalState &state, Program &program) {
    int ins = program.getFirstLineNumber();
    while (ins != -1) {
        std::string read = program.getline(ins), line;
        int k = 0;
        while ('0' <= read[k] && read[k] <= '9') {
            ++k;
        }
        ++k;
        for (int i = k; i < read.size(); ++i) {
            line[i - k] = read[i];
        }
        TokenScanner code;
        code.ignoreWhitespace();
        code.scanNumbers();
        code.setInput(line);
        read = code.nextToken();
        Statement *output;
        if (read == "GOTO") {   //
            delete output;
            int lineNumber = stringToInteger(code.nextToken());
            if (program.checkline(lineNumber)) {
                ins = lineNumber;
            } else {
                error(" LINE NUMBER ERROR");
            }
        } else if (read == "IF") {
            output = new IfStatement(line);
            output->execute(state, program);
            delete output;
        } else if (read == "INPUT") {
            output = new InputStatement(line);
            output->execute(state,program);
            delete output;
            ins = program.getNextLineNumber(ins);
        } else if (read == "LET") {   //
            output = new LetStatement(line);
            output->execute(state, program);
            delete output;
            ins = program.getNextLineNumber(ins);/*
            std::string name = scanner.nextToken();
            if (scanner.nextToken() != "=") {
                error("SYNTAX ERROR");
            }
            state.setValue(name, parseExp(scanner)->eval(state));
            */
        } else if (read == "PRINT") {   //
            output = new PrintStatement(parseExp(code));
            output->execute(state, program);
            delete output;
            ins = program.getNextLineNumber(ins);
            //Expression *parse = parseExp(scanner);
            //std::cout << parse->eval(state) << std::endl;
        } else if (read == "REM") {
            ins = program.getNextLineNumber(ins);
        } else if (read == "END") {
            break;
        } else {
            error("SYNTAX ERROR");
        }
    }
}



//IfStatement
IfStatement::IfStatement(std::string input) : input(input){}
IfStatement::~IfStatement() {}
void IfStatement::execute(EvalState &state, Program &program) {}
int IfStatement::executeif(EvalState &state, Program &program) {
    TokenScanner scan, expr1, expr2;
    std::string expression, read, sign;
    int ans1, ans2, GoTo;
    scan.ignoreWhitespace();
    scan.scanNumbers();
    scan.setInput(input);
    expression = scan.nextToken();
    read = scan.nextToken();
    while (read != ">" && read != "<" && read != "=") {
        expression = expression + read;
        read = scan.nextToken();
    }
    sign = read;
    expr1.ignoreWhitespace();
    expr1.scanNumbers();
    expr1.setInput(expression);
    ans1 = parseExp(expr1)->eval(state);
    expression = scan.nextToken();
    read = scan.nextToken();
    GoTo = stringToInteger(read);
    while (read != "THEN") {
        expression = expression + read;
        read = scan.nextToken();
    }
    expr2.ignoreWhitespace();
    expr2.scanNumbers();
    expr2.setInput(expression);
    ans2 = parseExp(expr2)->eval(state);
    if (read == ">" && ans1 > ans2 || read == "=" && ans1 == ans2 || read == "<" && ans1 < ans2) {
        return GoTo;
    } else return -1;
}



//ListStatement
ListStatement::ListStatement() {}
ListStatement::~ListStatement() {}
void ListStatement::execute(EvalState &state, Program &program) {
    int i = program.getFirstLineNumber();
    while (i != -1) {
        std::cout << program.getline(i) << '\n';
        i = program.getNextLineNumber(i);
    }
}