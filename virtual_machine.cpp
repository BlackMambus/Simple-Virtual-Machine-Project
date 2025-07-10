#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

using namespace std;

enum Instruction {
    PUSH, ADD, SUB, MUL, DIV, PRINT, HALT, INVALID
};

struct Command {
    Instruction instr;
    int operand;
};

Instruction parseInstruction(const string& token) {
    if (token == "PUSH") return PUSH;
    if (token == "ADD") return ADD;
    if (token == "SUB") return SUB;
    if (token == "MUL") return MUL;
    if (token == "DIV") return DIV;
    if (token == "PRINT") return PRINT;
    if (token == "HALT") return HALT;
    return INVALID;
}

vector<Command> parseProgram(const vector<string>& lines) {
    vector<Command> program;
    for (const auto& line : lines) {
        stringstream ss(line);
        string token;
        ss >> token;
        Instruction instr = parseInstruction(token);
        int operand = 0;
        if (instr == PUSH) {
            ss >> operand;
        }
        program.push_back({instr, operand});
    }
    return program;
}

void runProgram(const vector<Command>& program) {
    stack<int> vmStack;
    size_t ip = 0; // instruction pointer

    while (ip < program.size()) {
        Command cmd = program[ip];
        switch (cmd.instr) {
            case PUSH:
                vmStack.push(cmd.operand);
                break;
            case ADD: {
                int b = vmStack.top(); vmStack.pop();
                int a = vmStack.top(); vmStack.pop();
                vmStack.push(a + b);
                break;
            }
            case SUB: {
                int b = vmStack.top(); vmStack.pop();
                int a = vmStack.top(); vmStack.pop();
                vmStack.push(a - b);
                break;
            }
            case MUL: {
                int b = vmStack.top(); vmStack.pop();
                int a = vmStack.top(); vmStack.pop();
                vmStack.push(a * b);
                break;
            }
            case DIV: {
                int b = vmStack.top(); vmStack.pop();
                int a = vmStack.top(); vmStack.pop();
                vmStack.push(a / b);
                break;
            }
            case PRINT:
                cout << "Top of Stack: " << vmStack.top() << endl;
                break;
            case HALT:
                return;
            default:
                cerr << "Invalid instruction at line " << ip << endl;
                return;
        }
        ip++;
    }
}
int main() {
    vector<string> programText = {
        "PUSH 10",
        "PUSH 20",
        "ADD",
        "PUSH 5",
        "MUL",
        "PRINT",
        "HALT"
    };

    auto program = parseProgram(programText);
    runProgram(program);
    return 0;
}




