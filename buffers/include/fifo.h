#include <cassert>
#include <cstddef>
#include <cstdint>
#include <iostream>

template<typename T, size_t N>
class Fifo {
private:
	T m_entries[N];
	uint32_t m_count;
	uint32_t m_head;
	uint32_t m_tail;
public:
	Fifo() : m_head(0), m_tail(0), m_count(0) {
		for (int i = 0; i < N; ++i) {
			m_entries[i] = 0;
		}
	}
	~Fifo() {}

	void cycle();
	bool push(T&& item) {
		if (m_count == N)
			return false; 
		m_entries[m_head] = item;
		m_count++;
		if (++m_head == N) m_head = 0;
		return true;
	}

	T& front() {
		// Should check valid
		return m_entries[m_tail];
	}

	void pop() {
		assert(m_count > 0);
		m_entries[m_tail] = 0;
		m_count--;
		m_tail = (m_tail == N) ? m_tail = 0 : m_tail + 1;
	}

	void print() {
		for (int i = 0; i < N; ++i) {
			printf("[%d] %d\n", i, m_entries[i]);
		}
	}
};
