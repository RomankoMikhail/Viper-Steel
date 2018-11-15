#include "thread_pool.h"
#include <plog/Log.h>

struct thread_type
{
	std::shared_ptr<game::thread> thread;
	sf::Time remaing_time;
	bool expire;
};

std::vector<thread_type> threads;
sf::Mutex mutex;
sf::Clock threads_clock;

void thread_pool_add(std::shared_ptr<game::thread> thread, sf::Time time)
{
	bool flag = true;
	while (flag)
	{
		mutex.lock();

		if (threads.size() < max_threads)
		{
			thread_type t;
			t.thread = thread;
			t.remaing_time = time;
			if (time != sf::Time::Zero)
				t.expire = true;
			else
				t.expire = false;

			t.thread->launch();
			threads.push_back(t);
			flag = false;
		}
		mutex.unlock();
		sf::sleep(sf::milliseconds(10));
	}
}

int thread_pool_process()
{

	mutex.lock();

	sf::Time delta = threads_clock.restart();

	auto t = std::begin(threads);

	while (t != std::end(threads))
	{
		if (t->expire)
		{
			t->remaing_time -= delta;
		}
		if (t->remaing_time < sf::Time::Zero || t->thread->is_running() == false)
		{
			if(t->remaing_time < sf::Time::Zero)
				LOG_INFO << "Thread #" << t - std::begin(threads) << " terminated by time";
			else
				LOG_INFO << "Thread #" << t - std::begin(threads) << " ended";
			t = threads.erase(t);
			continue;
		}
		++t;
	}
	int running_threads = threads.size();
	mutex.unlock();
	return running_threads;
}
