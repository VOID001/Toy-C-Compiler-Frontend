#include <boost/test/unit_test.hpp>
#include <sstream>
#include "lexical/Lexical.hh"

BOOST_AUTO_TEST_CASE(lexial_literal_test0)
{
    std::stringstream ss{"0x123u"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::UINT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test1)
{
    std::stringstream ss{"0x123U"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::UINT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test2)
{
    std::stringstream ss{"0x123L"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::LONG_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test3)
{
    std::stringstream ss{"0x123Lu"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::ULONG_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test4)
{
    std::stringstream ss{"0"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test5)
{
    std::stringstream ss{"12345"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test6)
{
    std::stringstream ss{"12345."};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::DOUBLE_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test7)
{
    std::stringstream ss{"12345.0f"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::FLOAT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test8)
{
    std::stringstream ss{R"('\x3')"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test9)
{
    std::stringstream ss{R"('\t')"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test10)
{
    std::stringstream ss{"0x123"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::INT_L); 
}

BOOST_AUTO_TEST_CASE(lexial_literal_test11)
{
    std::stringstream ss{"13e12"};
    Lexical lex{ss};
    BOOST_CHECK(lex.getNextToken() == Token::DOUBLE_L); 
}


