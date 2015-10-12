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

    Token() = default;

    Token(int kind, int line, int pos)
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

    bool operator==(const Token& t) const
    {
        return kind_ == t.kind_;
    }

    operator int()
    {
        return kind_;
    }
};
