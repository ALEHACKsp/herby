#pragma once

#include "shared/include/auto.hpp"
#include "shared/include/win32.hpp"

#include "shared/detail/singleton.hpp"

namespace shared::win32
{

using EventFn = bool( * )( HWND window, UINT message, WPARAM wparam, LPARAM lparam);

class Input : public detail::Singleton< Input >
{
public:
	bool Create();
	void Destroy();

	void SetWindow( HWND window );
	HWND GetWindow() const;

	bool AddEvent( EventFn procedure );
	LRESULT ExecuteEventArray( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

private:
	static BOOL WINAPI EnumProcedure( HWND window, LPARAM lparam );
	static LRESULT WINAPI MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam );

private:
	HWND m_window = nullptr;
	WNDPROC m_procedure = nullptr;
	std::vector< EventFn > m_event_array = { };
};

}