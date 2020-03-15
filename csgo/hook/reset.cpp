#include "csgo/hook/procedure.hpp"

#include "csgo/engine.hpp"

namespace csgo::hook
{

HRESULT API_D3D Reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters )
{
	auto& renderer = engine::Renderer::Instance();

	renderer.Lost();

	m_reset_hook->Restore();
	const auto result = m_reset_hook->Win32Call< HRESULT >( device, presentation_parameters );
	m_reset_hook->Replace();

	renderer.Reset( result );

	return result;
}

}