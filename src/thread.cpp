#include "thread.h"

namespace game
{
void thread::terminate()
{
	m_thread.terminate();
	m_running = false;
	m_terminated = true;
}

void thread::wait()
{
	m_thread.wait();
}

void thread::launch()
{
	m_terminated = false;
	m_running = true;
	m_thread.launch();
}

const bool& thread::is_running()
{
	return m_running;
}

const bool& thread::is_terminated()
{
	return m_terminated;
}

thread::~thread()
{
	terminate();
}
} /* namespace game */

