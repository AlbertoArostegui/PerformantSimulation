#include "cache.h"

#include <cmath>

#include "tree_plru.h"

Cache::Cache(CacheConfig& config)
	: m_num_sets(config.num_sets), m_num_ways(config.num_ways), m_line_size(config.line_size)
{
	m_index_bits = std::log2(config.num_sets);
	m_line_offset_bits = std::log2(config.line_size);
	m_write_mode = config.write_mode;

	m_tags.resize(config.num_sets * config.num_ways, 0);
	m_dirty.resize(config.num_sets * config.num_ways, 0);
	m_valid.resize(config.num_sets * config.num_ways, 0);
	m_plru_states.resize(config.num_sets, 0);
}

uint32_t Cache::calculate_tag(Addr addr)
{
	return addr >> (m_index_bits + m_line_offset_bits);
}

uint32_t Cache::calculate_index(Addr addr)
{
	uint32_t offset_mask = (1 << (m_index_bits + m_line_offset_bits)) - 1;
	uint32_t index = (addr & offset_mask) >> m_line_offset_bits;
	return index;
}

uint32_t Cache::calculate_word_index(Addr addr)
{
	uint32_t offset_mask = (1 << m_line_offset_bits) - 1;
	return addr & offset_mask;
}

bool Cache::access_cache(Addr addr, AccessType type)
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
			TreePlru::update_plru(m_plru_states[set_index], i % m_num_ways, m_num_ways);
			break;
		}
	}

	if (hit && AccessType::WRITE == type)
		m_dirty[hit_line] = true;
	if (!hit) {
		// memory->req();
		// add write to mshr
	}

	return hit;
}

void Cache::fill(Addr addr)
{
	// TODO: Should write back if its dirty
	// TODO: If the miss was a write, we should set the dirty bit
	uint32_t set = calculate_index(addr);
	uint32_t tag = calculate_tag(addr);
	uint32_t victim_way = TreePlru::get_victim(m_plru_states[set_index], m_num_ways);
	uint32_t abs_way = set * m_num_ways + victim_way;
	TreePlru::update_plru(m_plru_states[set], victim_way, m_num_ways);
	m_valid.at(abs_way) = 1;
	m_dirty.at(abs_way) = 0;
	m_tags.at(abs_way) = tag;
}

void Cache::cycle()
{
// Only one access per cycle
// Read from port and access ??
// if memory req is back
// 	fill(addr);
// 	mshr complete 
}
