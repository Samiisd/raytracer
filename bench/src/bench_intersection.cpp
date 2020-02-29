#include <benchmark/benchmark.h>
#include <object.h>
#include <ray.h>

using namespace std;

const auto white = new UniformTexture({1, 1, 1}, 1, 5, 1, 1, 0);

static void BM_IntersectSphereCollision(benchmark::State &state) {
  // Bench setup
  const Sphere s(white, 10.0f, {1, 2, 3});
  const Ray ray{{20, 20, 20}, Vec3(-13, -13, -13).normalized()};

  for (auto _ : state) {
    auto r = s.intersect(ray);
  }
}
static void BM_IntersectSphereNoCollision(benchmark::State &state) {
  // Bench setup
  const Sphere s(white, 10.0f, {1, 2, 3});
  const Ray ray{{20, 20, 20}, Vec3(1239, 122, 4325).normalized()};

  for (auto _ : state) {
    auto t = s.intersect(ray);
  }
}

BENCHMARK(BM_IntersectSphereCollision);
BENCHMARK(BM_IntersectSphereNoCollision);
