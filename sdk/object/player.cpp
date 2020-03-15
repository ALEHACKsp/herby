#include "sdk/object/player.hpp"

#include "csgo/engine.hpp"

const Vector& C_BasePlayer::EyePosition() const
{
	return ( m_vecOrigin() + m_vecViewOffset() );
}

C_CSPlayer* C_CSPlayer::GetLocalCSPlayer()
{
	const auto base_entity = C_BaseEntity::GetBaseEntity( csgo::m_engine_client->GetLocalPlayer() );
	return ToCSPlayer( base_entity );
}

C_CSPlayer* C_CSPlayer::GetCSPlayer( const int index )
{
	const auto base_entity = C_BaseEntity::GetBaseEntity( index );
	return ToCSPlayer( base_entity );
}