#pragma once

#include "shared/include/win32.hpp"
#include "shared/include/auto.hpp"

#include "shared/detail/no_copy.hpp"
#include "shared/detail/no_move.hpp"

namespace shared::memory
{

class ObjectHook : public detail::NoCopy, public detail::NoMove
{
public:
	using Shared = std::shared_ptr< ObjectHook >;

public:
	ObjectHook() = default;

public:
	ObjectHook( void* procedure, void* replace );
	~ObjectHook();

public:
	bool Create( void* procedure, void* replace );
	void Destroy();

	void Replace();
	void Restore();

public:
	template< typename T, typename... ArgsT >
	T Call( ArgsT... args )
	{
		auto fn = reinterpret_cast< T( __thiscall* )( ArgsT... ) >( m_procedure );
		return fn( args... );
	}

	template< typename T, typename... ArgsT >
	T Win32Call( ArgsT... args )
	{
		auto fn = reinterpret_cast< T( __stdcall* )( ArgsT... ) >( m_procedure );
		return fn( args... );
	}

	template< typename T, typename... ArgsT >
	T FastCall( ArgsT... args )
	{
		auto fn = reinterpret_cast< T( __fastcall* )( ArgsT... ) >( m_procedure );
		return fn( args... );
	}

private:
	std::uint8_t* m_restore = nullptr;
	DWORD m_protect = 0;

	std::uint8_t* m_procedure = nullptr;
	void* m_replace = nullptr;
};

}