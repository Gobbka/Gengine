#pragma once
#include <cstring>

namespace Canvas {

	template<typename T>
	class DAIterator
	{
		T* _ptr;
	public:
		explicit DAIterator(T* ptr)
			: _ptr(ptr)
		{}

		T operator*()
		{
			return *_ptr;
		}

		void operator++()
		{
			++_ptr;
		}

		void operator--()
		{
			--_ptr;
		}

		bool operator!=(DAIterator<T>& iterator)
		{
			return _ptr != iterator._ptr;
		}
	};

	template<typename T>
	class DynamicAllocator
	{
		T* _data;
		unsigned _chunk_size;
		unsigned _allocated;
		unsigned _current_index;

	public:
		explicit DynamicAllocator(unsigned chunk_size);

		unsigned last_index();
		unsigned length() const;
		unsigned size() const;
		unsigned require(unsigned size);
		void push(T && object);

		T* at(unsigned index);

		DAIterator<T> begin() const;
		DAIterator<T> end() const;

		void clear();
	};

	template <typename T>
	DynamicAllocator<T>::DynamicAllocator(unsigned chunk_size)
		: _data(new T[chunk_size])
		, _chunk_size(chunk_size)
		, _allocated(chunk_size)
		, _current_index(0)
	{}

	template <typename T>
	unsigned DynamicAllocator<T>::last_index()
	{
		return _current_index;
	}

	template <typename T>
	unsigned DynamicAllocator<T>::length() const
	{
		return _current_index;
	}

	template <typename T>
	unsigned DynamicAllocator<T>::size() const
	{
		return _current_index * sizeof(T);
	}

	template <typename T>
	void DynamicAllocator<T>::clear()
	{
		_current_index = 0;
	}

	template <typename T>
	unsigned DynamicAllocator<T>::require(unsigned size)
	{
		if(_current_index + size > _allocated)
		{
			const int needed = (_current_index + size) / _chunk_size + 1;
			auto* new_buffer = new T[needed * _chunk_size];

			memcpy(new_buffer, _data, _current_index * sizeof(T));

			delete[] _data;
			_data = new_buffer;
		}

		const auto old_index = _current_index;

		_current_index += size;

		return old_index;
	}

	template <typename T>
	void DynamicAllocator<T>::push(T&& object)
	{
		auto index = require(1);
		*at(index) = object;
	}

	template <typename T>
	T* DynamicAllocator<T>::at(unsigned index)
	{
		return &_data[index];
	}

	template <typename T>
	DAIterator<T> DynamicAllocator<T>::begin() const
	{
		return DAIterator<T>(_data);
	}

	template <typename T>
	DAIterator<T> DynamicAllocator<T>::end() const
	{
		return DAIterator<T>( & _data[_current_index]);
	}
}
