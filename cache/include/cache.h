#include <cstdint>
#include <vector>

using Addr = uint64_t;
using Cycle = uint64_t;

enum class AccessType {
	WRITE,
	READ,
};

enum class CacheWriteMode {
	WRITEBACK,
	WRITETHROUGH,
};

struct CacheConfig {
	unsigned num_ways;
	unsigned num_sets;
	unsigned line_size; // In bytes
	CacheWriteMode write_mode;
};

class Cache {
public:
	Cache(CacheConfig& config);
	bool access_cache(Addr addr, AccessType type);
	void cycle();
private:
	uint32_t calculate_index(Addr addr);
	uint32_t calculate_tag(Addr addr);
	uint32_t calculate_word_index(Addr addr);
	void fill(Addr addr);

	std::vector<Addr> m_tags;
	std::vector<uint8_t> m_valid;
	std::vector<uint8_t> m_dirty;
	std::vector<uint32_t> m_plru_states;

	CacheWriteMode m_write_mode;
	uint32_t m_num_sets;
	uint32_t m_index_bits;
	uint32_t m_num_ways;
	uint32_t m_line_size;
	uint32_t m_line_offset_bits;
};
