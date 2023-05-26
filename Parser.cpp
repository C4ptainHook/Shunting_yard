#include "Parser.h"

queue<Parser::Token> Parser::Parse(const char* exp) {
    queue<Token> tokenized_q;
    for (const auto* step = exp; *step; step++) {
        if(std::isblank(*step)) { } //condition to skip any space before expression itself

        //else check if char is number if it is set pointer to track first digit and move step until reach non-digit
        // then using string ctr and iterator create a substr with number. Sending taken number to the Q and reset step
        // one char backwards  because while has been triggered by next-to char
        else if(std::isdigit(*step))
        {
            auto* first_digit = step;
            while (std::isdigit(*step))
            {
                ++step;
            }
            const std::string Number = std::string(first_digit,step);
            tokenized_q.push(Parser::Token(Parser::Token::Token_Type::Number, Number));
            step--;
        }
        //getting here = input is either operator or some trash -> then if op - classify it else mark like undefined
        //special substitution for unary minus https://stackoverflow.com/questions/1593080/how-can-i-modify-my-shunting-yard-algorithm-so-it-accepts-unary-operators/5240912#5240912
        else{
             Token::Token_Type type = Token::Token_Type::Undefined;
             int precedence = -1;
             bool is_rightAssociative = false;
             bool unary = false;
             auto op = *step;
            switch (op) {
                default: break;
                case '+':  type = Token::Token_Type::Operator; precedence = 2; break;
                case '*':  type = Token::Token_Type::Operator; precedence = 3; break;
                case '/':  type = Token::Token_Type::Operator; precedence = 3; break;
                case '^':  type = Token::Token_Type::Operator; precedence = 4;  is_rightAssociative = true; break;
                case '(':  type = Token::Token_Type::LeftParen; break;
                case ')':  type = Token::Token_Type::RightParen; break;
                case '-':{
                    if(tokenized_q.empty()
                    || tokenized_q.back().type == Token::Token_Type::LeftParen
                    || tokenized_q.back().type == Token::Token_Type::Operator
                    )
                    {
                        type = Token::Token_Type::Operator;
                        unary = true;
                        op = 'm';
                        precedence = 5;
                    }
                    else {
                        type = Token::Token_Type::Operator;
                        precedence = 2;
                    }
                }
            }
            const std::string Operator = std::string(1,op);
            Token t(type, Operator, precedence, is_rightAssociative, unary);
            tokenized_q.push(t);
        }
    }
    return tokenized_q;
}