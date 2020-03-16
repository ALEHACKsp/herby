#pragma once

#include "sdk/object/entity.hpp"

//#include "source/engine.hpp"

enum CSWeaponType
{
	WEAPONTYPE_KNIFE = 0,
	WEAPONTYPE_PISTOL,
	WEAPONTYPE_SUBMACHINEGUN,
	WEAPONTYPE_RIFLE,
	WEAPONTYPE_SHOTGUN,
	WEAPONTYPE_SNIPER_RIFLE,
	WEAPONTYPE_MACHINEGUN,
	WEAPONTYPE_C4,
	WEAPONTYPE_PLACEHOLDER,
	WEAPONTYPE_GRENADE,
	WEAPONTYPE_UNKNOWN
};

class CCSWeaponInfo
{
public:
	PAD( 0x0088 );
	const char* m_hud_name = nullptr;
	const char* m_weapon_name = nullptr;
	PAD( 0x0038 );
	CSWeaponType m_type = WEAPONTYPE_UNKNOWN;
	PAD( 0x0020 );
	int m_damage = 0;
	float m_armor_ratio = 0.f;
	int m_bullets = 0;
	float m_penetration = 0.f;
	PAD( 0x0008 );
	float m_range = 0.f;
	float m_range_modifier = 0.f;
	PAD( 0x0030 );
	float m_inaccuracy_crouch = 0.f;
	PAD( 0x0030 );
	float m_inaccuracy_move = 0.f;
};

class C_BaseCombatWeapon : public C_BaseEntity
{
public:
	NET_PROP( short, m_iItemDefinitionIndex, "DT_BaseAttributableItem", "m_iItemDefinitionIndex" );

	NET_PROP( int, m_iClip1, "DT_BaseCombatWeapon", "m_iClip1" );
	NET_PROP( int, m_iClip2, "DT_BaseCombatWeapon", "m_iClip2" );
	NET_PROP( int, m_iPrimaryAmmoType, "DT_BaseCombatWeapon", "m_iPrimaryAmmoType" );
	NET_PROP( int, m_iSecondaryAmmoType, "DT_BaseCombatWeapon", "m_iSecondaryAmmoType" );

	NET_PROP( float, m_flNextPrimaryAttack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	NET_PROP( float, m_flNextSecondaryAttack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );
};

class C_WeaponCSBase : public C_BaseCombatWeapon
{
public:
	bool IsFireTime();
	bool IsSecondaryFireTime();

	bool IsGun();
	bool IsPistol();

	CCSWeaponInfo* GetCSWeaponData();

public:
	NET_PROP( float, m_fAccuracyPenalty, "DT_WeaponCSBase", "m_fAccuracyPenalty" );
	NET_PROP( float, m_flRecoilIndex, "DT_WeaponCSBase", "m_flRecoilIndex" );
};

class C_BaseAnimating : public C_BaseEntity
{
public:
	bool GetBoneTransform( matrix3x4_t* bone_transform, const float time );
	bool GetBonePosition( matrix3x4_t* bone_transform, const int bone, Vector& output );

public:
	NET_PROP( bool, m_bClientSideAnimation, "DT_BaseAnimating", "m_bClientSideAnimation" );
	NET_PROP( bool, m_bClientSideFrameReset, "DT_BaseAnimating", "m_bClientSideFrameReset" );

	NET_PROP( int, m_nSequence, "DT_BaseAnimating", "m_nSequence" );
	NET_PROP( int, m_nForceBone, "DT_BaseAnimating", "m_nForceBone" );
	NET_PROP( int, m_nSkin, "DT_BaseAnimating", "m_nSkin" );
	NET_PROP( int, m_nBody, "DT_BaseAnimating", "m_nBody" );
	NET_PROP( int, m_nHitboxSet, "DT_BaseAnimating", "m_nHitboxSet" );

	NET_PROP( float, m_flCycle, "DT_BaseAnimating", "m_flCycle" );
	NET_PROP( float, m_flPlaybackRate, "DT_BaseAnimating", "m_flPlaybackRate" );

	NET_PROP( Vector, m_vecForce, "DT_BaseAnimating", "m_vecForce" );
};

class C_BaseAnimatingOverlay : public C_BaseAnimating
{
public:

};

class C_BaseCombatCharacter : public C_BaseAnimatingOverlay
{
public:
	C_WeaponCSBase* GetActiveWeapon()
	{
		const auto base_entity = C_BaseEntity::GetBaseEntityFromHandle( m_hActiveWeapon() );

		if( !base_entity )
			return nullptr;

		return reinterpret_cast< C_WeaponCSBase* >( base_entity );
	}

public:
	NET_PROP( ULONG, m_hActiveWeapon, "DT_BaseCombatCharacter", "m_hActiveWeapon" );
	NET_PROP( float, m_flNextAttack, "DT_BaseCombatCharacter", "m_flNextAttack" );
};