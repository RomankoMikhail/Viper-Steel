#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <array>

template<typename T, unsigned h, unsigned w>
using array2d = std::array<std::array<T, w>, h>;

template<typename T1, typename T2>
bool within(T1 value, T2 low, T2 high)
{
	if(low <= value && value <= high)
		return true;
	return false;
}

template<typename T1, typename T2>
bool withinDelta(T1 value, T2 target, T2 delta)
{
	if(target - delta <= value && value <= target + delta)
		return true;
	return false;
}

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T1, typename T2> T1 clamp(T1 val, T2 low, T2 high)
{
	if(val < low)
		return low;
	if(val > high)
		return high;
	return val;
}

int gcd (int a, int b);

#endif /* TEMPLATES_H_ */
