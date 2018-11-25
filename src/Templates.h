#ifndef TEMPLATES_H_
#define TEMPLATES_H_

#include <array>
#include <algorithm>

template<typename T, unsigned h, unsigned w>
using array2d = std::array<std::array<T, w>, h>;

/*!
 * \brief Checks if value is in range [min; max]
 * \ingroup math
 *
 * \param value value to check
 * \param min minimum value
 * \param max maximum value
 * \return \b true if value is in range
 * \return \b false if value out of range
 */
template<typename T1, typename T2>
bool inRange(T1 value, T2 min, T2 max)
{
	if (min <= value && value <= max)
		return true;
	return false;
}

/*!
 * \brief Checks if two floating point values are equal
 * \ingroup math
 *
 * \param a a value
 * \param b b value
 * \param ulp units in the last place
 * \return \b true if a and b are equal
 * \return \b false if a and b are not equal
 */
template<typename T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type approx(T a, T b, int ulp)
{
	return std::abs(a - b) <= std::numeric_limits<T>::epsilon() * std::max(std::abs(a), std::abs(b)) * ulp;
}

/*!
 * \brief Gets sign of a value
 * \ingroup math
 *
 * \param val value
 * \return -1 if value is negative
 * \return 0 if value is zero
 * \return 1 if value is positive
 */
template<typename T>
int sign(T val)
{
	return (T(0) < val) - (val < T(0));
}

/*!
 * \brief Clamps a value between a minimum and maximum value.
 * \ingroup math
 *
 * \param val value
 * \param min minimum value
 * \param max maximum value
 *
 * \return value between min and max
 */
template<typename T1, typename T2>
T1 clamp(T1 val, T2 min, T2 max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}

/*!
 * \brief greatest common divisor of two integers
 * \ingroup math
 *
 * \param a first integer
 * \param b second integer
 *
 * \return greatest common divisor
 */
int gcd(int a, int b);

#endif /* TEMPLATES_H_ */
