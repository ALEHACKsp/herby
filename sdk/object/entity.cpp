#include "sdk/object/entity.hpp"
#include "sdk/object/weapon.hpp"

#include "csgo/engine.hpp"

C_BaseEntity* C_BaseEntity::GetBaseEntity( const int index )
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntity( index );
	return ( C_BaseEntity* )( client_entity );
}

C_BaseEntity* C_BaseEntity::GetBaseEntityFromHandle( const ULONG& base_handle )
{
	const auto client_entity = csgo::m_client_entity_list->GetClientEntityFromHandle( base_handle );
	return ( C_BaseEntity* )( client_entity );
}

bool C_BaseAnimating::GetBoneTransform( matrix3x4_t* bone_transform, const float time )
{
	const auto client_renderable = GetClientRenderable();

	if( !client_renderable )
		return false;

	return client_renderable->SetupBones( bone_transform, 128, 0x0100, time );
}

bool C_BaseAnimating::GetBonePosition( matrix3x4_t* bone_transform, const int bone, Vector& output )
{
	if( bone_transform )
	{
		for( auto i = 0; i < 3; i++ )
			output[ i ] = bone_transform[ bone ][ i ][ 3 ];
	}

	return ( !output.IsZero() && output.IsValid() );
}

