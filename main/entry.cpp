#include "csgo/engine.hpp"

void ImageLoad()
{
	if( !csgo::Create() )
	{
		// throw exception
	}
}

void ImageDestroy()
{
	csgo::Destroy();
}

BOOL WINAPI DllMain( HMODULE image, DWORD reason, LPVOID reserved )
{
	switch( reason )
	{
		case DLL_PROCESS_ATTACH:
		{
			ImageLoad();
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			ImageDestroy();
			break;
		}
	}

	return TRUE;
}