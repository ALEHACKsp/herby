#pragma once

#include "sdk/sdk.hpp"

namespace csgo::engine
{

class NetPropSystem : public detail::Singleton< NetPropSystem >
{
public:
	bool Create();
	void Destroy();

	int Get( const char* recv_table_name, const char* recv_prop_name ) const;

private:
	int GetRecursive( RecvTable* recv_table, const char* recv_prop_name ) const;

	RecvTable* GetRecvTable( const char* recv_table_name ) const;

private:
	std::vector< RecvTable* > m_recv_table_array = { };
};

}

#define NET_PROP( return_type, name, recv_table_name, recv_prop_name ) \
	return_type& name ## () const \
	{ \
		const auto& net_prop_system = csgo::engine::NetPropSystem::Instance(); \
		static auto displacement = 0; \
        if( !displacement ) \
             displacement = net_prop_system.Get( recv_table_name, recv_prop_name ); \
		return *( return_type* )( this + displacement ); \
	}

#define NET_PROP_EX( return_type, name, recv_table_name, recv_prop_name, extra ) \
	return_type& name ## () const \
	{ \
		const auto& net_prop_system = csgo::engine::NetPropSystem::Instance(); \
		static auto displacement = 0; \
        if( !displacement ) \
             displacement = ( net_prop_system.Get( recv_table_name, recv_prop_name ) + extra ); \
		return *( return_type* )( this + displacement ); \
	}