#include <benchmark/benchmark.h>
#include <object.h>
#include <ray.h>

using namespace std;

static void BM_IntersectSphereCollision(benchmark::State &state) {
  // Bench setup
  const Sphere s(10.0f, {1, 2, 3});
  const Ray ray{{20, 20, 20}, Vector3(-13, -13, -13).normalized()};

  for (auto _ : state) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
    s.intersect(ray);
#pragma clang diagnostic pop
  }
}
static void BM_IntersectSphereNoCollision(benchmark::State &state) {
  // Bench setup
  const Sphere s(10.0f, {1, 2, 3});
  const Ray ray{{20, 20, 20}, Vector3(1239, 122, 4325).normalized()};

  for (auto _ : state) {
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-result"
    s.intersect(ray);
#pragma clang diagnostic pop
  }
}

BENCHMARK(BM_IntersectSphereCollision);
BENCHMARK(BM_IntersectSphereNoCollision);
