#include "sdk/object/weapon.hpp"

#include "csgo/engine.hpp"

bool C_WeaponCSBase::IsFireTime()
{
	return ( csgo::m_globals->curtime >= m_flNextPrimaryAttack() );
}

bool C_WeaponCSBase::IsSecondaryFireTime()
{
	return ( csgo::m_globals->curtime >= m_flNextSecondaryAttack() );
}

bool C_WeaponCSBase::IsGun() 
{
	auto data = GetCSWeaponData();

	if( !data )
		return false;

	return ( data->m_type != WEAPONTYPE_KNIFE &&
		data->m_type != WEAPONTYPE_C4 &&
		data->m_type != WEAPONTYPE_GRENADE );
}

bool C_WeaponCSBase::IsPistol()
{
	auto data = GetCSWeaponData();
	return ( data ? data->m_type == WEAPONTYPE_PISTOL : false );
}

CCSWeaponInfo* C_WeaponCSBase::GetCSWeaponData()
{
	static auto procedure = memory::scan< CCSWeaponInfo*( __thiscall* )( void* ) >( L"client_panorama.dll", "55 8B EC 81 EC ? ? ? ? 53 8B D9 56 57 8D 8B" );
	return procedure( this );
}