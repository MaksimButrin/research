#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>

class Timer 
{
public:
	Timer() {};
	~Timer() {};

public:
	template<typename Function>
	void setTimeout(Function function, int delay);

	template<typename Function>
	void setInterval(Function function, int interval);

	void stop();

private:
	bool clear = false;
	std::atomic<bool> _active{ true };
};

template<typename Function>
inline void Timer::setTimeout(Function function, int delay)
{
	_active = true;
	std::thread t([=]() {
		if (!_active.load()) return;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		if (!_active.load()) return;
		function();
	});
	t.detach();
}

template<typename Function>
inline void Timer::setInterval(Function function, int interval)
{
	_active = true;
	std::thread t([=]() {
		while (_active.load()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			if (!_active.load()) return;
			function();
		}
	});
	t.detach();
}

