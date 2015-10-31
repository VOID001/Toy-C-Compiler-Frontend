SET(TEST_SOURCES
	test.cc
    utils/GenericPushBack.cc
    lexer/literal.cc
    lexer/integer.cc
    ../src/Lexer.cc
)

ADD_EXECUTABLE(toycc_test ${TEST_SOURCES})
INCLUDE_DIRECTORIES(../inc)
ADD_CUSTOM_TARGET(run_test COMMAND ${CMAKE_BINARY_DIR}/test/toycc_test DEPENDS toycc_test WORKING_DIRECTORY ${CMAKE_SOURCE_DIR})
