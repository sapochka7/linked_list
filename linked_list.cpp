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

public:
	dList()
	: head(nullptr), tail(nullptr)
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
	}

	T remove_front()
	{
		if (!head)
			throw std::runtime_error("List is empty");
		auto temp = head;
		T data = temp->data;
		head = head->next;
		if (head)
			head->prev = nullptr;
		else
			tail = nullptr;
		return data;
	}

	T remove_back()
	{
		if (!tail)
			throw std::runtime_error("List is empty");
		auto temp = tail;
		T data = temp->data;
		tail = tail->prev;
		if (tail)
			tail->next = nullptr;
		else
			head = nullptr;
		return data;
	}

	bool is_empty() const
	{
        return head == nullptr;
    }

	void display_forward()
	{
        auto current = head;
		while (current != nullptr)
		{
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

	void display_backward()
	{
        auto current = tail;
		while (current != nullptr)
		{
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }
};

// Home brew unit test

void verify_list()
{
	dList<char> list;

    assert(list.is_empty());

	list.add_front('b');
	list.add_back('c');
	list.add_front('a');
	list.add_back('d');

	assert(!list.is_empty());

	list.display_forward();  // Expected output: a b c d
	list.display_backward(); // Expected output: d c b a

	// Remove elements one at a time from both ends
	assert(list.remove_front() 	== 'a');
	assert(list.remove_back() 	== 'd');
	assert(list.remove_front() 	== 'b');
	assert(list.remove_back() 	== 'c');

	assert(list.is_empty());    // List is empty

	bool got_exception=false;
	try
	{
		list.remove_back(); // Provoke an exception
	}
	catch (const std::runtime_error& e)
	{
		got_exception = true;
	}
	assert(got_exception); 	// Exception as expected

	got_exception = false;
	try
	{
		list.remove_front(); // Provoke an exception
	} catch (const std::runtime_error& e)
	{
		got_exception = true;
	}
	assert(got_exception); 	// Exception as expected

	assert(list.is_empty());    // List still empty
}

int main()
{
	verify_list();
    std::cout << "All tests passed." << std::endl;
    return 0;
}

