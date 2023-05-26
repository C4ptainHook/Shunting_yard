#pragma once
#include "Parser.h"
#include "Stack.h"

namespace Algorithm {
    queue<Parser::Token> Shunting_yard(queue<Parser::Token>& parsed_q) {
        queue<Parser::Token> output;
        stack<Parser::Token> operator_stack;
        queue<Parser::Token>::iterator it;
            for(it = parsed_q.begin(); it!=parsed_q.end(); ++it) {
               switch((*it).type){

                   case Parser::Token::Token_Type::Number: {
                       output.push(*it);
                       break;}

                   case Parser::Token::Token_Type::Operator: {
                       while(!operator_stack.empty()
                       &&operator_stack.peek().precedence <= (*it).precedence )
                       {
                           output.push(operator_stack.peek());
                           operator_stack.pop();
                       }
                       operator_stack.push(*it);
                       break;
                   }

                   case Parser::Token::Token_Type::LeftParen: {
                       operator_stack.push(*it); break;}

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
                   default: {throw std::runtime_error("Wrong symbol  "+(*it).str+" in the expr!");}
               }
            }
            while(!operator_stack.empty()) {
                output.push(operator_stack.peek());
                operator_stack.pop();}
        return output;
    }
}
