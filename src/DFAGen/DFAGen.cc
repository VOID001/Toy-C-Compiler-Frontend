#include <iostream>
#include <fstream>
#include <map>

using namespace std;
#define STATE_NUM 15
#define CASE_NUM 128

using state_t = unsigned short;
using case_t = unsigned char;

case_t index_of(int c) {
	if(c > 0 && c < 128) return c;
	return 0;
}

void dump_content(std::ostream& is)
{
	map<state_t, map<case_t, state_t>> lmap;

	for(size_t i = 0; i < STATE_NUM; ++i) {
		for(size_t j = 0; j < CASE_NUM; ++j)
			lmap[i][j] = 0;
	}

	#define T(From, Case, To)		\
	do {					\
		lmap[From][index_of(Case)] = To;	\
	} while(0)

	std::string alpha_symbol("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz_+-*/\\=<>!&");
	std::string alpha_number_symbol("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_+-*/\\=<>!&");
	std::string number("0123456789");

	for(char c : alpha_symbol) {
		T(1, c, 2);
		T(3, c, 2);
		T(4, c, 2);
		T(5, c, 2);
	}
	for(char c : alpha_number_symbol)
		T(2, c, 2);
	for(char c : number) {
		T(1, c, 4);
		T(3, c, 4);
		T(4, c, 4);
		T(5, c, 5);
	}
	for(unsigned char c = 0; c < CASE_NUM; ++c) {
		T(10, c, 10);
		T(12, c, 12);
		T(14, c, 12);
	}
	T(1, '"', 12);
	T(1, '-', 3);
	T(1, ';', 10);
	T(1, ' ', 11);
	T(1, '\t', 11);
	T(1, '\n', 11);
	T(1, '{', 6);
	T(1, '}', 7);
	T(1, '(', 8);
	T(1, ')', 9);
	T(4, '.', 5);
	T(12, '"', 13);
	T(12, '\\', 14);
	T(10, '\n', 11);

    is << "#include \"lexical/Lexical.hh\"" << std::endl << std::endl;
    is << "Lexical::state_t Lexical::dfa_trans_table_[][128] =" << std::endl;

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
