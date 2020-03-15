#include "csgo/engine/net_prop_system.hpp"

#include "csgo/engine.hpp"

namespace csgo::engine
{

bool NetPropSystem::Create()
{
	for( auto client_class = m_base_client->GetAllClasses(); client_class; client_class = client_class->m_pNext )
	{
		const auto recv_table = client_class->m_pRecvTable;

		if( recv_table )
			m_recv_table_array.emplace_back( recv_table );
	}

	return !m_recv_table_array.empty();
}

void NetPropSystem::Destroy()
{
	m_recv_table_array.clear();
}

int NetPropSystem::Get( const char* recv_table_name, const char* recv_prop_name ) const
{
	const auto recv_table = GetRecvTable( recv_table_name );

	if( !recv_table )
		return 0;

	return GetRecursive( recv_table, recv_prop_name );
}

int NetPropSystem::GetRecursive( RecvTable* recv_table, const char* recv_prop_name ) const
{
	auto extra = 0;

	for( auto i = 0; i < recv_table->m_nProps; i++ )
	{
		const auto recv_prop = &recv_table->m_pProps[ i ];

		if( recv_prop )
		{
			const auto data_table = recv_prop->m_pDataTable;

			if( data_table && data_table->m_nProps )
			{
				const auto displacement = GetRecursive( data_table, recv_prop_name );

				if( displacement )
					extra += ( recv_prop->m_Offset + displacement );
			}

			if( !std::strcmp( recv_prop->m_pVarName, recv_prop_name ) )
				return ( recv_prop->m_Offset + extra );
		}
	}

	return extra;
}

RecvTable* NetPropSystem::GetRecvTable( const char* recv_table_name ) const
{
	if( !m_recv_table_array.empty() )
	{
		for( const auto& recv_table : m_recv_table_array )
		{
			if( !std::strcmp( recv_table_name, recv_table->m_pNetTableName ) )
				return recv_table;
		}
	}

	return nullptr;
}

}