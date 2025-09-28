#include "RingBuffer.h"

namespace Eclipse::Utilities
{
	template<typename T, size_t capacity>
	inline void RingBuffer<T, capacity>::Push(const T& value)
	{
		buffer[index] = value;
		index = (index + 1) % capacity;

		if (size < capacity) size++;
	}

	template<typename T, size_t capacity>
	inline const T& RingBuffer<T, capacity>::Get(size_t i) const
	{
		return buffer[(index + capacity - size + i) % capacity];
	}
	
	template<typename T, size_t capacity>
	inline T& RingBuffer<T, capacity>::Get(size_t i)
	{
		return buffer[(index + capacity - size + i) % capacity];
	}

	template<typename T, size_t capacity>
	inline size_t RingBuffer<T, capacity>::Count() const
	{
		return size;
	}
}