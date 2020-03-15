#include "sdk/math/vector.hpp"

// 
// [ Vector ] implementation
// 
Vector::Vector()
	: x( 0.f )
	, y( 0.f )
	, z( 0.f )
{ }

Vector::Vector( const float vector_x, const float vector_y, const float vector_z )
	: x( vector_x )
	, y( vector_y )
	, z( vector_z )
{ }

Vector::Vector( const Vector& vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
	, z( vector[ 2 ] )
{ }

Vector::Vector( const float* vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
	, z( vector[ 2 ] )
{ }

void Vector::Init( const float vector_x /*= 0.f*/, const float vector_y /*= 0.f*/, const float vector_z /*= 0.f*/ )
{
	x = vector_x;
	y = vector_y;
	z = vector_z;
}

void Vector::Invalidate()
{
	x = FLT_MAX;
	y = FLT_MAX;
	z = FLT_MAX;
}

bool Vector::IsValid() const
{
	return ( !IsZero() );
}

bool Vector::IsZero() const
{
	return ( ( x == 0.f ) &&
			 ( y == 0.f ) &&
			 ( z == 0.f ) );
}

float Vector::Dot( const Vector& vector ) const
{
	return ( ( x * vector[ 0 ] ) +
			 ( y * vector[ 1 ] ) +
			 ( z * vector[ 2 ] ) );
}

float Vector::Dot2D( const Vector& vector ) const
{
	return ( ( x * vector[ 0 ] ) +
			 ( y * vector[ 1 ] ) );
}

float Vector::LengthSqr() const
{
	const auto vector( *this );
	return Dot( vector );
}

float Vector::Length() const
{
	const auto length_squared = LengthSqr();
	return sqrt( length_squared );
}

float Vector::Length2DSqr() const
{
	const auto vector( *this );
	return Dot2D( vector );
}

float Vector::Length2D() const
{
	const auto length_squared = Length2DSqr();
	return sqrt( length_squared );
}

float Vector::DistToSqr( const Vector& vector ) const
{
	const auto direction( *this - vector );
	return direction.LengthSqr();
}

float Vector::DistTo( const Vector& vector ) const
{
	const auto direction( *this - vector );
	return direction.Length();
}

float Vector::Normalize()
{
	auto& vector( *this );
	const auto length = Length();

	if( length != 0.f )
		vector /= length;
	else
		vector.Init();

	return length;
}

void Vector::NormalizeFast()
{
	auto length = Length();
	auto length_normal = 1.f / length;

	x *= length_normal;
	y *= length_normal;
	z *= length_normal;
}

Vector Vector::Cross( const Vector& vector ) const
{
	return { ( ( y * vector[ 2 ] ) - ( z * vector[ 1 ] ) ),
			 ( ( z * vector[ 0 ] ) - ( x * vector[ 2 ] ) ),
			 ( ( x * vector[ 1 ] ) - ( y * vector[ 0 ] ) ) };
}

Vector4D Vector::ToVector4() const
{
	return { x, y, z, 0.f };
}

float Vector::operator[]( const std::size_t index ) const
{
	const auto vector( reinterpret_cast< const float* >( this ) );
	return vector[ index ];
}

float& Vector::operator[]( const std::size_t index )
{
	auto vector( reinterpret_cast< float* >( this ) );
	return vector[ index ];
}

Vector& Vector::operator=( const Vector& vector )
{
	x = vector[ 0 ];
	y = vector[ 1 ];
	z = vector[ 2 ];

	return *this;
}

bool Vector::operator==( const Vector& vector ) const
{
	return ( ( x == vector[ 0 ] ) &&
			 ( y == vector[ 1 ] ) &&
			 ( z == vector[ 2 ] ) );
}

bool Vector::operator!=( const Vector& vector ) const
{
	return ( ( x != vector[ 0 ] ) ||
			 ( y != vector[ 1 ] ) ||
			 ( z != vector[ 2 ] ) );
}

Vector& Vector::operator+=( const Vector& vector )
{
	x += vector[ 0 ];
	y += vector[ 1 ];
	z += vector[ 2 ];

	return *this;
}

Vector& Vector::operator-=( const Vector& vector )
{
	x -= vector[ 0 ];
	y -= vector[ 1 ];
	z -= vector[ 2 ];

	return *this;
}

Vector& Vector::operator*=( const Vector& vector )
{
	x *= vector[ 0 ];
	y *= vector[ 1 ];
	z *= vector[ 2 ];

	return *this;
}

Vector& Vector::operator/=( const Vector& vector )
{
	x /= vector[ 0 ];
	y /= vector[ 1 ];
	z /= vector[ 2 ];

	return *this;
}

Vector& Vector::operator+=( const float value )
{
	x += value;
	y += value;
	z += value;

	return *this;
}

Vector& Vector::operator-=( const float value )
{
	x -= value;
	y -= value;
	z -= value;

	return *this;
}

Vector& Vector::operator*=( const float value )
{
	x *= value;
	y *= value;
	z *= value;

	return *this;
}

Vector& Vector::operator/=( const float value )
{
	x /= value;
	y /= value;
	z /= value;

	return *this;
}

Vector Vector::operator+( const Vector& vector ) const
{
	return { ( x + vector[ 0 ] ),
			 ( y + vector[ 1 ] ),
			 ( z + vector[ 2 ] ) };
}

Vector Vector::operator-( const Vector& vector ) const
{
	return { ( x - vector[ 0 ] ),
			 ( y - vector[ 1 ] ),
			 ( z - vector[ 2 ] ) };
}

Vector Vector::operator*( const Vector& vector ) const
{
	return { ( x * vector[ 0 ] ),
			 ( y * vector[ 1 ] ),
			 ( z * vector[ 2 ] ) };
}

Vector Vector::operator/( const Vector& vector ) const
{
	return { ( x / vector[ 0 ] ),
			 ( y / vector[ 1 ] ),
			 ( z / vector[ 2 ] ) };
}

Vector Vector::operator+( const float value ) const
{
	return { ( x + value ),
			 ( y + value ),
			 ( z + value ) };
}

Vector Vector::operator-( const float value ) const
{
	return { ( x - value ),
			 ( y - value ),
			 ( z - value ) };
}

Vector Vector::operator*( const float value ) const
{
	return { ( x * value ),
			 ( y * value ),
			 ( z * value ) };
}

Vector Vector::operator/( const float value ) const
{
	return { ( x / value ),
			 ( y / value ),
			 ( z / value ) };
}

Vector Vector::Zero( 0.f, 0.f, 0.f );