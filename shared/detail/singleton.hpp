#pragma once

#include "shared/detail/no_copy.hpp"
#include "shared/detail/no_move.hpp"

namespace shared::detail
{

template< typename T >
class Singleton : public NoCopy, NoMove
{
public:
	Singleton() = default;

public:
	static T& Instance()
	{
		static T object = { };
		return object;
	}
};

}