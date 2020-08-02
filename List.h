#pragma once

namespace chess {

	template <class T>
	struct ListNode
	{
		T* item;
		ListNode<T>* prev;
		ListNode<T>* next;

		ListNode(T* _item) {
			item = _item;
			prev = nullptr;
			next = nullptr;
		}

		~ListNode() {
			if (next) {
				delete next;
			}
		}
	};


	template <class T>
	struct List {
		ListNode<T>* nodes;
		size_t length;

		List<T>() {
			nodes = nullptr;
			length = 0;
		}

		void append(T* _item) {
			ListNode<T>* node = new ListNode<T>(_item);

			if (!nodes) {
				nodes = node;
			}
			else {
				ListNode<T>* ptr = nodes;
				while (ptr->next) {
					ptr = ptr->next;
				}
				ptr->next = node;
				node->prev = ptr;
			}

			++length;
		}

		void remove(ListNode<T>* node) {
			if (node->prev) {
				node->prev->next = node->next;
			}

			if (node->next) {
				node->next->prev = node->prev;
			}

			node->prev = nullptr;
			node->next = nullptr;
			delete node;

			--length;
		}

		~List() {
			if (nodes) {
				delete nodes;
			}
			length = 0;
		}
	};
}