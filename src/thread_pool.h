#ifndef THREAD_POOL_H_
#define THREAD_POOL_H_

#include <array>
#include <SFML/System.hpp>
#include "thread.h"
#include <mutex>
#include <memory>
#include <vector>

const int max_threads = 8;

void thread_pool_add(std::shared_ptr<game::thread> thread, sf::Time time = sf::Time::Zero);
int thread_pool_process();


#endif /* THREAD_POOL_H_ */
