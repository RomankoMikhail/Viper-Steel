#include <functional>
#include <SFML/System.hpp>
#include <plog/Log.h>

#include <memory>
#include <functional>
#include <atomic>
#include <pthread.h>

#ifndef THREAD_H_
#define THREAD_H_

namespace game
{
class thread
{
	std::function<void(void)> m_callback;

	std::atomic<bool> m_finished, m_terminated;
	pthread_t m_thread;
	pthread_attr_t m_attr;

	void* _second_payload()
	{
		m_finished = false;
		m_terminated = false;
		pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
		m_callback();
		m_finished = true;
		return NULL;
	}
	static void* _fisrt_payload(void* context)
	{
		void* res = ((thread*) context)->_second_payload();
		return res;
	}

	thread();
public:
	template<typename F>
	thread(F function)
	{
		m_thread = 0;
		m_callback = function;
	}
	template<typename F, typename A>
	thread(F function, A arg)
	{
		m_thread = 0;
		m_callback = std::bind(function, arg);
	}
	template<typename C>
	thread(void (C::*function)(), C *object)
	{
		m_thread = 0;
		m_callback = std::bind(function, object);
	}

	~thread()
	{
		terminate();
	}

	const bool is_terminated()
	{
		return m_terminated;
	}

	const bool is_running()
	{
		return !m_finished;
	}
	const bool is_finished()
	{
		return !m_finished;
	}

	void launch()
	{
		m_finished = false;
		m_terminated = false;
		pthread_attr_init(&m_attr);
		pthread_attr_setdetachstate(&m_attr, PTHREAD_CREATE_JOINABLE);
		pthread_create(&m_thread, &m_attr, &thread::_fisrt_payload, this);
		pthread_attr_destroy(&m_attr);
	}

	void wait()
	{
		void *status;
		pthread_join(m_thread, &status);
	}

	void terminate()
	{
		pthread_cancel(m_thread);
		pthread_kill(m_thread, 1);
		pthread_kill(m_thread, 2);
		pthread_kill(m_thread, 3);
		pthread_kill(m_thread, 4);
		pthread_kill(m_thread, 5);
		pthread_kill(m_thread, 6);
		pthread_kill(m_thread, 7);
		pthread_kill(m_thread, 8);
		pthread_kill(m_thread, 9);
		wait();
		m_finished = true;
		m_terminated = true;
	}
};
/*
 class thread: sf::NonCopyable
 {
 std::function<void(void)> m_func;
 sf::Thread m_thread;
 bool m_running = false;
 bool m_terminated = false;
 public:
 void terminate();
 void wait();
 void launch();
 const bool& is_running();
 const bool& is_terminated();

 template<typename F>
 thread(F func);

 template<typename F, typename A>
 thread(F func, A arg);

 template<typename C>
 thread(void(C::*function)(), C *object);

 ~thread();
 };
 */
typedef std::shared_ptr<thread> thread_ptr;

} /* namespace game */

/*
 template<typename F>
 inline game::thread::thread(F func) :
 m_thread([this,func]()
 {	this->m_running = true;func();this->m_running = false;})
 {
 LOG_INFO << "Thread started";
 }

 template<typename F, typename A>
 inline game::thread::thread(F func, A arg) :
 m_thread([this,func,arg]()
 {	this->m_running = true;func(arg);this->m_running = false;})
 {
 LOG_INFO << "Thread started";
 }

 template<typename C>
 inline game::thread::thread(void (C::*function)(), C* object) :
 m_thread([this,function,object]()
 {	this->m_running = true;(object->*function)();this->m_running = false;})
 {
 LOG_INFO << "Thread started";
 }
 */
#endif /* THREAD_H_ */
