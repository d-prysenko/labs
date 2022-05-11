#pragma once
#include <cstdint>
#include <stack>
#include <cassert>
#include <string>
#include <sstream>

#ifdef _WIN32

#include <Windows.h>

#endif // _WIN32

namespace com
{


	template<typename T>
	struct node
	{
		T value;
		node<T>* left;
		node<T>* right;
		int height;

		node()
			: left(nullptr), right(nullptr), height(1)
		{}

		node(T value)
			: value(value), left(nullptr), right(nullptr), height(1)
		{}

		int max_child_height()
		{
			int left_height = (left != nullptr) ? left->height : 0;
			int right_height = (right != nullptr) ? right->height : 0;
			return max(left_height, right_height);
		}
	};


	template<typename T>
	class AVLTree
	{
	public:
		class iterator
		{
		private:
			com::node<T>* _p = nullptr;
			std::stack<com::node<T>*> _nodes;

			void fill_stack(com::node<T>* p_node)
			{
				while (p_node->left != nullptr)
				{
					_nodes.push(p_node);
					p_node = p_node->left;
				}
				
				_p = p_node;
			}

		public:
			iterator()
			{
				fill_stack(root());
			}

			iterator(com::node<T>* p_node)
			{
				fill_stack(p_node);
				//_p = _nodes.top();
				//_nodes.pop();
				//this->operator++();
			}

			T operator* ()
			{
				return _p->value;
			}

			iterator operator++()
			{
				if (_p->right && _p->right->value != 0)
					fill_stack(_p->right);
				else if (_nodes.size() > 0)
				{
					_p = _nodes.top();
					_nodes.pop();
				}
				else
					this->_p = nullptr;

				return *this;
			}
		};

	public:
		AVLTree();
		~AVLTree();

		void insert(T val);
		void remove(T val);

		size_t size() const;
		void clear();

		node<T>* root() const;

		//iterator max();
		//iterator min();
		T* find(T val);

		iterator begin() const
		{
			return iterator(m_root);
		}

		iterator end() const
		{
			return iterator(nullptr);
		}

	protected:


		size_t m_size;
		node<T>* m_root;

	private:
		node<T>* m_insert(node<T>* p_node, T val);
		node<T>* m_remove(node<T>* p_node, T val);
		void m_clear(node<T>* p_node);


		//        y                x
		//       / \              / \
		//      x   T3    -->    T1  y
		//     / \                  / \
		//    T1 T2                T2 T3
		node<T>* rotate_right(node<T>* y);

		//        y                x
		//       / \              / \
		//      x   T3    <--    T1  y
		//     / \                  / \
		//    T1 T2                T2 T3
		node<T>* rotate_left(node<T>* x);

		int balance_factor(node<T>* N);
		node<T>* find_min_node(node<T>* p_node);

	};

	template<class T>
	inline AVLTree<T>::AVLTree()
		: m_size(0), m_root(nullptr)
	{}

	template<class T>
	inline AVLTree<T>::~AVLTree()
	{
		clear();
	}

	template<class T>
	inline void AVLTree<T>::insert(T val)
	{
		m_root = m_insert(m_root, val);
	}


	template<class T>
	inline node<T>* AVLTree<T>::m_insert(node<T>* p_node, T val)
	{
		if (p_node == nullptr)
		{
			m_size++;
			return new node<T>(val);
		}

		if (val < p_node->value)
			p_node->left = m_insert(p_node->left, val);
		else if (val > p_node->value)
			p_node->right = m_insert(p_node->right, val);
		else
			return p_node;

		p_node->height = p_node->max_child_height() + 1;

		int balance = balance_factor(p_node);

		// left left
		if (balance > 1 && val < p_node->left->value)
			return rotate_right(p_node);

		// right right
		if (balance < -1 && val > p_node->right->value)
			return rotate_left(p_node);

		// left right
		if (balance > 1 && val > p_node->left->value)
		{
			p_node->left = rotate_left(p_node->left);
			return rotate_right(p_node);
		}

		// right left
		if (balance < -1 && val < p_node->right->value)
		{
			p_node->right = rotate_right(p_node->right);
			return rotate_left(p_node);
		}

		return p_node;
	}

	template<class T>
	inline void AVLTree<T>::remove(T val)
	{
		m_root = m_remove(m_root, val);
	}


