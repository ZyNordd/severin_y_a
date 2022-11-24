#include <QueueP/QueueP.h>

int main() {
	QueueP a;
	a.push(1);
	a.push(3);
	a.push(5);
	a.push(4);
	a.push(7);
	a.push(1);
	a.push(5);
	a.push(3);
	a.push(6); 
	QueueP b(a);
	for (int i = 0; i < 9; ++i) {
		std::cout << a.pop() << ' ';
	}
	std::cout << std::endl;
	for (int i = 0; i < 9; ++i) {
		std::cout << b.pop() << ' ';
	}

	return 0;
}