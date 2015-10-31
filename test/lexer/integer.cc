#include <boost/test/unit_test.hpp>
#include <sstream>
#include "lexer/Lexer.hh"

#include <iostream>

BOOST_AUTO_TEST_CASE(lexial_integer_test0)
{
    std::stringstream ss{"12345"};
    Lexer lex{ss};
    BOOST_REQUIRE(lex.getNextToken() == Token::INT_L);
std::cout << lex.getInteger<unsigned long>() << std::endl;
    BOOST_CHECK(lex.getInteger<int>() == 12345);
}
