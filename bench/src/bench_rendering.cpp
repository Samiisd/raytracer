#include <benchmark/benchmark.h>
#include <camera.h>
#include <object.h>
#include <ray.h>
#include <renderer.h>
#include <scene.h>

using namespace std;

const auto white = new UniformTexture({1, 1, 1}, 1, 5, 1, 1, 0);
const auto red = new UniformTexture({1, 0, 0}, 1, 1, 1, 10, 0);
const auto green = new UniformTexture({0, 1, 0}, 1, 7, 1, 6, 0);
const auto blue = new UniformTexture({0, 0.05, 1}, 10, 5, 1, 5, 0);

const std::vector<Object *> multipleObjects = {
    new Plane(white, Vec3(0, 1, 0).normalized(), {0, 0, 0}),
    new Plane(white, Vec3(0, 0, -1).normalized(), {0, 0, 5}),
    new Plane(red, Vec3(1, 0, 0).normalized(), {-3, 0, 0}),
    new Plane(green, Vec3(-1, 0, 0).normalized(), {5, 0, 0}),

    new Sphere(blue, 0.5, {0, .75, 0}),
    new Sphere(red, 0.5, {-1, .5, 0}),
    new Sphere(green, 0.5, {1, .5, 0}),
    new Sphere(blue, 0.5, {2, 1, -2}),
};

const vector<Light *> multipleLights = {
    new Light({1, 1, -2}),
    new Light({-1, 2, 2}),
};

static void BM_DefaultSceneRendering_1080_1920_depth3(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam, multipleObjects, multipleLights};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image A = engine.render(3, 0, false);
  }
}

static void BM_DefaultSceneRendering_1080_1920_depth1(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam, multipleObjects, multipleLights};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(1, 0, false);
  }
}

static void BM_DefaultSceneRendering_1080_1920_depth5(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam, multipleObjects, multipleLights};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(5, 0, false);
  }
}

static void
BM_DefaultSceneRendering_1080_1920_depth5_threads(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam, multipleObjects, multipleLights};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(5, 0, true);
  }
}

static void BM_DefaultSceneRendering_135_240_depth3(benchmark::State &state) {
  const size_t imHeight = 135, imWidth = 240;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam, multipleObjects, multipleLights};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(3, 0, false);
  }
}

static void BM_EmptySceneRendering_1080_1920_depth3(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene{cam};
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(3, 0, false);
  }
}

static void
BM_SceneWithOneObjectRendering_1080_1920_depth3(benchmark::State &state) {
  const size_t imHeight = 1080, imWidth = 1920;

  const Camera cam{imHeight,  imWidth, {0, 1, -4}, {0, 0, 0},
                   {0, 1, 0}, 10,      60,         16.0f / 9.0f};

  const auto scene = Scene(cam, {new Sphere(white, 1, {0, 0, 0})}, {});
  auto engine = Renderer(scene, imHeight, imWidth);

  for (auto _ : state) {
    Image a = engine.render(3, 0, false);
  }
}

BENCHMARK(BM_DefaultSceneRendering_1080_1920_depth3);
BENCHMARK(BM_DefaultSceneRendering_1080_1920_depth1);
BENCHMARK(BM_DefaultSceneRendering_1080_1920_depth5);
BENCHMARK(BM_DefaultSceneRendering_1080_1920_depth5_threads);
BENCHMARK(BM_DefaultSceneRendering_135_240_depth3);
BENCHMARK(BM_EmptySceneRendering_1080_1920_depth3);
BENCHMARK(BM_SceneWithOneObjectRendering_1080_1920_depth3);
