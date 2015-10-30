#include <iostream>
#include <fstream>
#include <map>
#include "DFA.hh"

using namespace std;
#define STATE_NUM 15
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

	std::string alpha_symbol("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_+-*/\\=<>!&");
	std::string alpha_number_symbol("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_+-*/\\=<>!&");
	std::string number("0123456789");

    std::string all_chars;
    for(unsigned char i = 0; i < 128; ++i)
        all_chars.push_back(i);

    L(1, alpha_symbol, 2);
    L(3, alpha_symbol, 2);
    L(4, alpha_symbol, 2);
    L(5, alpha_symbol, 2);

    L(2, alpha_number_symbol, 2);

    L(1, number, 4);
    L(3, number, 4);
    L(4, number, 4);
    L(5, number, 4);
    
    L(10, all_chars, 10);
    L(12, all_chars, 12);
    L(14, all_chars, 12);
    
	L(1, '"', 12);
	L(1, '-', 3);
	L(1, ';', 10);
	L(1, ' ', 11);
	L(1, '\t', 11);
	L(1, '\n', 11);
	L(1, '{', 6);
	L(1, '}', 7);
	L(1, '(', 8);
	L(1, ')', 9);
	L(4, '.', 5);
	L(12, '"', 13);
	L(12, '\\', 14);
	L(10, '\n', 11);

    is << "#include \"lexical/Lexical.hh\"" << std::endl << std::endl;
    is << "Lexical::state_t Lexical::dfa_trans_table_[][128] =" << std::endl;

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
    std::ofstream ofs{"src/Lexical.cc"};
    if(!ofs)
    {
        std::cerr << "can't open src/Lexical.cc" << std::endl;
        return -1;
    }
    dump_content(ofs);
}
