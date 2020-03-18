#pragma once

#include "shared/auto.hpp"

namespace csgo::hook
{

HRESULT API_D3D Present( IDirect3DDevice9* device, const RECT* source_rect, const RECT* dest_rect, HWND dest_window_override, const RGNDATA* dirty_region );
HRESULT API_D3D Reset( IDirect3DDevice9* device, D3DPRESENT_PARAMETERS* presentation_parameters );

INT API_FASTCALL FrameStageNotify( void* ecx, void* edx, int stage );

}
