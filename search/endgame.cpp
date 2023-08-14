#include "endgame.h"
#include "endgame.h"
#include <algorithm>
#include <cmath>
#include <iterator>
#include <numeric>
#include <vector>

// Generates all possible HalfPos' where only the last given number of fields contain checkers.
// Generates 'MultisetNumber(checkers, fields+1)' positions.
template <typename OutputIt>
void generate_all(OutputIt it, int checkers, int fields, HalfPos pos = {}, int field_to_fill = 1)
{
    while (pos.Checkers() <= checkers)
    {
        if (field_to_fill == fields)
            *it++ = pos;
        else
            generate_all(it, checkers, fields, pos, field_to_fill + 1);
        pos.Checkers(field_to_fill)++;
    }
}

EndgameTable::EndgameTable(int fields, int checkers)
    : fields(fields)
    , checkers(checkers)
{
    // Generate all pos
    std::vector<HalfPos> pos;
    pos.reserve(MultisetNumber(checkers, fields + 1));
    generate_all(std::back_inserter(pos), checkers, fields);

    // Sort smallest pips to largest pips
    std::ranges::sort(pos, [](const HalfPos& l, const HalfPos& r) { return l.Pips() < r.Pips(); });

    // blocks with the same number of pips can be processed concurrently
    std::vector<int64_t> blocks;
    blocks.resize(pos.back().Pips() + 1);
    for (std::size_t i = 0; i < pos.size(); i++)
        blocks[pos[i].Pips()] = i + 1;

    // Initialize map
    pd[HalfPos{ {0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0} }] = ProbDist{ {1.0} };
    
    std::unordered_map<HalfPos, ProbDist> local_pd;
    for (std::size_t j = 1; j < blocks.size(); j++)
    {
        #pragma omp parallel private(local_pd)
        {
            #pragma omp for
            for (int64_t i = blocks[j - 1]; i < blocks[j]; i++)
            {
                ProbDist avg;
                for (const Dice& roll : AllDiceConfigs())
                {
                    ProbDist best;
                    double best_E = std::numeric_limits<double>::infinity();
                    for (const Moves& ply : pos[i].PossibleMoves(roll))
                    {
                        ProbDist novum = pd.at(Play(pos[i], ply));
                        double novum_E = novum.ExpectationValue();
                        if (novum_E < best_E)
                        {
                            best = novum;
                            best_E = novum_E;
                        }
                    }

                    avg += best;
                    if (!roll.IsPair())
                        avg += best;
                }
                avg.ShiftOneUp();
                avg.Normalize();
                local_pd[pos[i]] = std::move(avg);
            }
            #pragma omp critical
            pd.merge(local_pd);
        }
    }
}

bool EndgameTable::Contains(const HalfPos& pos) const
{
    if (pos.Checkers() > checkers)
        return false;
    if (pos.HighestChecker() > fields)
        return false;
    return true;
}

bool EndgameTable::Contains(const Position& pos) const
{
    if (!pos.IsEndgame())
        return false;
    if (!Contains(pos.Player()))
        return false;
    if (!Contains(pos.Opponent()))
        return false;
    return true;
}

ProbDist EndgameTable::BearingOffProbDist(const HalfPos& pos) const
{
    return pd.at(pos);
}

double EndgameTable::WinProbability(const Position& pos) const
{
    ProbDist P = pd.at(pos.Player());
    ProbDist O = pd.at(pos.Opponent());

    double win = 0.0;
    double not_O = 1.0;
    for (int i = 0; i < std::min(P.size(), O.size()); i++)
    {
        win += P[i] * not_O;
        not_O -= O[i];
    }
    return win;
}