#include <boost/test/unit_test.hpp>
#include <sstream>
#include "lexical/Lexical.hh"

BOOST_AUTO_TEST_CASE(lexial_literal_test)
{
    std::stringstream ss{"0x123"};
    Lexical lex{ss};
    Token t = lex.getNextToken();
    BOOST_CHECK(t == lex.getCurToken());
}
