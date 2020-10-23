#pragma once

#ifdef _WIN32
#	include <immintrin.h>
#elif defined(__linux__)
#	include <x86intrin.h>
#elif defined(MACOS)
#	include <x86intrin.h>
#endif