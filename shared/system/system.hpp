#pragma once

#include "shared/include/auto.hpp"
#include "shared/include/win32.hpp"

#include "shared/detail/singleton.hpp"

namespace shared::win32
{

enum ExecuteState
{
	Work,
	Question,
	Quit,
	Gui,
};

class System : public detail::Singleton< System >
{
public:
	~System();

public:
	bool Create();
	void Destroy();

	ExecuteState GetExecuteState() const;
	void SetExecuteState( const ExecuteState execute_state );

public:
	bool Gui();
	void Gui( bool gui );

private:
	static bool MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

private:
	ExecuteState m_execute_state = ExecuteState::Work;
};

}