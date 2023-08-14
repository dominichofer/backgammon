#pragma once
#include <compare>
#include <cstddef>
#include <string>
#include <vector>

class ProbDist
{
    std::vector<double> p{}; // Probability
public:
    ProbDist() noexcept = default;
    explicit ProbDist(std::vector<double> p) : p(std::move(p)) {}

    bool operator==(const ProbDist& o) const { return p == o.p; }
    bool operator!=(const ProbDist& o) const { return p != o.p; }

    double operator[](std::size_t i) const { return p[i]; }
    ProbDist& operator+=(const ProbDist&); // denormalizes

    std::size_t size() const { return p.size(); }
    double ExpectationValue() const;

    void Normalize();
    void ShiftOneUp();
};

std::string to_string(const ProbDist&);
