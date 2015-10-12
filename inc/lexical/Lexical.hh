#pragma once
#include <type_traits>
#include <iostream>
#include <vector>
#include <utility>
#include <functional>
#include "Token.hh"

class Lexical {
private:
    using state_t = unsigned short;
    using case_t = unsigned char;
    state_t cur_state_ = 1;
    std::string token_buf_;
    std::istream& input_stream_;
    Token cur_token_;
    unsigned long integer_value_;
    double float_value_;
    std::string identifier_;
    static state_t dfa_trans_table_[][128];
    std::vector<std::function<Token()>> reaction_map_ = 
    { 
    /*0*/   [this]{ std::cout << "0" << std::endl; return Token{}; }
    };  

public:
    Lexical(std::istream& is) : input_stream_{is} {}

    /**
     * \brief discard current token and update it to next token in stream
     * \return current token(after update).
     */ 
    Token getNextToken()
    {
        while(true) 
        {
            state_t next_state = 0;
            int c = input_stream_.get();
            case_t next_case = index_of(c);
            if((next_state = dfa_trans_table_[cur_state_][next_case])) 
            {
                token_buf_.push_back(c);
                cur_state_ = next_state;          
            }
            else
            {
                cur_token_ = reaction_map_[cur_state_]();
                token_buf_.clear();
                reset_state();
                input_stream_.unget(); 
                return cur_token_;
            }
        }
    }

    /**
     * \brief get current token.
     * \return current token.
     */ 
    Token getCurToken() 
    {
        return cur_token_;
    }

    template <typename _Integer>
    _Integer getInteger()
    {
        static_assert(std::is_integral<_Integer>::value, 
            "template param of getInteger should be a integer type");
        return static_cast<_Integer>(integer_value_);
    }

    template <typename _Float>
    _Float getFloat()
    {
        static_assert(std::is_same<float, _Float>::value || std::is_same<double, _Float>::value, 
            "template param of getFloat should be float or double type");
        return static_cast<_Float>(float_value_);
    }

private:
    case_t index_of(int c)
    {
        if(c > 0 && c < 128) return c;
        return 0;
    }

    void reset_state()
    {
        cur_state_ = 1;
    }
};
