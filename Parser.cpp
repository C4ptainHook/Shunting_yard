#include "Parser.h"

template<class T>
Token<T>::Token(bool criterion, unsigned short _prior, T _val) {
    enum Rank{
        AdSub = 1;
        MultDiv =
    };
    is_operand=criterion;
    priority=_prior;
    value=_val;
}
queue<Token<std::string>> Parser::parse_data(c) {
    queue<Token<std::string>> parsed_expr;



}