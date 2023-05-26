#pragma once
#include "Parser.h"
#include "Stack.h"

namespace Algorithm {
    queue<Parser::Token> Shunting_yard(queue<Parser::Token>& parsed_q) {
        queue<Parser::Token> output;
        stack<Parser::Token> operator_stack;
            for(auto token : parsed_q) {
               switch(token.type){
                   case Parser::Token::Token_Type::Number: {
                       output.push(token); break;}
                   case Parser::Token::Token_Type::Operator: {
                       while(!operator_stack.empty()
                       &&operator_stack.peek().precedence <= token.precedence )
                       {
                           output.push(operator_stack.peek());
                           operator_stack.pop();
                       }
                       operator_stack.push(token);
                       break;
                   }
                   case Parser::Token::Token_Type::LeftParen: {
                       operator_stack.push(token); break;}
                   case Parser::Token::Token_Type::RightParen: {
                       while(!operator_stack.empty()
                             &&operator_stack.peek().type != Parser::Token::Token_Type::LeftParen)
                       {
                           output.push(operator_stack.peek());
                           operator_stack.pop();
                       }
                       if(operator_stack.empty()) {
                           throw std::runtime_error("Parenthesis mismatch!");
                       }
                       else {
                           operator_stack.pop();
                       }
                       break;
                   }
                   default: throw std::runtime_error("Wrong symbol  "+token.str+" in the expr!");
               }
            }
            while(!operator_stack.empty()) {
                output.push(operator_stack.peek());
                operator_stack.pop();}
        return output;
    }
}
