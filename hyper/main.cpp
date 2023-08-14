#include "core/core.h"
#include "search/search.h"
#include <iostream>
#include <unordered_map>
#include <random>
#include <vector>

int main(int argc, char* argv[])
{
	uint64_t sum = 0;
	for (int i = 0; i < 25; i++)
		sum += MultisetNumber(15, i + 1) * MultisetNumber(15, 25 - i);
	std::cout << sum;
	return 0;

	//EndgameTable table(12, 3);
	//Position start{ {0, -1,-1,-1,0,0,0, 0,0,0,0,0,0, 0,0,0,0,0,0, 0,0,0,1,1,1, 0} };

	//std::mt19937_64 rng;
	//std::uniform_real_distribution<double> dist{ -1.0, 1.0 };
	//std::unordered_map<Position, double> positions;
	//int count = 0;
	//for (int a = off; a <= bar; a++)
	//	for (int b = off; b <= a; b++)
	//		for (int c = off; c <= b; c++)
	//			for (int d = off; d <= bar; d++)
	//				if (d == off || d == bar || (d != a && d != b && d != c))
	//					for (int e = off; e <= d; e++)
	//						if (e == off || e == bar || (e != a && e != b && e != c))
	//							for (int f = off; f <= e; f++)
	//								if (f == off || f == bar || (f != a && f != b && f != c))
	//								{
	//									std::array<int8_t, 26> fields;
	//									fields.fill(0);
	//									if (a != off)
	//										fields[a]++;
	//									if (b != off)
	//										fields[b]++;
	//									if (c != off)
	//										fields[c]++;
	//									if (d != bar)
	//										fields[d]--;
	//									if (e != bar)
	//										fields[e]--;
	//									if (f != bar)
	//										fields[f]--;
	//									Position pos{ fields };
	//									if (table.Contains(pos))
	//									{
	//										positions[pos] = table.WinProbability(pos);
	//										count++;
	//									}
	//									else
	//										positions[pos] = dist(rng);
	//								}


	//std::cout << positions.size() << "\n" << count;
	//return 0;
}