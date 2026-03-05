#include <unordered_map>
#include <condition_variable>
#include <thread>
#include <functional>
#include <atomic>
#include <iostream>
#include <mutex>
#include <queue>
#include <optional>

enum EventType {
    EVENT_TYPE_1,
    EVENT_TYPE_2,
    EVENT_TYPE_3,
};

using EventHandler = std::function<void(const EventType)>;

class EventLoop {
    bool running_;
    std::unordered_map<EventType, EventHandler> eventHandlers_;

    bool eventReceived_;
    EventType incomingEvent_;
    std::mutex mutex_;
    std::condition_variable cv_;

    private: 
        std::queue<EventType> eventQueue_;

    public: 
        EventLoop() : running_{true} {
            RegisterHandler(EventType::EVENT_TYPE_3, [this](const EventType e){
                std::cout << "Stop" << std::endl;
                this->running_ = false;
            });
        }

        void RegisterHandler(EventType e, EventHandler handler) {
            eventHandlers_[e] = handler;
        }

        std::optional<EventType> GetNextEvent() {
            std::unique_lock<std::mutex> lock{mutex_};
            cv_.wait(lock, [this]() {
                return !eventQueue_.empty();
            });

            cv_.wait_for(lock, std::chrono::milliseconds{100}, [this](){
                return !eventQueue_.empty();
            });

            if (!eventQueue_.empty()) {
                EventType e = eventQueue_.front();
                eventQueue_.pop();
                return e;
            }

            return std::nullopt;
        }

        void PostEvent(EventType e) {
            std::unique_lock<std::mutex> lock{mutex_};

            eventQueue_.push(e);

            cv_.notify_one();
        }

        void HandleEvent(EventType e) {
            auto it = eventHandlers_.find(e);

            if (it != eventHandlers_.end()) {
                it->second(e);
            }
        }

        void Run() {
            while(running_) {
                std::cout << "[main] waiting for the event...\n";
                std::optional<EventType> e = GetNextEvent();
                if (e) {
                    HandleEvent(*e);
                }
            }
        }

        void Stop() {
            running_ = false;
            PostEvent(EventType::EVENT_TYPE_3);
        }
};

int main() {
    EventLoop loop;

    auto handler = [](const EventType e) {
        std::cout << "[main] Received event: " << static_cast<int>(e) << std::endl;
    };

    auto thread_ = std::thread([&loop]() {

        std::chrono::milliseconds intvl{2000};

        std::this_thread::sleep_for(intvl);
        loop.PostEvent(EventType::EVENT_TYPE_1);

        std::this_thread::sleep_for(intvl);
        loop.PostEvent(EventType::EVENT_TYPE_2);

        std::this_thread::sleep_for(intvl);
        loop.Stop();
    });

    loop.RegisterHandler(EventType::EVENT_TYPE_1, handler);
    loop.RegisterHandler(EventType::EVENT_TYPE_2, handler);

    loop.Run();

    if (thread_.joinable()) {
        thread_.join();
    }

    return 0;
}