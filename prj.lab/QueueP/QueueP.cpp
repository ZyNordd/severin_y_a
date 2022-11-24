#include <QueueP/QueueP.h>
#include <iostream>

QueueP::QueueP() {
	this->head_ = nullptr;
}

QueueP::QueueP(const QueueP& copy) {
	if (copy.isEmpty()) head_ = nullptr;
	head_ = std::make_unique<Node>(copy.top());
	Node* temp = head_.get();
	const Node* temp_copy = copy.head_->next.get();
	while (temp_copy != nullptr) {
		temp->next = std::make_unique<Node>(temp_copy->value);
		temp = temp->next.get();
		temp_copy = temp_copy->next.get();
	}
	return;
}

QueueP::~QueueP() {
}

void QueueP::push(const int rhs) {
	std::unique_ptr<Node> newnode = std::make_unique<Node>(rhs);
	if (head_ == nullptr || head_->value > rhs) {
		newnode->next = std::move(head_);
		head_ = std::move(newnode);
		return;
	}
	Node* current = head_.get();
	while (current->next != nullptr && rhs >= current->next->value) {
		current = current->next.get();
	}
	newnode->next = std::move(current->next);
	current->next = std::move(newnode);
}


int QueueP::pop() {
		int value = this->head_->value;
		head_ = std::move(head_->next);
		return value;
}

int QueueP::top() const{
	return this->head_->value;
}

bool QueueP::isEmpty() const{
	return this->head_.get() == nullptr;
}
