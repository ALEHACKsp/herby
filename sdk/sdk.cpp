#include "sdk/sdk.hpp"

#include "csgo/engine.hpp"

std::vector< render_text_data_t > m_renderer_text_array = { };
std::vector< render_line_data_t > m_renderer_line_array = { };
std::vector< render_rect_data_t > m_renderer_rect_array = { };

VMatrix WorldToScreenMatrix()
{
	static auto pointer = memory::scan< std::uintptr_t* >( L"client_panorama.dll", "0F 10 05 ? ? ? ? 8D 85 ? ? ? ? B9", 3 );
	return *( VMatrix* )( *pointer + 0x00B0 );
}

bool WorldToScreen( const Vector& world, Vector2D& screen )
{
	auto mat = WorldToScreenMatrix();

	auto z = mat[ 3 ][ 0 ] * world[ 0 ] + mat[ 3 ][ 1 ] * world[ 1 ] + mat[ 3 ][ 2 ] * world[ 2 ] + mat[ 3 ][ 3 ];

	if( z < 0.01f )
		return false;

	auto inverse = 1.f / z;

	screen[ 0 ] = ( mat[ 0 ][ 0 ] * world[ 0 ] + mat[ 0 ][ 1 ] * world[ 1 ] + mat[ 0 ][ 2 ] * world[ 2 ] + mat[ 0 ][ 3 ] ) * inverse;
	screen[ 1 ] = ( mat[ 1 ][ 0 ] * world[ 0 ] + mat[ 1 ][ 1 ] * world[ 1 ] + mat[ 1 ][ 2 ] * world[ 2 ] + mat[ 1 ][ 3 ] ) * inverse;

	auto w = 0, h = 0;
	csgo::m_engine_client->GetScreenSize(w, h);

	auto x = static_cast< float >( w ) / 2.f;
	auto y = static_cast< float >( h ) / 2.f;

	x += 0.5f * screen[ 0 ] * static_cast< float >( w ) + 0.5f;
	y -= 0.5f * screen[ 1 ] * static_cast< float >( h ) + 0.5f;

	screen[ 0 ] = x;
	screen[ 1 ] = y;

	return true;
}