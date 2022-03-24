#pragma once

template<class T>
class List
{
private:

	struct node
	{
		T val;
		node* p_next;

		node(T value, node* p_next = nullptr)
			: val(value), p_next(p_next)
		{}
	};

	node* p_begin;

public:

	struct iterator
	{
		node* p_node;

		iterator(node* p_node = nullptr);

		T operator*()
		{
			return p_node->val;
		}

		iterator& operator++()
		{
			p_node = p_node->p_next;
			return *this;
		}

		bool operator==(const iterator& other);
		bool operator!=(const iterator& other);
	};

	size_t m_size;

public:

	List();

	iterator begin()
	{
		return iterator(p_begin);
	}

	iterator end()
	{
		return iterator();
	}

	void insert(T value);
	void insertAfter(T value, iterator position);
	void remove(iterator position);

};

template<class T>
inline List<T>::iterator::iterator(node* p_node)
	: p_node(p_node)
{}

template<class T>
inline bool List<T>::iterator::operator==(const iterator& other)
{
	return this->p_node == other.p_node;
}

template<class T>
inline bool List<T>::iterator::operator!=(const iterator& other)
{
	return this->p_node != other.p_node;
}

template<class T>
inline List<T>::List()
	: p_begin(nullptr), m_size(0)
{}

template<class T>
inline void List<T>::insert(T value)
{
	m_size++;

	if (p_begin == nullptr)
	{
		p_begin = new node(value);
		return;
	}

	node* temp = p_begin;
	while (temp->p_next != nullptr)
		temp = temp->p_next;

	temp->p_next = new node(value);
}

template<class T>
inline void List<T>::insertAfter(T value, iterator position)
{
	m_size++;

	if (p_begin == nullptr)
	{
		p_begin = new node(value);
		return;
	}

	for (iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it == position)
		{
			node* p_next = it.p_node->p_next;
			it.p_node->p_next = new node(value, p_next);

			return;
		}
	}
}

template<class T>
inline void List<T>::remove(iterator position)
{
	if (m_size == 1)
	{
		delete p_begin;
		p_begin = nullptr;
		m_size--;
		return;
	}

	if (position == this->begin())
	{
		node* temp = p_begin;
		p_begin = p_begin->p_next;
		delete temp;
		m_size--;
		return;
	}

	iterator last = this->begin();
	for (iterator it = this->begin(); it != this->end(); ++it)
	{
		if (it == position)
		{
			node* p_next = it.p_node->p_next;
			delete it.p_node;
			last.p_node->p_next = p_next;
			m_size--;

			return;
		}

		last = it;
	}
}