#include "cache.h"
#include <cmath>

Cache::Cache(CacheConfig& config)
{
	m_num_sets = config.num_sets;
	m_index_bits = log2(config.num_sets);
	m_num_ways = config.num_ways;
	m_line_size = config.line_size;
	m_write_mode = config.write_mode;
	m_line_offset_bits = log2(config.line_size);

	m_tags.resize(config.num_sets * config.num_ways, 0);
	m_dirty.resize(config.num_sets * config.num_ways, 0);
	m_valid.resize(config.num_sets * config.num_ways, 0);
}

unsigned Cache::calculate_tag(Addr addr)
{
	return addr >> (m_index_bits + m_line_offset_bits);
}

unsigned Cache::calculate_index(Addr addr)
{
	uint32_t offset_mask = (1 << (m_index_bits + m_line_offset_bits)) - 1;
	uint32_t index = (addr & offset_mask) >> m_line_offset_bits;
	return index;
}

unsigned Cache::calculate_word_index(Addr addr)
{
	uint32_t offset_mask = (1 << m_line_offset_bits) - 1;
	return addr & offset_mask;
}

bool Cache::access_cache(Addr addr, AccessType type, Cycle cycle)
{
	uint32_t tag = calculate_tag(addr);
	uint32_t set_index = calculate_index(addr);
	bool hit = false;

	uint32_t first = set_index * m_num_ways;
	uint32_t hit_line;
	for (uint32_t i = first; i < first + m_num_ways; ++i) {
		if (m_valid[i] && m_tags[i] == tag) {
			hit = true;
			hit_line = first + i;
		}
	}

	if (hit && AccessType::WRITE == type)
		m_dirty[hit_line] = true;

return hit;
}

void Cache::cycle()
{
// Only one access per cycle
// Read from port and access ??
}