	template<class T>
	inline node<T>* AVLTree<T>::m_remove(node<T>* p_node, T val)
	{

		if (p_node == nullptr)
			return p_node;

		if (val < p_node->value)
			p_node->left = m_remove(p_node->left, val);

		else if (val > p_node->value)
			p_node->right = m_remove(p_node->right, val);

		else
		{
			// node with only one child or no child
			if ((p_node->left == nullptr) || (p_node->right == nullptr))
			{
				node<T>* temp = p_node->left ? p_node->left : p_node->right;

				delete p_node;
				p_node = temp;
			}
			else
			{
				node<T>* temp = find_min_node(p_node->right);

				delete p_node;
				p_node = temp;

				p_node->right = m_remove(p_node->right, temp->value);
			}

			m_size--;
		}


		if (p_node == nullptr)
			return p_node;

		p_node->height = p_node->max_child_height() + 1;

		int balance = balance_factor(p_node);

		// left left
		if (balance > 1 && balance_factor(p_node->left) >= 0)
			return rotate_right(p_node);

		// right right
		if (balance < -1 && balance_factor(p_node->right) <= 0)
			return rotate_left(p_node);

		// left right
		if (balance > 1 && balance_factor(p_node->left) < 0)
		{
			p_node->left = rotate_left(p_node->left);
			return rotate_right(p_node);
		}

		// right left
		if (balance < -1 && balance_factor(p_node->right) > 0)
		{
			p_node->right = rotate_right(p_node->right);
			return rotate_left(p_node);
		}

		return p_node;
		
	}

	template<typename T>
	inline node<T>* AVLTree<T>::root() const
	{
		return m_root;
	}

	template<typename T>
	inline T* AVLTree<T>::find(T val)
	{
		node<T>* temp = m_root;
		while (temp != nullptr)
		{
			if (val < temp->value)
				temp = temp->left;
			else if (val > temp->value)
				temp = temp->right;
			else
				return &(temp->value);
		}

		return nullptr;
	}

	template<class T>
	inline size_t AVLTree<T>::size() const
	{
		return m_size;
	}

	template<class T>
	inline void AVLTree<T>::clear()
	{
		m_clear(m_root);
	}

	template<typename T>
	inline void AVLTree<T>::m_clear(node<T>* p_node)
	{
		if (p_node == nullptr)
			return;

		m_clear(p_node->left);
		m_clear(p_node->right);

		delete p_node;
		p_node = nullptr;
	}

	template<typename T>
	inline node<T>* AVLTree<T>::rotate_right(node<T>* y)
	{
		node<T>* x = y->left;
		node<T>* T2 = x->right;

		x->right = y;
		y->left = T2;

		y->height = y->max_child_height() + 1;
		x->height = x->max_child_height() + 1;

		return x;
	}

	template<typename T>
	inline node<T>* AVLTree<T>::rotate_left(node<T>* x)
	{
		node<T>* y = x->right;
		node<T>* T2 = y->left;

		y->left = x;
		x->right = T2;

		x->height = x->max_child_height() + 1;
		y->height = y->max_child_height() + 1;

		return y;
	}

	template<typename T>
	inline int AVLTree<T>::balance_factor(node<T>* p_node)
	{
		if (p_node == NULL)
			return 0;

		int left_height, right_height;
		left_height = right_height = 0;

		if (p_node->left)
			left_height = p_node->left->height;

		if (p_node->right)
			right_height = p_node->right->height;

		return left_height - right_height;
	}

	template<typename T>
	inline node<T>* AVLTree<T>::find_min_node(node<T>* p_node)
	{
		node<T>* current = p_node;

		while (current->left != nullptr)
			current = current->left;

		return current;
	}





	class util
	{

	#define _abort(message)															\
	{																				\
		std::cerr << "Error: " << message << std::endl;								\
		std::cerr << "file: " << __FILE__ << ":" << __LINE__ << std::endl;			\
		std::cerr << "function: " << __FUNCTION__ << std::endl;						\
		std::abort();																\
	}

	private:
		template<class T>
		static std::stringstream dot_export_node(const node<T>* p_node)
		{
			std::stringstream output;

			std::string name = std::to_string((int)p_node);

			output << "n" << name << ";";
			output << "n" << name << " [label=\"" << p_node->value << " : " << p_node->height << "\"];";

			if (p_node->left != nullptr)
				output << "n" << name << " -- " << dot_export_node(p_node->left).str();

			if (p_node->right != nullptr)
				output << "n" << name << " -- " << dot_export_node(p_node->right).str();

			return output;
		}


	public:
		// serealization to dot language for visualizing tree
		// http://magjac.com/graphviz-visual-editor/
		//
		// T must implement friend std::ostream& operator<<(std::ostream& out, T& value) for serialization
		template<class T>
		static std::string dot_export(const AVLTree<T>& tree)
		{
			return "graph {" + dot_export_node(tree.root()).str() + "}";
		}

		static int copy_to_clipboard(std::string buffer)
		{
			#ifdef _WIN32

				int code = OpenClipboard(NULL);

				if (code == NULL)
				{
					_abort("OpenClipboard returned null");
					return code;
				}

				EmptyClipboard();

				HGLOBAL hg = GlobalAlloc(GMEM_MOVEABLE, buffer.size() + 1);

				if (!hg) {
					CloseClipboard();
					_abort("GlobalAlloc returned null");
					return code;
				}

				memcpy(GlobalLock(hg), buffer.c_str(), buffer.size() + 1);

				GlobalUnlock(hg);
				SetClipboardData(CF_TEXT, hg);
				CloseClipboard();
				GlobalFree(hg);

			#else
				// TODO: Call platform specific functions to access clipboard
				_abort("TODO: Call platform specific functions to access clipboard");
			#endif // _WIN32
		}
	};

}