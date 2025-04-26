#include <catch2/catch_test_macros.hpp>
#include "EventDispatcher.hpp"

struct MyEvent {	
	int data;
};

TEST_CASE("Subscribe and Dispatch", "[EventDispatch]") {
	EventDispatcher dispatcher;
	int called = 0;
	auto token = dispatcher.subscribe<MyEvent>(
			[&](const MyEvent& e){
				called = e.data;
			});

	dispatcher.dispatch(MyEvent{123});
	REQUIRE(called == 123);
	dispatcher.unsubscribe<MyEvent>(token);
}

TEST_CASE("Unsubscribe prevents callback", "[EventDispatcher]") {

	EventDispatcher dispatcher;
	bool called = false;

	auto token = dispatcher.subscribe<MyEvent>([&](const MyEvent) {
			called = true;
	});

	dispatcher.unsubscribe<MyEvent>(token);
	dispatcher.dispatch(MyEvent{43});

	REQUIRE_FALSE(called);

}
