#ifndef TEMPLATES_HPP_
#define TEMPLATES_HPP_

#include <array>

template<typename T, unsigned h, unsigned w>
using array2d = std::array<std::array<T, w>, h>;

template<typename T1, typename T2, typename T3>
bool within(T1 value, T2 low, T3 high)
{
	if(low <= value && value <= high)
		return true;
	return false;
}

template<typename T1, typename T2, typename T3>
bool withinDelta(T1 value, T2 target, T3 delta)
{
	if(target - delta <= value && value <= target + delta)
		return true;
	return false;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

static int gcd (int a, int b) {
  long r, i;
  while(b!=0){
    r = a % b;
    a = b;
    b = r;
  }
  return a;
}

#endif /* TEMPLATES_HPP_ */
