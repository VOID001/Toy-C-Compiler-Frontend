SET(TOYCC_SRCS
    main.cc
    Lexer.cc
)

SUBDIRS(
    DFAGen
)

INCLUDE_DIRECTORIES(../inc)
ADD_EXECUTABLE(toycc ${TOYCC_SRCS})
