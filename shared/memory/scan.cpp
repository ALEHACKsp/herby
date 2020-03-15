#include "shared/memory/scan.hpp"

#define IN_RANGE( value, min, max ) ( value >= min && value <= max )

#define GET_BITS( value ) ( IN_RANGE( value, '0', '9' ) ? ( value - '0' ) : ( ( value & ~0x0020 ) - 'A' + 0x000A ) )
#define GET_BYTE( value ) ( ( GET_BITS( value[ 0 ] ) << 4 ) | ( GET_BITS( value[ 1 ] ) ) )

namespace shared::memory
{

std::uintptr_t ScanLocation( const std::uintptr_t location,
	const std::size_t size,
	const std::string& signature,
	const std::intptr_t displacement /*= 0*/,
	const std::size_t read /*= 0*/ )
{
	auto scan_result = ( std::uintptr_t )( 0 );
	auto scan_data = const_cast< char* >( signature.data() );

	const auto scan_start = static_cast< std::uintptr_t >( location );
	const auto scan_end = static_cast< std::uintptr_t >( location + size );

	for( auto scan_current = scan_start; scan_current < scan_end; scan_current++ )
	{
		if( !scan_data[ 0 ] )
			break;

		if( scan_data[ 0 ] == '\?' || ( *( std::uint8_t* )( scan_current ) == GET_BYTE( scan_data ) ) )
		{
			if( !scan_result )
				scan_result = scan_current;

			if( !scan_data[ 2 ] )
				break;

			scan_data += ( ( scan_data[ 0 ] == '\?' ) ? 2 : 3 );
		}
		else
		{
			scan_data = const_cast< char* >( signature.data() );
			scan_result = 0;
		}
	}

	if( scan_result )
	{
		scan_result += displacement;

		if( read )
		{
			for( auto i = 0; i < read; i++ )
			{
				scan_result = *( std::uintptr_t* )( scan_result );

				if( !scan_result )
					break;
			}
		}
	}

	return scan_result;
}

std::uintptr_t ScanImage( const std::wstring& image_name,
	const std::string& signature,
	const std::intptr_t displacement /*= 0*/,
	const std::size_t read /*= 0*/ )
{
	const auto image = reinterpret_cast< std::uintptr_t >( GetModuleHandleW( !( image_name.empty() ) ? image_name.c_str() : nullptr ) );

	if( !image )
		return 0;

	const auto dos_header = reinterpret_cast< IMAGE_DOS_HEADER* >( image );

	if( !dos_header )
		return 0;

	if( dos_header->e_magic != IMAGE_DOS_SIGNATURE )
		return 0;

	const auto nt_headers = reinterpret_cast< IMAGE_NT_HEADERS* >( image + dos_header->e_lfanew );

	if( !nt_headers )
		return 0;

	if( nt_headers->Signature != IMAGE_NT_SIGNATURE )
		return 0;

	const auto image_size = static_cast< std::size_t >( nt_headers->OptionalHeader.SizeOfImage );

	if( !image_size )
		return 0;

	return ScanLocation( image, image_size, signature, displacement, read );
}

}