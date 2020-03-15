#pragma once

#include <iostream>

namespace shared::memory
{

template< std::size_t N, typename T >
T vget( void* object )
{
	const auto procedure_array = *( std::uintptr_t** )( object );
	return ( T )( procedure_array[ N ] );
}

template< std::size_t N, typename T, typename... ArgsT >
T Call( void* object, ArgsT... args )
{
	const auto procedure = vget< N, T( __thiscall* )( void*, ArgsT... ) >( object );
	return procedure( object, args... );
}


}