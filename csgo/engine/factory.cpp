#include "csgo/engine/factory.hpp"

#include "sdk/sdk.hpp"

namespace csgo::engine
{

Factory::Factory( const std::wstring& image_name ) :
	m_image( GetModuleHandleW( image_name.c_str() ) )
{

}

void* Factory::Query( const std::string& name, bool custom )
{
	const auto create_interface = reinterpret_cast< void*( * )( const char*, int* ) >( GetProcAddress( m_image, "CreateInterface" ) );

	if( !create_interface )
		return nullptr;

	if( custom )
		return create_interface( name.c_str(), nullptr );

	for( auto i = 0; i <= 200; i++ )
	{
		char interface_data[ 128 ] = { };
		sprintf_s( interface_data, "%s%03i", name.c_str(), i );

		const auto procedure = create_interface( interface_data, nullptr );

		if( procedure )
			return procedure;
	}

	return nullptr;
}

}