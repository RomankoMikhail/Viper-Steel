#include <functional>
#include <SFML/System.hpp>

#ifndef THREAD_H_
#define THREAD_H_

#include <memory>

namespace game
{

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

typedef std::shared_ptr<thread> thread_ptr;

} /* namespace game */



template<typename F>
inline game::thread::thread(F func) :
		m_thread([this,func]()
		{	this->m_running = true;func();this->m_running = false;})
{
}

template<typename F, typename A>
inline game::thread::thread(F func, A arg) :
		m_thread([this,func,arg]()
		{	this->m_running = true;func(arg);this->m_running = false;})
{
}

template<typename C>
inline game::thread::thread(void (C::*function)(), C* object) :
	m_thread([this,function,object]()
		{	this->m_running = true;(object->*function)();this->m_running = false;})
{
}

#endif /* THREAD_H_ */
