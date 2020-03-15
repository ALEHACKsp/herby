#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

#include "sdk/object/entity.hpp"
#include "sdk/object/player.hpp"
#include "sdk/object/weapon.hpp"

namespace csgo::hook
{

bool RenderBegin()
{
	m_renderer_text_array.clear();
	m_renderer_line_array.clear();
	m_renderer_rect_array.clear();

	return true;
}

void RenderEnd()
{

}

void RenderText( const ImVec2& coords, unsigned layout, const ImColor& color, const char* message, ... )
{
	char output[ 1024 ] = { };

	va_list args;
	va_start( args, message );
	vsprintf_s( output, message, args );
	va_end( args );

	m_renderer_text_array.push_back( { coords, layout, color, output } );
}

void RenderLine( const ImVec2& start, const ImVec2& end, const ImColor& color, float width = 1.f )
{
	m_renderer_line_array.push_back( { start, end, color, width } );
}

void RenderRect( const ImVec2& coords, const ImVec2& size, const ImColor& color, bool rected = true )
{
	m_renderer_rect_array.push_back( { coords, size, color, rected } );
}

void RenderPlayer( C_CSPlayer* player, int index )
{
	Vector2D screen = { };

	if( WorldToScreen( player->m_vecOrigin(), screen ) )
	{
		// TODO
		RenderText( { screen.x, screen.y }, engine::TextCenterH, { 1.f, 1.f, 1.f }, "nigger" );
	}
}

void RenderScene()
{
	const auto local_player = C_CSPlayer::GetLocalCSPlayer();

	if( !local_player )
		return;

	for( auto i = 1; i <= 64; i++ )
	{
		const auto player = C_CSPlayer::GetCSPlayer( i );

		if( !player )
			continue;

		RenderPlayer( player, i );
	}
}

INT API_FASTCALL FrameStageNotify( void* ecx, void* edx, int stage )
{
	if( stage == 5 ) // frame render start
	{
		if( RenderBegin() )
		{
			RenderScene();

			RenderEnd();
		}
	}

	m_frame_stage_notify_hook->Restore();
	const auto result = m_frame_stage_notify_hook->Call< INT >( ecx, stage );
	m_frame_stage_notify_hook->Replace();

	return result;

}

}