#include <boost/test/unit_test.hpp>
#include <vector>
#include <queue>
#include <string>
#include "utils.hh"

using namespace toycc::utils;

BOOST_AUTO_TEST_CASE(generic_push_back_test)
{
    std::vector<int> vec;
    generic_push_back(vec, 1);
    BOOST_REQUIRE(vec.size() == 1);
    BOOST_CHECK(vec[0] == 1);
    generic_push_back(vec, 2);
    BOOST_REQUIRE(vec.size() == 2);
    BOOST_CHECK(vec[1] == 2);

    std::queue<std::string> que;
    generic_push_back(que, "a");
    BOOST_REQUIRE(que.size() == 1);
    generic_push_back(que, "b");
    BOOST_REQUIRE(que.size() == 2);
}
