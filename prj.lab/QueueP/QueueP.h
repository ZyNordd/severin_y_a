#ifndef QUEUEP
#define QUEUEP
#include <iostream>
#include <memory>

class QueueP {
private:
	struct Node {
		int value = 0;
		std::unique_ptr<Node> next = nullptr;
		Node(const int& val) {
			this->value = val;
		}
	};
	std::unique_ptr<Node> head_ = nullptr;
public:
	QueueP();
	QueueP(const QueueP& copy);
	~QueueP();
	void push(const int rhs);
	int pop();
	int top() const;
	bool isEmpty() const;
};
#endif QUEUEP
