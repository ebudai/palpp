#pragma once

#include <cstdint>
#include <chrono>

namespace platform
{
	uint64_t available_memory();
	uint64_t available_swap_space();
	uint64_t used_swap_space();
	void sleep(std::chrono::high_resolution_clock::duration duration);
	void set_denormals_to_zero();
	void minimize_system_timer_resolution();
	void restore_system_timer_resolution();
}