#include "csgo/feature/gui.hpp"

namespace csgo::feature
{

bool Gui::Create()
{
	auto& input = win32::Input::Instance();

	if( !input.AddEvent( &Gui::MessageProcedure ) )
		return false;

	auto& style = ImGui::GetStyle();

	ImGui::StyleColorsDark();

	style.WindowPadding = { 8.f, 8.f };
	style.WindowRounding = 0.f;
	style.WindowBorderSize = 0.f;
	style.ChildRounding = 0.f;
	style.ChildBorderSize = 1.f;
	style.PopupRounding = 0.f;
	style.PopupBorderSize = 0.f;
	style.FramePadding = { 4.f, 2.f };
	style.FrameRounding = 0.f;
	style.FrameBorderSize = 0.f;
	style.IndentSpacing = 20.f;
	style.ScrollbarSize = 14.f;
	style.ScrollbarRounding = 0.f;
	style.GrabMinSize = 10.f;
	style.GrabRounding = 0.f;

	return true;
}

void Gui::Destroy()
{

}

void Gui::Present()
{
	auto& system = win32::System::Instance();

	if( !system.Gui() )
		return;

	// TODO
}

bool Gui::MessageProcedure( HWND window, UINT message, WPARAM wparam, LPARAM lparam )
{
	auto& system = win32::System::Instance();

	switch( message )
	{
		case WM_KEYDOWN:
		case WM_SYSKEYDOWN:
		{
			if( wparam == VK_HOME )
			{
				system.Gui( !system.Gui() );
				return true;
			}

			break;
		}
	}

	if( system.Gui() )
	{
		if( ImGui_ImplWin32_WndProcHandler( window, message, wparam, lparam ) )
			return true;
	}

	return false;
}

}