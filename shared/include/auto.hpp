#pragma once

#include <iostream>
#include <chrono>
#include <algorithm>
#include <string>
#include <vector>
#include <atomic>
#include <future>
#include <mutex>
#include <thread>

using namespace std::chrono_literals;
using namespace std::string_literals;

#define API_INLINE __inline
#define API_FORCEINLINE __forceinline

#define API_CDECL __cdecl
#define API_STDCALL __stdcall
#define API_THISCALL __thiscall
#define API_FASTCALL __fastcall

#define API_NT API_STDCALL
#define API_WIN32 API_STDCALL
#define API_D3D API_STDCALL
