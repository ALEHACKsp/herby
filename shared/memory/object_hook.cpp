#include "shared/memory/object_hook.hpp"

namespace shared::memory
{

ObjectHook::ObjectHook( void* procedure, void* replace )
{
	if( !Create( procedure, replace ) )
	{
		// throw exception
	}
}

ObjectHook::~ObjectHook()
{
	Destroy();
}

bool ObjectHook::Create( void* procedure, void* replace )
{
	m_procedure = reinterpret_cast< std::uint8_t* >( procedure );

	if( !m_procedure )
		return false;

	m_replace = replace;

	if( !m_replace )
		return false;

	m_restore = new std::uint8_t[ 7 ];
	memcpy( m_restore, m_procedure, 7 );

	VirtualProtect( m_procedure, 16, PAGE_EXECUTE_READWRITE, &m_protect );
	Replace();

	return true;
}

void ObjectHook::Destroy()
{
	Restore();
}

void ObjectHook::Replace()
{
	if( !m_procedure )
		return;

	*( std::uint16_t* )( m_procedure ) = 0x50B8;
	*( void** )( m_procedure + 1 ) = m_replace;
	*( std::uint16_t* )( m_procedure + 5 ) = 0xE0FF;
}

void ObjectHook::Restore()
{
	if( !m_procedure )
		return;

	if( !m_restore )
		return;

	memcpy( m_procedure, m_restore, 7 );
}

}