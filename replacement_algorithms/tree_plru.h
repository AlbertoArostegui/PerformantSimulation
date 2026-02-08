namespace TreePlru {
inline void update_plru(uint32_t& state, uint32_t way, uint32_t num_ways)
{
	uint32_t node_idx = 0;
	uint32_t levels = std::log2(num_ways);
	for (uint32_t i = 0; i < levels; ++i) {
		uint32_t bit_check = (way << (levels - 1 - i)) & 1;
		if (!bit_check) {
			state |= 1U << node_idx;
			node_idx = 2 * node_idx + 1;
		} else {
			state &= ~(1U << node_idx); 
			node_idx = 2 * node_idx + 2;
		}
	}
}
inline uint32_t get_victim(uint32_t& state, uint32_t num_ways)
{
	uint32_t node_idx = 0;
	uint32_t levels = std::log2(num_ways);
	uint32_t victim = 0;
	for (uint32_t i = 0; i < levels; ++i) {
		uint32_t right = state & (1U << node_idx);
		if (right) {
			node_idx = 2 * node_idx + 2;
			victim |= (1 << (levels - 1 - i)); 
		} else {
			node_idx = 2 * node_idx + 1;
		}
	}
	return victim;
}
};
