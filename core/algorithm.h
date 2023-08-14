#pragma once
#include <cstdint>
#include <string>
#include <functional>

template <std::ranges::input_range R, typename Projection = std::identity>
std::string join(const std::string& separator, R&& rng, Projection proj = {})
{
    if (std::empty(rng))
        return {};
    
    std::string ret = proj(*std::begin(rng));
    for (auto it = std::begin(rng) + 1; it != std::end(rng); ++it)
        ret += separator + proj(*it);
    return ret;
}


template <std::ranges::input_range R, typename Projection = std::identity>
std::string join(char separator, R&& rng, Projection proj = {})
{
    return join(std::string{separator}, rng, proj);
}

int64_t Binomial(int64_t n, int64_t k);

// The number of ways in which n indistinguishable balls can be distributed into k distinguishable boxes.
int64_t MultisetNumber(int64_t n, int64_t k);