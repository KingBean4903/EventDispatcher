#include <benchmark/benchmark.h>
#include "EventDispatcher.hpp"

using namespace EventSystem;

struct BenchmarkEvent {
		int value;
};

EventDispatcher dispatcher;

static void BM_Subscribe(benchmark::State& state) {
		

	for (auto _ : state) {
			auto token = dispatcher.subscribe<BenchmarkEvent>
				([](const BenchmarkEvent&){});
			benchmark::DoNotOptimize(token);
	}
}

BENCHMARK(BM_Subscribe);

static void BM_Unsubscribe(benchmark::State& state) {
	
	EventDispatcher dispatche;
	std::vector<SubscriptionToken > tokens;
	for(int i = 0; i < state.range(0); ++i) {
			tokens.push_back(dispatcher.subscribe<BenchmarkEvent>
					([](const BenchmarkEvent&){}));
	}
	state.ResumeTiming();
	for (auto _ : state) {
			for (auto token : tokens) {
					dispatcher.unsubscribe<BenchmarkEvent>(token);
			}
	}
}

BENCHMARK(BM_Subscribe)->Arg(100)->Arg(100);

static void BM_SyncDispatch(benchmark::State& state) {
		EventDispatcher dispatcher;
		for (int i = 0; i < state.range(0); ++i) {
						dispatcher.subscribe<BenchMarkEvent>(
								[](const BenchmarkEvent&){});	
		}

		BenchmarkEvent evt{42};
		for (auto _ : state){
				dispatcher.dispatch(evt);
		}

}

BENCHMARK(BM_SyncDispatch)->Arg(10)->Arg(100)->Arg(1000);

static void BM_AsyncDispatch(benchmark::State& state) {
	
	EventDispatcher dispatcher;
	dispatcher.enableAsyncDispatch();
	for (int i = 0; i < std::range(0); ++i) {
			dispatcher.subscribe<BenchmarkEvent>([](const BenchmarkEvent&){});
	}

	BenchmarkEvent evt{42};
	for (auto _ : state) {
			dispatcher.dispatch(evt);
	}

	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	dispatcher.stopAsyncDispatch();

}
BENCHMARK(BM_AsyncDispatch)->Arg(10)->Arg(100)->Arg(1000);

BENCHMARK_MAIN();
