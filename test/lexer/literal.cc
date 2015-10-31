#include <boost/test/unit_test.hpp>
#include <sstream>
#include "lexer/Lexer.hh"

BOOST_AUTO_TEST_CASE(lexial_literal_test0)
{
    std::stringstream ss{"0x123u"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::UINT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test1)
{
    std::stringstream ss{"0x123U"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::UINT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test2)
{
    std::stringstream ss{"0x123L"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::LONG_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test3)
{
    std::stringstream ss{"0x123Lu"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::ULONG_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test4)
{
    std::stringstream ss{"0"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test5)
{
    std::stringstream ss{"12345"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test6)
{
    std::stringstream ss{"12345."};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::DOUBLE_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test7)
{
    std::stringstream ss{"12345.0f"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::FLOAT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test8)
{
    std::stringstream ss{R"('\x3')"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test9)
{
    std::stringstream ss{R"('\t')"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test10)
{
    std::stringstream ss{"0x123"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test11)
{
    std::stringstream ss{"13e12"};
    Lexer lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::DOUBLE_L); 
}


