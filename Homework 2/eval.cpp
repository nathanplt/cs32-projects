#include <iostream>
#include <string>
#include <stack>
#include <cassert>

using namespace std;

bool valid_infix(string infix);

int precedence(char op);

void infix_to_postfix(const string &infix, string &postfix);

int evaluate(string infix, const bool values[], string& postfix, bool& result)
{
    // Make sure infix is valid
    if (!valid_infix(infix)) {
        return 1;
    }
    
    // Convert infix to postfix expression
    infix_to_postfix(infix, postfix);
    
    // Evaluate postfix expression
    stack<char> operands;
    for (char c : postfix) {
        if (isdigit(c)) {
            operands.push(values[c - '0']);
        } else if (c == '!') {
            bool operand = operands.top();
            operands.pop();
            operands.push(!operand);
        } else {
            bool operand2 = operands.top();
            operands.pop();
            bool operand1 = operands.top();
            operands.pop();
            
            if (c == '&') {
                operands.push(operand1 && operand2);
            } else {
                operands.push(operand1 || operand2);
            }
        }
    }
    
    result = operands.top();
    return 0;
}

bool valid_infix(string infix)
{
    // Returns true if the given infix is valid, false if not
    bool expectDigit = true;
    int openPara = 0;
    for (char c : infix) {
        if (isspace(c)) {
            continue;
        }
        
        if (isdigit(c)) {
            // If we don't expect a digit, return false
            if (!expectDigit) {
                return false;
            }
            expectDigit = false;
        } else if (c == '(') {
            // An open parantheses can only be placed where a digit is expected
            if (!expectDigit) {
                return false;
            }
            openPara++;
        } else if (c == ')') {
            // A closing parantheses cannot be placed where a digit should be
            if (expectDigit) {
                return false;
            }
            
            if (--openPara < 0) {
                return false;
            }
        } else if (c == '!') {
            // A NOT operator must be placed where a digit is expected
            if (!expectDigit) {
                return false;
            }
        } else if (c == '&' || c == '|') {
            // The binary operators cannot be placed where a digit is expected
            if (expectDigit) {
                return false;
            }
            
            // A digit must follow a binary operator
            expectDigit = true;
        } else {
            // Not a valid character
            return false;
        }
    }
    
    // Cannot be expecting a digit, and all parantheses must be closed off
    return !expectDigit && openPara == 0;
}

int precedence(char op) {
    // Returns value of precedence
    if (op == '!') {
        return 3;
    } else if (op == '&') {
        return 2;
    } else if (op == '|') {
        return 1;
    }
    return 0;
}

void infix_to_postfix(const string &infix, string &postfix) {
    postfix = "";
    stack<char> op_stack;
    for (char c : infix) {
        if (isspace(c)) {
            continue;
        }
        
        if (isdigit(c)) {
            postfix += c;
        } else if (c == '(') {
            op_stack.push(c);
        } else if (c == ')') {
            while (op_stack.top() != '(') {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.pop();
        } else {
            while (!op_stack.empty() && op_stack.top() != '(' && precedence(c) <= precedence(op_stack.top())) {
                postfix += op_stack.top();
                op_stack.pop();
            }
            op_stack.push(c);
        }
    }
    
    while (!op_stack.empty()) {
        postfix += op_stack.top();
        op_stack.pop();
    }
}

int main()
{
    bool ba[10] = {
      //  0      1      2      3      4      5      6      7      8      9
        true,  true,  true,  false, false, false, true,  false, true,  false
    };
    string pf;
    bool answer;
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  answer);
    assert(evaluate("", ba, pf, answer) == 1);
    assert(evaluate("8|", ba, pf, answer) == 1);
    assert(evaluate(" &6", ba, pf, answer) == 1);
    assert(evaluate("4 5", ba, pf, answer) == 1);
    assert(evaluate("01", ba, pf, answer) == 1);
    assert(evaluate("()", ba, pf, answer) == 1);
    assert(evaluate("()4", ba, pf, answer) == 1);
    assert(evaluate("2(9|8)", ba, pf, answer) == 1);
    assert(evaluate("2(&8)", ba, pf, answer) == 1);
    assert(evaluate("(6&(7|7)", ba, pf, answer) == 1);
    assert(evaluate("x+5", ba, pf, answer) == 1);
    assert(evaluate("2|3|4", ba, pf, answer) == 0
                           &&  pf == "23|4|"  &&  answer);
    assert(evaluate("2|(3|4)", ba, pf, answer) == 0
                           &&  pf == "234||"  &&  answer);
    assert(evaluate("4  |  !3 & (0&3) ", ba, pf, answer) == 0
                           &&  pf == "43!03&&|"  &&  !answer);
    assert(evaluate(" 9  ", ba, pf, answer) == 0  &&  pf == "9"  &&  !answer);
    assert(evaluate("((6))", ba, pf, answer) == 0  &&  pf == "6"  &&  answer);
    ba[2] = false;
    ba[9] = true;
    assert(evaluate("((9))", ba, pf, answer) == 0  &&  pf == "9"  &&  answer);
    assert(evaluate("2| 3", ba, pf, answer) == 0  &&  pf == "23|" &&  !answer);
    
    assert(evaluate("!!7", ba, pf, answer) == 0 && pf == "7!!" && !answer);
    
    cout << "Passed all tests" << endl;
}
