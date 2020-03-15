#pragma once

#include "sdk/object/entity.hpp"
#include "sdk/object/weapon.hpp"

class C_BasePlayer : public C_BaseCombatCharacter
{
public:
	const Vector& EyePosition() const;

public:
	NET_PROP( char, m_lifeState, "DT_BasePlayer", "m_lifeState" );

	NET_PROP( bool, m_bDucked, "DT_BasePlayer", "m_bDucked" );
	NET_PROP( bool, m_bDucking, "DT_BasePlayer", "m_bDucking" );
	NET_PROP( bool, m_bInDuckJump, "DT_BasePlayer", "m_bInDuckJump" );
	NET_PROP( bool, m_bDrawViewmodel, "DT_BasePlayer", "m_bDrawViewmodel" );

	NET_PROP( int, m_iAmmo, "DT_BasePlayer", "m_iAmmo" );
	NET_PROP( int, m_nTickBase, "DT_BasePlayer", "m_nTickBase" );
	NET_PROP( int, m_nWaterLevel, "DT_BasePlayer", "m_nWaterLevel" );
	NET_PROP( int, m_iFOV, "DT_BasePlayer", "m_iFOV" );
	NET_PROP( int, m_iDefaultFOV, "DT_BasePlayer", "m_iDefaultFOV" );
	NET_PROP( int, m_iHealth, "DT_BasePlayer", "m_iHealth" );
	NET_PROP( int, m_fFlags, "DT_BasePlayer", "m_fFlags" );
	NET_PROP( int, m_iObserverMode, "DT_BasePlayer", "m_iObserverMode" );

	NET_PROP( float, m_flFallVelocity, "DT_BasePlayer", "m_flFallVelocity" );
	NET_PROP( float, m_flStepSize, "DT_BasePlayer", "m_flStepSize" );
	NET_PROP( float, m_flFriction, "DT_BasePlayer", "m_flFriction" );
	NET_PROP( float, m_flDeathTime, "DT_BasePlayer", "m_flDeathTime" );
	NET_PROP( float, m_flLaggedMovementValue, "DT_BasePlayer", "m_flLaggedMovementValue" );
	NET_PROP( float, m_flMaxspeed, "DT_BasePlayer", "m_flMaxspeed" );

	NET_PROP( Vector, m_vecViewOffset, "DT_BasePlayer", "m_vecViewOffset[0]" );
	NET_PROP( Vector, m_vecVelocity, "DT_BasePlayer", "m_vecVelocity[0]" );
	NET_PROP( Vector, m_vecBaseVelocity, "DT_BasePlayer", "m_vecBaseVelocity" );

	NET_PROP( QAngle, m_aimPunchAngle, "DT_BasePlayer", "m_aimPunchAngle" );
	NET_PROP( QAngle, m_vecPunchAngle, "DT_BasePlayer", "m_vecPunchAngle" );
	NET_PROP( QAngle, m_vecPunchAngleVel, "DT_BasePlayer", "m_vecPunchAngleVel" );

	NET_PROP( ULONG, m_hLastWeapon, "DT_BasePlayer", "m_hLastWeapon" );
	NET_PROP( ULONG, m_hGroundEntity, "DT_BasePlayer", "m_hGroundEntity" );
	NET_PROP( ULONG, m_hObserverTarget, "DT_BasePlayer", "m_hObserverTarget" );
};

class C_CSPlayer : public C_BasePlayer
{
public:
	static C_CSPlayer* GetLocalCSPlayer();
	static C_CSPlayer* GetCSPlayer( const int index );

public:
	NET_PROP( bool, m_bIsDefusing, "DT_CSPlayer", "m_bIsDefusing" );

	NET_PROP( int, m_ArmorValue, "DT_CSPlayer", "m_ArmorValue" );
	NET_PROP( int, m_iShotsFired, "DT_CSPlayer", "m_iShotsFired" );
};

API_INLINE C_BasePlayer* ToBasePlayer( C_BaseEntity* base_entity )
{
	if( !base_entity )
		return nullptr;

	const auto player = ( C_BasePlayer* )( base_entity );

	if( player->m_iHealth() <= 0 )
		return nullptr;

	const auto client_networkable = player->GetClientNetworkable();

	if( !client_networkable )
		return nullptr;

	if( client_networkable->IsDormant() )
		return nullptr;

	return player;
}

API_INLINE C_CSPlayer* ToCSPlayer( C_BaseEntity* base_entity )
{
	if( !base_entity )
		return nullptr;

	const auto player = ( C_CSPlayer* )( base_entity );
	
	if( player->m_iHealth() <= 0 )
		return nullptr;

	const auto client_networkable = player->GetClientNetworkable();

	if( !client_networkable )
		return nullptr;

	if( client_networkable->IsDormant() )
		return nullptr;

	return player;
}