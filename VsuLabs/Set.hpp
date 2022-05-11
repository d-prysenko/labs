#pragma once
#include "AVLTree.hpp"
#include <stack>
#include <iostream>

namespace com
{

	template<typename T>
	class Set : public com::AVLTree<T>
	{
	public:
		Set();
		Set(const Set<T>& other);

		bool includes(T val);

		Set<T> union_with(Set<T>& other);
		Set<T> intersect_with(Set<T>& other);
		Set<T> subtract(Set<T>& other);
		bool included_in(Set<T>& other);

		friend std::ostream& operator<<(std::ostream& stream, Set<T>& other)
		{
			auto it = other.begin();
			for (int i = 0; i < other.size(); ++i, ++it)
			{
				stream << *it << " ";
			}

			return stream;
		}

		friend std::istream& operator>>(std::istream& stream, Set<T>& other)
		{
			T temp;
			stream >> temp;

			other.insert(temp);

			return stream;
		}
	};

	template<typename T>
	inline Set<T>::Set()
		: com::AVLTree<T>()
	{}

	template<typename T>
	inline com::Set<T>::Set(const Set<T>& other)
	{
		auto it = other.begin();
		for (int i = 0; i < other.size(); ++i, ++it)
		{
			this->insert(*it);
		}
	}

	template<typename T>
	inline bool Set<T>::includes(T val)
	{
		T* pos = AVLTree.find(val);
		return pos == nullptr ? false : true;
	}

	template<typename T>
	inline Set<T> Set<T>::union_with(Set<T>& other)
	{
		Set<T> res;

		auto it = this->begin();
		for (int i = 0; i < this->size(); ++i, ++it)
		{
			res.insert(*it);
		}

		it = other.begin();
		for (int i = 0; i < other.size(); ++i, ++it)
		{
			res.insert(*it);
		}

		return res;
	}

	template<typename T>
	inline Set<T> Set<T>::intersect_with(Set<T>& other)
	{
		Set<T> res;

		auto it = this->begin();
		for (int i = 0; i < this->size(); ++i, ++it)
		{
			if (other.find(*it) != nullptr)
			{
				res.insert(*it);
			}
		}

		return res;
	}

	template<typename T>
	inline Set<T> Set<T>::subtract(Set<T>& other)
	{
		Set<T> res;

		auto it = other.begin();
		for (int i = 0; i < other.size(); ++i, ++it)
		{
			if (this->find(*it) == nullptr)
			{
				res.insert(*it);
			}
		}

		return res;
	}

	template<typename T>
	inline bool Set<T>::included_in(Set<T>& other)
	{
		auto it = this->begin();
		bool isOk = true;

		for (int i = 0; i < this->size() && isOk; ++i, ++it)
		{
			if (other.find(*it) == nullptr)
				isOk = false;
		}

		return isOk;
	}

}