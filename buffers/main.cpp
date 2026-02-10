#include "fifo.h"
#include "dynamic_fifo.h"

int main() {
	Fifo<int, 5> fifo;
	DynamicFifo<int> dfifo(10);
	fifo.push(5);
	fifo.push(10);
	fifo.push(1000);
	fifo.push(90);
	fifo.push(1010);
	fifo.push(12404);
	fifo.print();

	fifo.pop();
	fifo.pop();
	fifo.pop();
	fifo.print();

	dfifo.push(12);
	dfifo.push(12454);
	std::cout << dfifo.front() << "\n";
	std::cout << dfifo.front() << "\n";
	dfifo.pop();
	std::cout << dfifo.front() << "\n";
	dfifo.pop();
	std::cout << dfifo.front() << "\n";
	return 0;
}
