#include <utility>

namespace toycc 
{
namespace utils 
{

template <typename, typename, typename = void>
struct GenericPushBack {};

template <typename _Container, typename _Item>
struct GenericPushBack<_Container, _Item, decltype(std::declval<_Container>().push_back(0))>
{
    static void generic_push_back(_Container& c, _Item&& it)
    {
        c.push_back(std::forward<_Item>(it));
    }
};

template <typename _Container, typename _Item>
struct GenericPushBack<_Container, _Item, decltype(std::declval<_Container>().push(0))>
{
    static void generic_push_back(_Container& c, _Item&& it)
    {
        c.push(std::forward<_Item>(it));
    }
};

template <typename _Container, typename _Item>
void generic_push_back(_Container& c, _Item&& it)
{
    GenericPushBack<_Container, _Item>::generic_push_back(c, std::forward<_Item>(it));
}

/* end of namespace utils */
}
/* end of namespace toycc */
}   
