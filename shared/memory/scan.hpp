#pragma once

#include "shared/memory/macro.hpp"

#include "shared/include/auto.hpp"
#include "shared/include/win32.hpp"

namespace shared::memory
{

std::uintptr_t ScanLocation( const std::uintptr_t location,
	const std::size_t size,
	const std::string& signature,
	const std::intptr_t displacement = 0,
	const std::size_t read = 0 );

std::uintptr_t ScanImage( const std::wstring& image_name,
	const std::string& signature,
	const std::intptr_t displacement = 0,
	const std::size_t read = 0 );

template< typename T >
T scan( const std::wstring& image_name,
	const std::string& signature,
	const std::intptr_t displacement = 0,
	const std::size_t read = 0 )
{
	const auto scan_result = ScanImage( image_name, signature, displacement, read );
	return ( T )( scan_result );
}

}