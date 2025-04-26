# EventDispatcherProject

EventDispatcherProject is a modern, header-only, type-safe event dispatching system in C++20.

It supports:

🧠 Type-safe event subscription and dispatch.

⚡ Synchronous and asynchronous dispatch modes.

🛡️ Thread-safe subscriptions and unsubscriptions.

🧪 Full unit tests with Catch2.

📈 Performance benchmarks with Google Benchmark.

📦 Header-only design — easy to integrate!

/EventDispatcherProject
├── include/
│   └── EventDispatcher.hpp   # Header-only event dispatcher
├── benchmarks/
│   └── EventDispatcherBenchmark.cpp # Google Benchmark tests
├── tests/
│   └── EventDispatcherTests.cpp  # Unit tests using Catch2
├── examples/
│   └── BasicUsage.cpp   # Simple example of usage
├── CMakeLists.txt
└── README.md

📈 Benchmarks
We benchmark common operations like:

1. Subscribing callbacks

1. Dispatching events synchronously and asynchronously

1. Unsubscribing callbacks

Benchmarks are powered by Google Benchmark.


📜 License
This project is open-sourced under the MIT License.
Feel free to use it in your own projects!



✨ Future Work
Event filtering (dispatch only to certain subscribers)

Priority-based subscribers

Event propagation/cancelation

Connection to networked server events (example coming soon!)
