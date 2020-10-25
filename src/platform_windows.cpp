#ifdef _WIN32
#include "platform.h"
#include "pthread.h"
#include <Windows.h>

using namespace std::chrono;

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

	void sleep(high_resolution_clock::duration duration)
	{
		using namespace std::chrono;

		auto nanos = duration_cast<nanoseconds>(duration).count();
		auto seconds = nanos / 1'000'000'000;
		nanos -= seconds * 1'000'000'000;
		timespec request
		{
			.tv_sec = seconds,
			.tv_nsec = static_cast<long>(nanos)
		};

		nanosleep(&request, nullptr);
	}
}
#endif //_WIN32