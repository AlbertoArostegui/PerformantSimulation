#include <cassert>
#include <cstdint>
#include <memory>

template<typename T>
class DynamicFifo {
private:
	std::unique_ptr<T[]> m_entries;
	uint32_t m_capacity;
	uint32_t m_count;
	uint32_t m_head;
	uint32_t m_tail;
public:
	DynamicFifo(uint32_t size) : m_capacity(size), m_count(0), m_head(0), m_tail(0) {
		if (size == 0) assert(false && "FIFO cannot be null sized");
		m_entries = std::make_unique<T[]>(size);
		m_capacity = size;
	}

	DynamicFifo(const DynamicFifo&) = delete;
	DynamicFifo& operator=(const DynamicFifo&) = delete;

	bool push(T&& item) {
		if (m_count == m_capacity) return false;
		m_entries[m_head] = item;
		m_count++;
		m_head = (++m_head == m_capacity) ? 0 : m_head;
		return true;
	}

	T& front() {
		return m_entries[m_tail];
	}

	const T& front() const {
		return m_entries[m_tail];
	}

	void pop() {
		if (m_count == 0) return;
		m_entries[m_tail] = T();
		m_count--;
		m_tail = (++m_tail == m_capacity) ? 0 : m_tail;
	}

	bool empty() const { return m_count == 0; }
	bool full() const { return m_count == m_capacity; }
	uint32_t size() const { return m_count; }
};
