#include <string>
#include <functional>

template <typename Iterable, typename Projection = std::identity>
std::string join(const std::string& separator, const Iterable& iterable, Projection proj = {})
{
    if (std::empty(iterable))
        return {};
    
    std::string ret = proj(*std::begin(iterable));
    for (auto it = std::begin(iterable) + 1; it != std::end(iterable); ++it)
        ret += separator + proj(*it);
    return ret;
}


template <typename Iterable, typename Projection = std::identity>
std::string join(char separator, const Iterable& iterable, Projection proj = {})
{
    return join(std::string{separator}, iterable, proj);
}