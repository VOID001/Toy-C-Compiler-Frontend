#include <iostream>
#include <fstream>
#include <map>
#include "DFA.hh"

using namespace std;
#define STATE_NUM 27
#define CASE_NUM 128

using state_t = unsigned short;
using case_t = unsigned char;

void dump_content(std::ostream& is)
{
    DFA<state_t, case_t> dfa(STATE_NUM, CASE_NUM);
    
    #define L(From, Case, To)           \
    do {                                \
        dfa.link(From, Case, To);       \
    } while(0)

    #define UL(From, Case)              \
    do {                                \
        dfa.unlink(From, Case);         \
    } while(0)

    std::string any_char;
    for(unsigned char i = 0; i < 128; ++i)
        any_char.push_back(i);

    std::string alpha;
    for(unsigned char i = 'A'; i <= 'z'; ++i)
        alpha.push_back(i);

    std::string octal = "01234567";
    std::string hex = "0123456789abcdefABCDEF";
    std::string number = "0123456789";

    L(1, '\'', 2);
    L(1, std::string("+-"), 3);
    L(1, '0', 18);
    L(1, std::string("123456789"), 19);
    
    L(2, any_char, 5);
    UL(2, '\\');
    L(2, '\\', 4);

    L(3, '0', 18);
    L(3, std::string("123456789"), 19);

    L(4, alpha, 9);
    UL(4, 'x');
    L(4, 'x', 6);
    L(4, octal, 10);

    L(5, '\'', 17);

    L(6, hex, 7);

    L(7, hex, 8);
    L(7, '\'', 17);

    L(8, '\'', 17);
    L(9, '\'', 17);
    L(10, '\'', 17);
    L(11, '\'', 17);
    L(12, '\'', 17);

    L(13, hex, 13);
    L(13, std::string("Uu"), 24);
    L(13, std::string("Ll"), 25);

    L(14, number, 14);
    L(14, '.', 22);

    L(15, std::string("+-"), 16);
    L(15, number, 20);

    L(16, number, 20);    
    
    L(18, 'x', 13);
    L(18, std::string("89"), 14); 
    L(18, std::string("Ee"), 15); 
    L(18, octal, 23);
    
    L(19, std::string("Ee"), 15);
    L(19, number, 19);
    L(19, '.', 22);
    L(19, std::string("Uu"), 24);
    L(19, std::string("Ll"), 25);
    
    L(20, number, 20);
    L(20, std::string("Ff"), 21);
    
    L(22, std::string("Ff"), 21);
    L(22, number, 22);

    L(23, std::string("89"), 14);
    L(23, std::string("Ee"), 15);
    L(23, octal, 23);
    L(23, std::string("Uu"), 24);
    L(23, std::string("Ll"), 25);

    L(24, std::string("Ll"), 26);

    L(25, std::string("Uu"), 26);
    
    is << "#include \"lexer/Lexer.hh\"" << std::endl << std::endl;
    is << "Lexer::state_t Lexer::dfa_trans_table_[][128] =" << std::endl;

    auto lmap = dfa.getMap();

    is << "{" << std::endl;
    for(size_t i = 0; i < STATE_NUM; ++i) {
        is << "\t{" << std::endl;
        is << "\t\t";
        for(size_t j = 0; j < lmap[i].size() / 4 * 1; ++j) {
            is << lmap[i][j];
            is << ",";
        }
        is << std::endl << "\t\t";
        for(size_t j = lmap[i].size() / 4 * 1; j < lmap[i].size() / 4 * 2; ++j) {
            is << lmap[i][j];
            is << ",";
        }
        is << std::endl << "\t\t";
        for(size_t j = lmap[i].size() / 4 * 2; j < lmap[i].size() / 4 * 3; ++j) {
            is << lmap[i][j];
            is << ",";
        }
        is << std::endl << "\t\t";
        for(size_t j = lmap[i].size() / 4 * 3; j < lmap[i].size() / 4 * 4; ++j) {
            is << lmap[i][j];
            if(j != CASE_NUM - 1)
                is << ",";
        }
        is << std::endl;
        is << "\t}";
        if(i != STATE_NUM - 1)
            is << ",";
        is << std::endl;
    }
    is << "};" << std::endl;
}

int main()
{
    std::ofstream ofs{"src/Lexer.cc"};
    if(!ofs)
    {
        std::cerr << "can't open src/Lexer.cc" << std::endl;
        return -1;
    }
    dump_content(ofs);
}
