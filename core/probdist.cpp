#include "probdist.h"
#include "probdist.h"
#include "probdist.h"
#include <numeric>

ProbDist& ProbDist::operator+=(const ProbDist& o) // denormalizes
{
    if (o.size() > p.size())
        p.resize(o.size(), 0.0);
    for (std::size_t i = 0; i < o.size(); i++)
        p[i] += o[i];
    return *this;
}

double ProbDist::ExpectationValue() const
{
    double E = 0.0;
    for (std::size_t i = 0; i < p.size(); i++)
        E += p[i] * i;
    return E;
}

void ProbDist::Normalize()
{
    double sum = std::accumulate(p.begin(), p.end(), 0.0);
    for (std::size_t i = 0; i < p.size(); i++)
        p[i] /= sum;
}

void ProbDist::ShiftOneUp()
{
    p.insert(p.begin(), 1, 0.0);
}

std::string to_string(const ProbDist& dist)
{
    std::string ret;
    for (std::size_t i = 0; i < dist.size(); i++)
        ret += std::to_string(i) + ": " + std::to_string(dist[i]) + '\n';
    return ret;
}
