#include "EventDispatcher.hpp"
#include <iostream>

using namespace EventSystem;

struct HelloEvent {
		std::string message;
};

int main() {

	EventDispatcher dispatcher;

	auto token = dispatcher.subscribe<HelloEvent>([](const HelloEvent& event){
					std::cout << "Recieved event: " << event.message << std::endl;
			});

	dispatcher.dispatch(HelloEvent{"Hello from EventDispatch!"});

	dispatcher.unsubscribe<HelloEvent>(token);

	// Async dispatch example
	dispatcher.enableAsyncDispatch();
	dispatcher.subscribe<HelloEvent>([](const HelloEvent& e){
			std::cout << "[Async] "  << e.message << "\n";
	});

	dispatcher.dispatchAsync(HelloEvent{"Hello from async"});
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	dispatcher.stopAsyncDispatcher();


	return 0;
}
