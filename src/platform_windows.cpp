#ifdef _WIN32
#include "platform.h"
#include "pthread.h"
#include "intrinsics.h"
#include <Windows.h>

using namespace std::chrono;

extern "C" NTSYSAPI NTSTATUS NTAPI NtSetTimerResolution(ULONG DesiredResolution, BOOLEAN SetResolution, PULONG CurrentResolution);
extern "C" NTSYSAPI NTSTATUS NTAPI NtQueryTimerResolution(OUT PULONG MinimumResolution,	OUT PULONG MaximumResolution, OUT PULONG CurrentResolution);

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

	void set_denormals_to_zero()
	{
		uint32_t current_word = 0;
		_controlfp_s(&current_word, _DN_FLUSH, _MCW_DN);
		_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
		_MM_SET_DENORMALS_ZERO_MODE(_MM_DENORMALS_ZERO_ON);
	}

	void minimize_system_timer_resolution()
	{
		ULONG minimum_resolution;
		ULONG maximum_resolution;
		ULONG current_resolution;
		NtQueryTimerResolution(&minimum_resolution, &maximum_resolution, &current_resolution);
		NtSetTimerResolution(maximum_resolution, TRUE, &current_resolution);
	}

	void restore_system_timer_resolution()
	{
		ULONG old_resolution;
		NtSetTimerResolution(0, FALSE, &old_resolution);
	}
}
#endif //_WIN32