#include "sdk/math/base.hpp"

// 
// [ matrix3x4_t ] implementation
// 
const float* matrix3x4_t::operator[]( const std::size_t index ) const
{
	return m[ index ];
}

float* matrix3x4_t::operator[]( const std::size_t index )
{
	return m[ index ];
}

// 
// [ VMatrix ] implementation
// 
const float* VMatrix::operator[]( const std::size_t index ) const
{
	return m_flMatVal[ index ];
}

float* VMatrix::operator[]( const std::size_t index )
{
	return m_flMatVal[ index ];
}

// 
// [ procedure ] implementation
// 
float ToDegrees( const float radians )
{
	return ( radians * ( g_pi_degrees / g_pi_radians ) );
}

float ToRadians( const float degrees )
{
	return ( degrees * ( g_pi_radians / g_pi_degrees ) );
}

float AngleNormalize( float angle )
{
	angle = std::fmod( angle, 360.f );

	if( angle > 180.f )
		angle -= 360.f;
	else if( angle < -180.f )
		angle += 360.f;

	return angle;
}

void VectorTransform( const Vector& input, const matrix3x4_t& transform, Vector& output )
{
	for( auto i = 0; i < 3; i++ )
		output[ i ] = ( input.Dot( transform[ i ] ) + transform[ i ][ 3 ] );
}

void VectorAngles( const Vector& forward, QAngle& angles )
{
	const auto length2d_squared = forward.Length2DSqr();

	if( length2d_squared == 0.f )
	{
		if( forward[ 2 ] > 0.f )
			angles[ 0 ] = 270.f;
		else
			angles[ 0 ] = 90.f;

		angles[ 1 ] = 0.f;
		angles[ 2 ] = 0.f;
	}
	else
	{
		angles[ 0 ] = ToDegrees( std::atan2( -forward[ 2 ], std::sqrt( length2d_squared ) ) );
		angles[ 1 ] = ToDegrees( std::atan2( forward[ 1 ], forward[ 0 ] ) );
		angles[ 2 ] = 0.f;
	}

	angles.Normalize();
}

void VectorAngles( const Vector& forward, const Vector& pseudoup, QAngle& angles )
{
	auto left = pseudoup.Cross( forward );
	left.Normalize();

	const auto length2d = forward.Length2D();

	if( length2d > 0.001f )
	{
		const auto up_z = ( ( left[ 1 ] * forward[ 0 ] ) - ( left[ 0 ] * forward[ 1 ] ) );

		angles[ 0 ] = ToDegrees( std::atan2( -forward[ 2 ], length2d ) );
		angles[ 1 ] = ToDegrees( std::atan2( forward[ 1 ], forward[ 0 ] ) );
		angles[ 2 ] = ToDegrees( std::atan2( left[ 2 ], up_z ) );
	}
	else
	{
		angles[ 0 ] = ToDegrees( std::atan2( -forward[ 2 ], length2d ) );
		angles[ 1 ] = ToDegrees( std::atan2( -left[ 0 ], left[ 1 ] ) );
		angles[ 2 ] = 0.f;
	}

	angles.Normalize();
}

void AngleVectors( const QAngle& angles, Vector* forward )
{
	const auto radians_x = ToRadians( angles[ 0 ] );
	const auto radians_y = ToRadians( angles[ 1 ] );

	const auto sine_x = std::sin( radians_x );
	const auto sine_y = std::sin( radians_y );

	const auto cosine_x = std::cos( radians_x );
	const auto cosine_y = std::cos( radians_y );

	if( forward )
	{
		forward->x = ( cosine_x * cosine_y );
		forward->y = ( cosine_x * sine_y );
		forward->z = ( -sine_x );
	}
}

void AngleVectors( const QAngle& angles, Vector* forward, Vector* right, Vector* up )
{
	const auto radians_x = ToRadians( angles[ 0 ] );
	const auto radians_y = ToRadians( angles[ 1 ] );
	const auto radians_z = ToRadians( angles[ 2 ] );

	const auto sine_x = std::sin( radians_x );
	const auto sine_y = std::sin( radians_y );
	const auto sine_z = std::sin( radians_z );

	const auto cosine_x = std::cos( radians_x );
	const auto cosine_y = std::cos( radians_y );
	const auto cosine_z = std::cos( radians_z );

	if( forward )
	{
		forward->x = ( cosine_x * cosine_y );
		forward->y = ( cosine_x * sine_y );
		forward->z = ( -sine_x );
	}

	if( right )
	{
		right->x = ( -1.f * sine_z * sine_x * cosine_y + -1.f * cosine_z * -sine_y );
		right->y = ( -1.f * sine_z * sine_x * sine_y + -1.f * cosine_z * cosine_y );
		right->z = ( -1.f * sine_z * cosine_x );
	}

	if( up )
	{
		up->x = ( cosine_z * sine_x * cosine_y + -sine_z * -sine_y );
		up->y = ( cosine_z * sine_x * sine_y + -sine_z * cosine_y );
		up->z = ( cosine_z * cosine_x );
	}
}

void AngleVectorsTranspose( const QAngle& angles, Vector* forward, Vector* right, Vector* up )
{
	const auto radians_x = ToRadians( angles[ 0 ] );
	const auto radians_y = ToRadians( angles[ 1 ] );
	const auto radians_z = ToRadians( angles[ 2 ] );

	const auto sine_x = std::sin( radians_x );
	const auto sine_y = std::sin( radians_y );
	const auto sine_z = std::sin( radians_z );

	const auto cosine_x = std::cos( radians_x );
	const auto cosine_y = std::cos( radians_y );
	const auto cosine_z = std::cos( radians_z );

	if( forward )
	{
		forward->x = ( cosine_x * cosine_y );
		forward->y = ( sine_z * sine_x * cosine_y + cosine_z * -sine_y );
		forward->z = ( cosine_z * sine_x * cosine_y + -sine_z * -sine_y );
	}

	if( right )
	{
		right->x = ( cosine_x * sine_y );
		right->y = ( sine_z * sine_x * sine_y + cosine_z * cosine_y );
		right->z = ( cosine_z * sine_x * sine_y + -sine_z * cosine_y );
	}

	if( up )
	{
		up->x = ( -sine_x );
		up->y = ( sine_z * cosine_x );
		up->z = ( cosine_z * cosine_x );
	}
}