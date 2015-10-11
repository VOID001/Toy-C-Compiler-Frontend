SET(TOYCC_SRCS
    main.cc
    Lexical.cc
)

SUBDIRS(
    DFAGen
)

INCLUDE_DIRECTORIES(../inc)
ADD_EXECUTABLE(toycc ${TOYCC_SRCS})
