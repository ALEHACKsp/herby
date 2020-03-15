#include "csgo/engine.hpp"

#include "csgo/engine/factory.hpp"
#include "csgo/engine/net_prop_system.hpp"

namespace csgo
{

IBaseClientDLL* m_base_client = nullptr;
IClientEntityList* m_client_entity_list = nullptr;
IVEngineClient* m_engine_client = nullptr;

CGlobalVarsBase* m_globals = nullptr;

IDirect3DDevice9* m_direct_device = nullptr;

memory::ObjectHook::Shared m_present_hook = { };
memory::ObjectHook::Shared m_reset_hook = { };

memory::ObjectHook::Shared m_frame_stage_notify_hook = { };

bool Create()
{
	auto& input = win32::Input::Instance();
	auto& system = win32::System::Instance();

	auto& gui = feature::Gui::Instance();

	auto& renderer = engine::Renderer::Instance();
	auto& net_prop_system = engine::NetPropSystem::Instance();

	engine::Factory factory_client( L"client_panorama.dll" );
	engine::Factory factory_engine( L"engine.dll" );

	if( !input.Create() )
		return false;
	
	if( !system.Create() )
		return false;

	m_base_client = factory_client.Get< IBaseClientDLL* >( "VClient" );

	if( !m_base_client )
		return false;

	m_client_entity_list = factory_client.Get< IClientEntityList* >( "VClientEntityList" );

	if( !m_client_entity_list )
		return false;

	m_engine_client = factory_engine.Get< IVEngineClient* >( "VEngineClient" );

	if( !m_engine_client )
		return false;

	m_globals = memory::scan< CGlobalVarsBase* >( L"client_panorama.dll", "A1 ? ? ? ? 0F 57 ED", 1, 2 );

	if( !m_globals )
		return false;

	m_direct_device = memory::scan< IDirect3DDevice9* >( L"shaderapidx9.dll", "B9 ? ? ? ? 8B 47", 1, 2 );

	if( !m_direct_device )
		return false;

	if( !renderer.Create( m_direct_device ) )
		return false;

	if( !net_prop_system.Create() )
		return false;

	if( !gui.Create() )
		return false;

	const auto present_address = memory::vget< 17, void* >( m_direct_device );
	const auto reset_address = memory::vget< 16, void* >( m_direct_device );

	const auto frame_stage_notify_address = memory::vget< 37, void* >( m_base_client );

	m_present_hook = std::make_shared< memory::ObjectHook >( present_address, &hook::Present );
	m_reset_hook = std::make_shared< memory::ObjectHook >( reset_address, &hook::Reset );

	m_frame_stage_notify_hook = std::make_shared< memory::ObjectHook >( frame_stage_notify_address, &hook::FrameStageNotify );

	return true;
}

void Destroy()
{
	auto& input = win32::Input::Instance();
	auto& system = win32::System::Instance();

	auto& gui = feature::Gui::Instance();

	auto& renderer = engine::Renderer::Instance();
	auto& net_prop_system = engine::NetPropSystem::Instance();
	
	input.Destroy();
	system.Destroy();
	
	gui.Destroy();

	renderer.Destroy();
	net_prop_system.Destroy();

	if( m_present_hook )
		m_present_hook.reset();

	if( m_reset_hook )
		m_reset_hook.reset();

	if( m_frame_stage_notify_hook )
		m_frame_stage_notify_hook.reset();
}

}