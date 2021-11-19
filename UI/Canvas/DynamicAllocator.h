#pragma once

namespace Canvas {

	template<typename T>
	class DynamicAllocator
	{
		T* _data;
		unsigned _chunk_size;
		unsigned _allocated;
		unsigned _current_index;

	public:
		explicit DynamicAllocator(unsigned chunk_size);

		unsigned length() const;
		unsigned size() const;
		void clear();
		T* require(unsigned size);
	};

	template <typename T>
	DynamicAllocator<T>::DynamicAllocator(unsigned chunk_size)
		: _data(new T[chunk_size])
		, _chunk_size(chunk_size)
		, _allocated(chunk_size)
		, _current_index(0)
	{}

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
	T* DynamicAllocator<T>::require(unsigned size)
	{
		if(_current_index + size > _allocated)
		{
			const int needed = (_current_index + size) / _chunk_size + 1;
			auto* new_buffer = new T[needed * _chunk_size];

			memcpy(new_buffer, _data, _current_index * sizeof(T));

			delete[] _data;
			_data = new_buffer;
		}

		_current_index += size;

		return &_data[_current_index];
	}
}
