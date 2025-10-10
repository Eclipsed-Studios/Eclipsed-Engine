#pragma once

namespace Eclipse::Utilities
{
	template<typename T, size_t capacity>
	class RingBuffer final
	{
	public:
		void Push(const T& value);
		
		const T& Get(size_t i)const;
		T& Get(size_t i);

		size_t Count() const;

	private:
		std::array<T, capacity> buffer{};
		size_t index = 0;
		size_t size = 0;
	};
}

#include "RingBuffer.inl"