#include "benchmark/benchmark.h"
#include "search/search.h"

void EndgameTableInit(benchmark::State& state)
{
	for (auto _ : state)
		EndgameTable(state.range(0));
}
BENCHMARK(EndgameTableInit)->Unit(benchmark::kMillisecond)->DenseRange(1, 8, 1);

BENCHMARK_MAIN();