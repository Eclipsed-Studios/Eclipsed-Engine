#ifndef RANDOM_H
#define RANDOM_H

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <random>
#include <numeric>
#include <chrono>

class  Random
{
public:
	template<typename T>
	inline static T GetValue()
	{
		std::random_device rd;
		std::mt19937 eng(rd());

		std::uniform_int_distribution<T> distribution(std::numeric_limits<T>::min(), std::numeric_limits<T>::max());
		return distribution(eng);
	}

	static std::mt19937& Generator()
	{
		static std::mt19937 gen(static_cast<unsigned>(
			std::chrono::high_resolution_clock::now().time_since_epoch().count()));
		return gen;
	}

public:
	template<typename T>
	inline static T GetValue(T aMin, T aMax)
	{
		if constexpr (std::is_integral_v<T>)
		{
			std::uniform_int_distribution<T> dis(aMin, aMax);
			return dis(Generator());
		}
		else if constexpr (std::is_floating_point_v<T>)
		{
			std::uniform_real_distribution<T> dis(aMin, aMax);
			return dis(Generator());
		}
		else
		{
			static_assert(std::is_arithmetic_v<T>, "Unsupported type for Random::GetValue");
		}
	}

	inline static float GetFloat(float min = 0.0f, float max = 1.0f)
	{
		static std::mt19937 gen(std::random_device{}());
		std::uniform_real_distribution<> dis(min, max);
		return (float)dis(gen);
	}
};
#endif