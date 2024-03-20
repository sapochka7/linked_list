#include <memory>
#include <iostream>
#include <cassert>

template<typename T>
class Node
{
public:
	T data;
	std::shared_ptr<Node<T>> prev;
	std::shared_ptr<Node<T>> next;
public:
	explicit Node(T data)
	: data(data), prev(nullptr), next(nullptr)
	 {}
};

template<typename T>
class dList
{
private:
	std::shared_ptr<Node<T>> head;
	std::shared_ptr<Node<T>> tail;
	std::shared_ptr<Node<T>> cursor; // Cursor to track current position

public:
	dList()
	: head(nullptr), tail(nullptr), cursor(nullptr)
	{}

	void add_front(T data)
	{
		auto new_node = std::make_shared<Node<T>>(data);
		if (!head)
			head = tail = new_node;
		else
	{
			new_node->next = head;
			head->prev = new_node;
			head = new_node;
		}
		if (!cursor)
			cursor = head;
	}

	void add_back(T data)
	{
		auto new_node = std::make_shared<Node<T>>(data);
		if (!tail)
			head = tail = new_node;
		else
	{
			tail->next = new_node;
			new_node->prev = tail;
			tail = new_node;
		}
		if (!cursor)
			cursor = tail;
	}

	void remove_front()
	{
		if (!head)
			throw std::runtime_error("List is empty.");
		if(cursor == head)
			cursor = head->next;
		head = head->next;
		if (head)
			head->prev.reset();
		else
			tail.reset();
	}

	void remove_back()
	{
		if (!tail)
			throw std::runtime_error("List is empty.");
		if(cursor == tail)
			cursor = tail->prev;
		tail = tail->prev;
		if (tail)
			tail->next.reset();
		else
			head.reset();
	}

	bool is_empty() const
	{
		return !head;
	}

	void move_forward()
	{
		if (cursor && cursor->next)
			cursor = cursor->next;
		else if (tail)
			cursor = tail;
	}

	void move_backward()
	{
		if (cursor && cursor->prev)
			cursor = cursor->prev;
		else if (head)
			cursor = head;
	}

	T get_current_data()
	{
		if (cursor)
			return cursor->data;
		else
			throw std::runtime_error("Cursor is not set.");
	}

	void set_cursor_to_head()
	{
		cursor = head;
	}

	void set_cursor_to_tail()
	{
		cursor = tail;
	}

	bool is_cursor_set()
	{
		return cursor != nullptr;
	}

	void display_current()
	{
		if (cursor)
			std::cout << "Current data: " << cursor->data << std::endl;
		else
			std::cout << "Cursor is not set." << std::endl;
	}

	void display_forward()
	{
		auto node = head;
		while (node)
		{
			std::cout << node->data << " ";
			node = node->next;
		}
		std::cout << std::endl;
	}

	void display_backward()
	{
		auto node = tail;
		while (node)
		{
			std::cout << node->data << " ";
			node = node->prev;
		}
		std::cout << std::endl;
	}
};

void verify_list()
{
	dList<char> list;

	assert(list.is_empty());

	list.add_front('b');
	list.add_back('c');
	list.add_front('a');
	list.add_back('d');

	assert(!list.is_empty());

	list.display_forward(); // Expected output: a b c d
	list.display_backward(); // Expected output: d c b a

	list.set_cursor_to_head(); // Set cursor to head
	list.move_forward();		// Move cursor forward
	assert(list.get_current_data() == 'b');

	list.move_forward();		// Move cursor forward
	assert(list.get_current_data() == 'c');

	list.move_backward();	 // Move cursor backward
	assert(list.get_current_data() == 'b');

	list.move_backward();	 // Move cursor backward
	assert(list.get_current_data() == 'a');

	list.set_cursor_to_tail(); // Set cursor to tail
	assert(list.get_current_data() == 'd');

	list.move_forward();		// Move cursor forward (should not change)
	assert(list.get_current_data() == 'd');
	list.move_backward();	 // Move cursor backward
	assert(list.get_current_data() == 'c');

	list.move_forward();		// Move cursor forward
	assert(list.get_current_data() == 'd');

	list.move_forward();		// Move cursor forward (should not change)
	assert(list.get_current_data() == 'd');


	list.remove_front(); // Remove 'a'
	assert(list.get_current_data() == 'd'); // Keep position

	list.remove_back(); // Remove 'd'
	assert(list.get_current_data() == 'c'); // Cursor should move to available node

	bool got_exception = false;
	try
	{
		list.remove_front(); // Remove 'b'
		list.remove_front(); // Remove 'c', list is now empty
	}
	catch (const std::runtime_error& e)
	{
		got_exception = true;
	}
	assert(!got_exception && list.is_empty()); // List should be empty without exceptions

	got_exception = false;
	try
	{
		list.get_current_data(); // Trying to get data from an empty list
	}
	catch (const std::runtime_error& e)
	{
		got_exception = true;
	}
	assert(got_exception); // Should catch an exception because list is empty

	std::cout << "All tests passed." << std::endl;
}

int main()
{
	verify_list();
	return 0;
}
