#pragma once

class Token 
{
private:
    int kind_;
    int line_;
    int pos_;

public:
    enum
    {
        INT_L, UINT_L, LONG_L, ULONG_L, FLOAT_L, DOUBLE_L
    };

    Token(int kind = -1, int line = -1, int pos = -1)
        : kind_{kind}, line_{line}, pos_{pos}
    {}

    int getLineNumber() const
    {
        return line_;
    }
    
    int getPosNumber() const
    {
        return pos_;
    }

    operator int()
    {
        return kind_;
    }
};
