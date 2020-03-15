#include "shared/system/system.hpp"

#include "shared/auto.hpp"

namespace shared::win32
{

System::~System()
{
	Destroy();
}

bool System::Create()
{
	auto& input = win32::Input::Instance();

	if( !input.AddEvent( &MessageProcedure ) )
		return false;

	return true;
}

void System::Destroy()
{
	m_execute_state = ExecuteState::Quit;
}

ExecuteState System::GetExecuteState() const
{
	return m_execute_state;
}

void System::SetExecuteState( const ExecuteState execute_state )
{
	m_execute_state = execute_state;
}

bool System::Gui()
{
	auto& system = System::Instance();
	return ( system.GetExecuteState() == ExecuteState::Gui );
}

void System::Gui( bool gui )
{
	auto& system = System::Instance();
	system.SetExecuteState( gui ? ExecuteState::Gui : system.GetExecuteState() );
}

bool System::MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	auto& system = System::Instance();

	auto execute = false;

	switch( message )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if( wparam == VK_F11 )
			{
				execute = true;
				system.SetExecuteState( ExecuteState::Quit );
			}
			else if( wparam == VK_INSERT )
			{
				execute = true;
				system.SetExecuteState( ExecuteState::Gui );
			}

			break;
		}
	}

	return execute;
}

}