#include <functional>
#include <SFML/System.hpp>

#ifndef THREAD_H_
#define THREAD_H_

namespace game
{

class thread: sf::NonCopyable
{
	std::function<void(void)> m_func;
	sf::Thread m_thread;
	bool m_running = false;
public:
	void terminate();
	void wait();
	void launch();
	const bool& is_running();

	template<typename F>
	thread(F func);

	template<typename F, typename A>
	thread(F func, A arg);

	~thread();
};

} /* namespace game */

template<typename F>
inline game::thread::thread(F func) :
		m_thread([this,func]()
		{	this->m_running = true;func();this->m_running = false;})
{
}

template<typename F, typename A>
inline game::thread::thread(F func, A arg) :
		m_thread([this,func](A arg)
		{	this->m_running = true;func(arg);this->m_running = false;})
{
}

#endif /* THREAD_H_ */
