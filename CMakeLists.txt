cmake_minimum_required(VERSION 3.16)
project(EventDispatcherProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Enable testing
include(CTest)

# Add Google Benchmark adn Catch2
include(FetchContent)

#[[ FetchContent_Declare(
	benchmark
	GIT_REPOSITORY https://github.com/google/benchmark.git
	GIT_TAG v1.7.0
	CMAKE_ARGS
		-DBENCHMARK_ENABLE_TESTING=OFF
		-DBENCHMARK_ENABLE_GTEST_TESTS=OFF
	)
]]

FetchContent_Declare(
	catch2
	GIT_REPOSITORY https://github.com/catchorg/Catch2.git
	GIT_TAG v3.5.2
	)

FetchContent_Declare(
	googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG v1.16.0
	)

find_package(benchmark REQUIRED)


FetchContent_MakeAvailable(googletest benchmark catch2)

#if(NOT HAVE_PTHREAD_AFFINITY)
	#target_compile_definitions(benchmark PRIVATE HAVE_PTHREAD_AFFINITY=0)
		#endif()

include_directories(include)

# Add benchmark target
add_executable(EventDispatcherBenchmark benchmarks/EventDispatcherBenchmark.cpp)

target_link_libraries(EventDispatcherBenchmark benchmark::benchmark)
# Add test target
add_executable(EventDispatcherTests tests/EventDispatcherTests.cpp)

target_link_libraries(EventDispatcherTests Catch2::Catch2WithMain)

include(Catch)

# Add example test
add_executable(BasicUsage examples/BasicUsage.cpp)
