#pragma once

#include "sdk/sdk.hpp"

#include "csgo/engine/renderer.hpp"

#include "csgo/feature/triggerbot.hpp"
#include "csgo/feature/aimbot.hpp"
#include "csgo/feature/gui.hpp"

#include "csgo/hook/procedure.hpp"

#include "csgo/feature/aimbot.hpp"

namespace csgo
{

extern IBaseClientDLL* m_base_client;
extern IClientEntityList* m_client_entity_list;
extern IVEngineClient* m_engine_client;

extern CGlobalVarsBase* m_globals;

extern IDirect3DDevice9* m_direct_device;

extern memory::ObjectHook::Shared m_present_hook;
extern memory::ObjectHook::Shared m_reset_hook;

extern memory::ObjectHook::Shared m_frame_stage_notify_hook;

bool Create();
void Destroy();

}