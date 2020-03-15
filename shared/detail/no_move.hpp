#pragma once

namespace shared::detail
{

class NoMove
{
protected:
	NoMove() = default;
	NoMove( NoMove&& ) = delete;

protected:
	NoMove& operator=( NoMove&& ) = delete;
};

}