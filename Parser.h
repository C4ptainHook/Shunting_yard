#include <iostream>
#include "Queue.h"
#include "Stack.h"


class Token {
public:
    enum class Token_Type {
        Undefined,
        Number,
        Operator,
        LeftParen,
        RightParen,
    };

    Token(Token_Type type,
          const std::string& _str,
          int precedence = -1,
          bool rightAssociative = false,
          bool unary = false
    )
            : type { type }
            , str {_str }
            , precedence { precedence }
            , is_rightAssociative { rightAssociative }
            , unary { unary }
    {}

    const Token_Type type;
    const std::string str;
    const int precedence;
    const bool is_rightAssociative;
    const bool unary;
};

std::ostream& operator<<(std::ostream& os, const Token& token) {
    os << token.str;
    return os;
}

class Parser {
    std::string expression;
public:
    explicit Parser(char * _expr): expression(_expr) {}
    queue<Token<std::string>> parse_data();
};
