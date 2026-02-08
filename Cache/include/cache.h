#include <vector>
#include <cstdint>

using Addr = uint64_t;
using Cycle = uint64_t;

enum class AccessType
{
	WRITE,
	READ,
};

enum class CacheWriteMode
{
	WRITEBACK,
	WRITETHROUGH,
};

struct CacheConfig
{
	unsigned num_ways;
	unsigned num_sets;
	unsigned line_size; // In bytes
	CacheWriteMode write_mode;
};

class Cache
{
public:
	Cache(CacheConfig& config);
	bool access_cache(Addr addr, AccessType type, Cycle cycle);
	void cycle();
private:
	unsigned calculate_index(Addr addr);
	unsigned calculate_tag(Addr addr);
	unsigned calculate_word_index(Addr addr);

	std::vector<Addr> m_tags;
	std::vector<uint8_t> m_valid;
	std::vector<uint8_t> m_dirty;

	CacheWriteMode m_write_mode;
	unsigned m_num_sets;
	unsigned m_index_bits;
	unsigned m_num_ways;
	unsigned m_line_size;
	unsigned m_line_offset_bits;
};
