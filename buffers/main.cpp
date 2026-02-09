#include "fifo.h"

int main() {
	Fifo<int, 5> fifo;
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
	return 0;
}
