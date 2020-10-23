#ifdef _WIN32
#include "platform.h"
#include "pthread.h"
#include <Windows.h>

namespace platform
{
	uint64_t available_memory()
	{
		MEMORYSTATUSEX memInfo{ .dwLength = sizeof(MEMORYSTATUSEX) };
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullAvailPhys;
	}

	uint64_t available_swap_space()
	{
		MEMORYSTATUSEX memInfo{ .dwLength = sizeof(MEMORYSTATUSEX) };
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullAvailPageFile;
	}

	uint64_t used_swap_space()
	{
		MEMORYSTATUSEX memInfo{ .dwLength = sizeof(MEMORYSTATUSEX) };
		GlobalMemoryStatusEx(&memInfo);
		return memInfo.ullTotalPageFile - memInfo.ullAvailPhys;
	}

	void sleep(std::chrono::nanoseconds ns)
	{
		using namespace std::chrono;

		auto nanoseconds = ns.count();
		auto seconds = nanoseconds / 1'000'000'000;
		nanoseconds -= seconds * 1'000'000'000;
		timespec request
		{
			.tv_sec = seconds,
			.tv_nsec = static_cast<long>(nanoseconds)
		};

		nanosleep(&request, nullptr);
	}
}
#endif //_WIN32