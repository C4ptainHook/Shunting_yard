#pragma once
#include <cmath>
#include "Parser.h"
#include "Stack.h"

namespace Evaluator {
    int evaluate_expression(queue<Parser::Token>& postfix_q) {
        stack<int> temp_stack;
        while(!postfix_q.empty()) {
            switch (postfix_q.front().type) {
                case Parser::Token::Token_Type::Number: {
                    temp_stack.push(std::stoi(postfix_q.front().str));
                    postfix_q.pop();
                    break;
                }
                case Parser::Token::Token_Type::Operator: {
                    switch (postfix_q.front().str[0]) {
                        case '+': {
                            int right = temp_stack.peek();
                            temp_stack.pop();
                            int left = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(left+right);
                            break;
                        }
                        case '-' :{
                            int right = temp_stack.peek();
                            temp_stack.pop();
                            int left = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(left-right);
                            break;
                        }
                        case 'm' : {
                            int to_negative = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(-1*to_negative);
                        }
                        case '*' :{
                            int right = temp_stack.peek();
                            temp_stack.pop();
                            int left = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(left*right);
                            break;
                        }
                        case '/' :{
                            int right = temp_stack.peek();
                            temp_stack.pop();
                            int left = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(left/right);
                            break;
                        }
                        case '^' :{
                            int right = temp_stack.peek();
                            temp_stack.pop();
                            int left = temp_stack.peek();
                            temp_stack.pop();
                            temp_stack.push(static_cast<int>(pow(left, right)));
                            break;
                        }
                    }
                }
                default: break;
            }
        }
        return temp_stack.peek();
    }
}