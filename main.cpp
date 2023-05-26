#include "Parser.h"
#include "Shunting_yard.h"
#include "Evaluator.h"

int main() {
queue<Parser::Token> parsed_q = Parser::Parse("5-6+4");
queue<Parser::Token> postfix_q = Algorithm::Shunting_yard(parsed_q);
int result = Evaluator::evaluate_expression(postfix_q);
std::cout<<result;
}
