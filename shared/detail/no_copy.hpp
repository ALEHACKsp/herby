#pragma once

namespace shared::detail
{

class NoCopy
{
protected:
	NoCopy() = default;
	NoCopy( const NoCopy& ) = delete;

protected:
	NoCopy& operator=( const NoCopy& ) = delete;
};

}