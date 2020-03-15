#pragma once

#include "horizon/auto.hpp"

namespace csgo::engine
{

class Factory : public detail::Singleton< Factory >
{
public:
	Factory( const std::wstring& image_name );

private:
	void* Query( const std::string& name, bool custom );

public:
	template< typename T >
	T Get( const std::string& name, bool custom = false )
	{
		const auto query_interface = Query( name, custom );
		return ( T )( query_interface );
	}

private:
	HMODULE m_image = nullptr;
};

}