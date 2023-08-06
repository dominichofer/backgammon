#include <cstdint>
#include <vector>

struct Move
{
    int8_t from{0}, to{0};
    [[nodiscard]] auto operator<=>(const Move&) const noexcept = default;
};

using Moves = std::vector<Move>;
