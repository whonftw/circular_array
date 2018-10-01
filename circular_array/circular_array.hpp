#pragma once
#include <memory>
template<typename T>
class circular_array {
private:
	std::unique_ptr<T[]> m_InternalArray;
	std::size_t m_MaxSize;
	std::size_t m_CurrentSize = 0;

	// When pushing elements, either head gets decremented or tail gets incremented
	// After first push, head and tail need to be the same
	int m_Head = 1;
	int m_Tail = 0;

	void increase_size_if_needed();
public:
	circular_array(std::size_t);
	~circular_array();
	void push_back(T);
	T pop_back();
	void push_front(T);
	T pop_front();
	std::size_t size() const;


	// Subscript operator
	T& operator[](int);
	const T& operator[](int) const;
	T& at(int);
	const T& at(int) const;
};

template<typename T>
circular_array<T>::circular_array(std::size_t _initialSize) : m_MaxSize{ _initialSize }, m_InternalArray{ new T[_initialSize] }
{
}

template<typename T>
circular_array<T>::~circular_array()
{
}

template<typename T>
void circular_array<T>::increase_size_if_needed()
{
	if (m_CurrentSize == m_MaxSize)
	{
		T* newArray = new T[m_MaxSize * 2];
		for (std::size_t index = 0; index < m_CurrentSize; ++index)
		{
			newArray[index] = m_InternalArray[(m_Head + index) % m_MaxSize];
		}
		m_InternalArray.reset(newArray);
		m_Head = 0;
		m_Tail = m_CurrentSize - 1;
		m_MaxSize *= 2;
	}
}

template<typename T>
void circular_array<T>::push_back(T _element)
{
	increase_size_if_needed();
	++m_Tail;
	if (m_Tail == m_MaxSize)
	{
		m_Tail = 0;
	}
	m_InternalArray[m_Tail] = _element;
	++m_CurrentSize;
}

template<typename T>
T circular_array<T>::pop_back()
{
	auto position = m_Tail;
	--m_Tail;
	if (m_Tail == -1)
		m_Tail = m_MaxSize - 1;
	--m_CurrentSize;
	return std::move(m_InternalArray[position]);
}

template<typename T>
void circular_array<T>::push_front(T _element)
{
	increase_size_if_needed();
	--m_Head;
	if (m_Head == -1)
	{
		m_Head = m_MaxSize - 1;
	}
	m_InternalArray[m_Head] = _element;
	++m_CurrentSize;
}

template<typename T>
T circular_array<T>::pop_front()
{
	auto position = m_Head;
	++m_Head;
	if (m_Head == m_MaxSize)
		m_Head = 0;
	--m_CurrentSize;
	return std::move(m_InternalArray[position]);
}

template<typename T>
inline std::size_t circular_array<T>::size() const
{
	return m_CurrentSize;
}

template<typename T>
inline T& circular_array<T>::operator[](int _index)
{
	return m_InternalArray[(m_Head + _index) % m_MaxSize];
}

template<typename T>
inline const T& circular_array<T>::operator[](int _index) const
{
	return m_InternalArray[(m_Head + _index) % m_MaxSize];
}

template<typename T>
T& circular_array<T>::at(int _index)
{
	if (_index < 0 || _index >= m_CurrentSize)
		throw std::out_of_range;
	return m_InternalArray[(m_Head + _index) % m_MaxSize];
}

template<typename T>
const T& circular_array<T>::at(int _index) const
{
	if (_index < 0 || _index >= m_CurrentSize)
		throw std::out_of_range;
	return m_InternalArray[(m_Head + _index) % m_MaxSize];
}

