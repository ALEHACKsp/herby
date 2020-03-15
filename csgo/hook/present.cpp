#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

namespace csgo::hook
{

void RenderMap()
{
	auto& renderer = engine::Renderer::Instance();

	for( const auto& entry : m_renderer_text_array )
		renderer.DrawText( entry.m_begin, entry.m_layout, entry.m_color, entry.m_message.c_str() );

	for( const auto& entry : m_renderer_line_array )
		renderer.DrawLine( entry.m_begin, entry.m_end, entry.m_color, entry.m_width );

	for( const auto& entry : m_renderer_rect_array )
		renderer.DrawRect( entry.m_begin, entry.m_size, entry.m_color, entry.m_rected );
}

HRESULT API_D3D Present( IDirect3DDevice9* device, const RECT* source_rect, const RECT* dest_rect, HWND dest_window_override, const RGNDATA* dirty_region )
{
	auto& renderer = engine::Renderer::Instance();

	if( renderer.Begin() )
	{
		RenderMap();

		renderer.DrawText( { 20.f, 10.f }, engine::TextLeft, { 1.f, 1.f, 1.f }, "overlay" );
		
		renderer.End();
		renderer.Present();
	}

	m_present_hook->Restore();
	const auto result = m_present_hook->Win32Call< HRESULT >( device, source_rect, dest_rect, dest_window_override, dirty_region );
	m_present_hook->Replace();

	return result;
}

}