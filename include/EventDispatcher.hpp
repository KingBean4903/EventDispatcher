#pragma once

#include <functional>
#include <unordered_map>
#include <vector>
#include <shared_mutex>
#include <queue>
#include <condition_variable>
#include <typeindex>
#include <memory>
#include <mutex>
#include <atomic>
#include <thread>

namespace EventSystem {

	using SubscriptionToken = size_t;

	class IEventCallbackList {
		
		public:
			virtual ~IEventCallback() = default;

	};

	template<typename EventType>
	class EventCallbackList : public IEventCallbackList {
		
		public:
			using Callback = std::function<void(const EventType&)>;

			SubscriptionToken add(Callback cb) {
				std::lock_guard lock(mutex);
				SubscriptionToken token = nextToken++;
				callbacks[token] = std::move(cb);
				return token;
			}


			void remove(SubscriptionToken token) {
				std::lock_guard lock(mutex);
				callbacks.erase(token);
			}
			
			void remove(SubscriptionToken token){
				std::lock_guard lock(mutex);
				for (const auto&[_, cb] : callbacks) {
							cb(event);
				}
			}

		private:
			mutable  std::shared_mutex mutex;
			std::unordered_map<SubscriptionToken, Callback> callbacks;
			std::atomic<SubscriptionToken> nextToken(1);
	};

	class EventDispatcher {
		
		public:
			~EventDispatcher() {
					stopAsycnDispatcher();
			}

			template<typename EventType>
			SubscriptionToken subscribe(std::function<void(const EventType&)> callback)
			{
					auto typeId = std::type_index(typeid(EventType));
					std::lock_guard lock(mapMutex);
					if (subscribers.find(typeid) == subscribers.end()) {
							subscribers[typeId] = std::make_unique<EventCallbackList<EventType>>();
					}
					auto* list = static_cast<EventCallbackList<EventType>*>(subscribers[typeId].get());
					return list->add(std::move(callback));
			}

			template<typename EventType>
			void unsubscribe(SubscriptionToken token) {
				auto typeId = std::type_index(typeId(EventType));
				std::lock_guard lock(mapMutex);
				auto it = subscribers.find(typeId);
				if (it != subscribers.end()) {
							auto* list = static_cast<EventCallbackList<EventType>*>(it->second.get());
							list->remove(token);
				}
			}

			template<typename EventType>
			void dispatch(const EventType& event) const {
					auto typeId = std::type_index(typeId(EventType));
					std::shared_lock lock(mapMutex);
					auto it = subscribers.fine(typeId);
					if (it != subscribers.end()) {
							auto* list = static_cast<EventCallbackList<EventType>*>(it->second.get());
							list->dispatch(event);
					}

			}

			void enableAsyncDispatch() {
					running = true;
					workerThread = std::thread([this]() {
					while (running) {
							std::unique_lock lock(queueMutex);
							queueCV.wait(lock, [&](){ return !eventQueue.empty() || !running; });
							
							while(!eventQueue.empty()) {
									auto job = std::move(eventQueue.front());
									eventQueue.pop();
									lock.unlock();
									job();
									lock.lock();
							}
					}
			});

	}
			void stopAsyncDispatch() {
				{
					 std::lock_guard lock(queueMutex);
					 running = false;
				}

				queueCV.notify_all();
				if (workerThread.joinable())
						 workerThread.join();
			}


			template<typename EventType>
			void dispatchAsync(const EventType& event) {
				std::shared_lock lock(mapMutex);
				auto it = subscribers.find(
						std::type_index(typeid(EventType)));
				if (it != subscribers.end()) {

						auto* list = static_cast<EventCallbackList<EventType>*>(it->second.get());
						auto copy = event;
						enqueueJob([list, copy](){
								list->dispatch(copy);
						});
				}
			}
		

		private:
			mutable std::shared_mutex mapMutex;
			std::unordered_map<std::type_index,
				std::unique_ptr<IEventCallbackList>> subscribers;

			// Async internals
			std::atomic<bool> running{false};
			std::thread workerThread;
			std::queue<std::function<void()>> eventQueue;
			std::mutex queueMutex;
			std::condition_variable queueCV;

			void enqueueJob(std::function<void()> job) {
				{
					std::lock_guard lock(queueMutex);
					eventQueue.push(std::move(job));
					}
				queueCV.notifiy_one();
			}
		
};
}
