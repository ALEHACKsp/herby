#pragma once

#include "csgo/engine/net_prop_system.hpp"

//#include "sdk/object/weapon.hpp"

class IClientNetworkable
{
public:
	ClientClass* GetClientClass()
	{
		return memory::Call< 2, ClientClass* >( this );
	}

	bool IsDormant()
	{
		return memory::Call< 9, bool >( this );
	}

	int GetIndex() 
	{
		return memory::Call< 10, int >( this );
	}
};

class IClientRenderable
{
public:
	model_t* GetModel()
	{
		return memory::Call< 8, model_t* >( this );
	}

	int DrawModel( int flags, const int& instance )
	{
		return memory::Call< 9, int >( this, flags, instance );
	}

	bool SetupBones( matrix3x4_t* pBoneToWorldOut, int nMaxBones, int boneMask, float currentTime )
	{
		return memory::Call< 13, bool >( pBoneToWorldOut, nMaxBones, boneMask, currentTime );
	}
};

class IClientUnknown
{
public:
	IClientNetworkable* GetClientNetworkable()
	{
		return memory::Call< 4, IClientNetworkable* >( this );
	}

	IClientRenderable* GetClientRenderable()
	{
		return memory::Call< 5, IClientRenderable* >( this );
	}
};

class C_BaseEntity : public IClientUnknown
{
public:
	static C_BaseEntity* GetBaseEntity( const int index );
	static C_BaseEntity* GetBaseEntityFromHandle( const ULONG& base_handle );

public:
	NET_PROP( int, m_iTeamNum, "DT_BaseEntity", "m_iTeamNum" );

	NET_PROP( float, m_flSimulationTime, "DT_BaseEntity", "m_flSimulationTime" );

	NET_PROP( Vector, m_vecOrigin, "DT_BaseEntity", "m_vecOrigin" );

	NET_PROP( QAngle, m_angRotation, "DT_BaseEntity", "m_angRotation" );

public:
	NET_PROP_EX( const matrix3x4_t, m_rgflCoordinateFrame, "DT_BaseEntity", "m_CollisionGroup", -0x0030 );
};
