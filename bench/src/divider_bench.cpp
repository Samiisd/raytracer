#include <benchmark/benchmark.h>
#include <division.h>

using namespace std;

using LL = long long;

static void BM_Division(benchmark::State& state) {
  // Bench setup
  LL numerator = 1234234L;
  LL denominator = 320483290482309L;
  auto d = Division(Fraction{numerator, denominator});

  for (auto _ : state) {
    // Function to bench

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
    d.divide();
#pragma clang diagnostic pop
  }
}
BENCHMARK(BM_Division);

