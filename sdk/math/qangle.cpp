#include "sdk/math/qangle.hpp"

#include "sdk/math/base.hpp"

// 
// [ QAngle ] implementation
// 
QAngle::QAngle()
	: x( 0.f )
	, y( 0.f )
	, z( 0.f )
{ }

QAngle::QAngle( const float angles_x, const float angles_y, const float angles_z )
	: x( angles_x )
	, y( angles_y )
	, z( angles_z )
{ }

QAngle::QAngle( const QAngle& angles )
	: x( angles[ 0 ] )
	, y( angles[ 1 ] )
	, z( angles[ 2 ] )
{ }

void QAngle::Init( const float angles_x /*= 0.f*/, const float angles_y /*= 0.f*/, const float angles_z /*= 0.f*/ )
{
	x = angles_x;
	y = angles_y;
	z = angles_z;
}

void QAngle::Invalidate()
{
	x = FLT_MAX; 
	y = FLT_MAX; 
	z = FLT_MAX;
}

bool QAngle::IsValid() const
{
	return ( !IsZero() );
}

bool QAngle::IsZero() const
{
	return ( ( x == 0.f ) &&
		( y == 0.f ) &&
		( z == 0.f ) );
}

float QAngle::Dot( const QAngle& angles ) const
{
	return ( ( x * angles[ 0 ] ) +
		( y * angles[ 1 ] ) +
		( z * angles[ 2 ] ) );
}

float QAngle::LengthSqr() const
{
	const auto angles( *this );
	return Dot( angles );
}

float QAngle::Length() const
{
	const auto length_squared = LengthSqr();
	return std::sqrt( length_squared );
}

QAngle& QAngle::Normalize()
{
	x = AngleNormalize( x );
	y = AngleNormalize( y );
	z = 0.f; // AngleNormalize( z );

	return *this;
}

QAngle QAngle::Normalized() const
{
	auto angles( *this );
	return angles.Normalize();
}

QAngle& QAngle::Clamp()
{
	x = std::clamp( x, -89.f, 89.f );
	y = std::clamp( y, -180.f, 180.f );
	z = std::clamp( z, -50.f, 50.f );

	return *this;
}

QAngle QAngle::Clamped() const
{
	auto angles( *this );
	return angles.Clamp();
}

Vector QAngle::ToVector( Vector* side /*= nullptr*/, Vector* up /*= nullptr*/ ) const
{
	auto rad_pitch = ToRadians( x );
	auto rad_yaw = ToRadians( y );
	auto rad_roll = ToRadians( z );

	auto sin_pitch = std::sin( rad_pitch );
	auto sin_yaw = std::sin( rad_yaw );
	auto sin_roll = std::sin( rad_roll );

	auto cos_pitch = std::cos( rad_pitch );
	auto cos_yaw = std::cos( rad_yaw );
	auto cos_roll = std::cos( rad_roll );

	if( side )
	{
		side->x = -1.0f * sin_roll * sin_pitch * cos_yaw + -1.0f * cos_roll * -sin_yaw;
		side->y = -1.0f * sin_roll * sin_pitch * sin_yaw + -1.0f * cos_roll * cos_yaw;
		side->z = -1.0f * sin_roll * cos_pitch;
	}

	if( up )
	{
		up->x = cos_roll * sin_pitch * cos_yaw + -sin_roll * -sin_yaw;
		up->y = cos_roll * sin_pitch * sin_yaw + -sin_roll * cos_yaw;
		up->z = cos_roll * cos_pitch;
	}

	return { cos_pitch * cos_yaw, cos_pitch * sin_yaw, -sin_pitch };
}

float QAngle::operator[]( const std::size_t index ) const
{
	const auto angles( reinterpret_cast< const float* >( this ) );
	return angles[ index ];
}

float& QAngle::operator[]( const std::size_t index )
{
	auto angles( reinterpret_cast< float* >( this ) );
	return angles[ index ];
}

QAngle& QAngle::operator=( const QAngle& angles )
{
	x = angles[ 0 ];
	y = angles[ 1 ];
	z = angles[ 2 ];

	return *this;
}

bool QAngle::operator==( const QAngle& angles ) const
{
	return ( ( x == angles[ 0 ] ) &&
		( y == angles[ 1 ] ) &&
		( z == angles[ 2 ] ) );
}

bool QAngle::operator!=( const QAngle& angles ) const
{
	return ( ( x != angles[ 0 ] ) ||
		( y != angles[ 1 ] ) ||
		( z != angles[ 2 ] ) );
}

QAngle& QAngle::operator+=( const QAngle& angles )
{
	x += angles[ 0 ];
	y += angles[ 1 ];
	z += angles[ 2 ];

	return *this;
}

QAngle& QAngle::operator-=( const QAngle& angles )
{
	x -= angles[ 0 ];
	y -= angles[ 1 ];
	z -= angles[ 2 ];

	return *this;
}

QAngle& QAngle::operator*=( const QAngle& angles )
{
	x *= angles[ 0 ];
	y *= angles[ 1 ];
	z *= angles[ 2 ];

	return *this;
}

QAngle& QAngle::operator/=( const QAngle& angles )
{
	x /= angles[ 0 ];
	y /= angles[ 1 ];
	z /= angles[ 2 ];

	return *this;
}

QAngle& QAngle::operator+=( const float value )
{
	x += value;
	y += value;
	z += value;

	return *this;
}

QAngle& QAngle::operator-=( const float value )
{
	x -= value;
	y -= value;
	z -= value;

	return *this;
}

QAngle& QAngle::operator*=( const float value )
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

QAngle& QAngle::operator/=( const float value )
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

QAngle QAngle::operator+( const QAngle& angles ) const
{
	return { ( x + angles[ 0 ] ),
			 ( y + angles[ 1 ] ),
			 ( z + angles[ 2 ] ) };
}

QAngle QAngle::operator-( const QAngle& angles ) const
{
	return { ( x - angles[ 0 ] ),
			 ( y - angles[ 1 ] ),
			 ( z - angles[ 2 ] ) };
}

QAngle QAngle::operator*( const QAngle& angles ) const
{
	return { ( x * angles[ 0 ] ),
			 ( y * angles[ 1 ] ),
			 ( z * angles[ 2 ] ) };
}

QAngle QAngle::operator/( const QAngle& angles ) const
{
	return { ( x / angles[ 0 ] ),
			 ( y / angles[ 1 ] ),
			 ( z / angles[ 2 ] ) };
}

QAngle QAngle::operator+( const float value ) const
{
	return { ( x + value ),
			 ( y + value ),
			 ( z + value ) };
}

QAngle QAngle::operator-( const float value ) const
{
	return { ( x - value ),
			 ( y - value ),
			 ( z - value ) };
}

QAngle QAngle::operator*( const float value ) const
{
	return { ( x * value ),
			 ( y * value ),
			 ( z * value ) };
}

QAngle QAngle::operator/( const float value ) const
{
	return { ( x / value ),
			 ( y / value ),
			 ( z / value ) };
}

QAngle QAngle::Zero( 0.f, 0.f, 0.f );