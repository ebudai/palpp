#pragma once

#include <cstdint>
#include <chrono>

namespace platform
{
	uint64_t available_memory();
	uint64_t available_swap_space();
	uint64_t used_swap_space();
	void sleep(int64_t ns);
	
	template <typename rep, typename period> 
	void sleep(std::chrono::duration<rep, period> time)
	{
		sleep(std::chrono::duration_cast<std::chrono::nanoseconds>(time).count());
	}
}