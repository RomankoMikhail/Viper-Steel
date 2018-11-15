#include "thread.h"

namespace game
{
void thread::terminate()
{
	m_thread.terminate();
	m_running = false;
}

void thread::wait()
{
	m_thread.wait();
}

void thread::launch()
{
	m_running = true;
	m_thread.launch();
}

const bool& thread::is_running()
{
	return m_running;
}


thread::~thread()
{
	terminate();
}
} /* namespace game */

