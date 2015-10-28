#pragma once
#include <map>
#include <type_traits>

template<typename S, typename C>
class DFA 
{
private:
    size_t state_number_;
    std::map<S, std::map<C, S>> map_;
public:
    DFA(size_t state_num, size_t case_num) 
    {
        for(size_t i = 0; i < state_num; ++i) 
        {
            for(size_t j = 0; j < case_num; ++j)
                map_[i][j] = S{};
        }
    }

    void link(const S& from, const C& cas, const S& to)
    {
        map_[from][cas] = to;
    }

    template<typename CaseSet, typename = decltype(std::declval<CaseSet>().begin())>
    void link(const S& from, CaseSet&& st, const S& to)
    {
        for(auto&& c : st)
            map_[from][c] = to;
    }

    void unlink(const S& from, const C& cas)
    {
        map_[from][cas] = S{};
    }

    template<typename CaseSet, typename = decltype(std::declval<CaseSet>().begin())>
    void unlink(const S& from, CaseSet&& st)
    {
        for(auto&& c : st)
            map_[from][c] = S{};
    }

    const std::map<S, std::map<C, S>>& getMap()
    {
        return map_;
    }
}; 
