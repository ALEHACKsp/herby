#include "sdk/math/vector4d.hpp"

// 
// [ Vector4D ] implementation
// 
Vector4D::Vector4D()
	: x( 0.f )
	, y( 0.f )
	, z( 0.f )
	, w( 0.f )
{ }

Vector4D::Vector4D( const float vector_x, const float vector_y, const float vector_z, const float vector_w )
	: x( vector_x )
	, y( vector_y )
	, z( vector_z )
	, w( vector_w )
{ }

Vector4D::Vector4D( const Vector4D& vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
	, z( vector[ 2 ] )
	, w( vector[ 3 ] )
{ }

void Vector4D::Init( const float vector_x /*= 0.f*/, const float vector_y /*= 0.f*/, const float vector_z /*= 0.f*/, const float vector_w /*= 0.f*/ )
{
	x = vector_x;
	y = vector_y;
	z = vector_z;
	w = vector_w;
}

void Vector4D::Invalidate()
{
	x = FLT_MAX;
	y = FLT_MAX;
	z = FLT_MAX;
	w = FLT_MAX;
}

bool Vector4D::IsValid() const
{
	return ( !IsZero() );
}

bool Vector4D::IsZero() const
{
	return ( ( x == 0.f ) &&
			 ( y == 0.f ) &&
			 ( z == 0.f ) &&
			 ( w == 0.f ) );
}

float Vector4D::Dot( const Vector4D& vector ) const
{
	return ( ( x * vector[ 0 ] ) +
			 ( y * vector[ 1 ] ) +
			 ( z * vector[ 2 ] ) +
			 ( w * vector[ 3 ] ) );
}

float Vector4D::LengthSqr() const
{
	const auto vector( *this );
	return Dot( vector );
}

float Vector4D::Length() const
{
	const auto length_squared = LengthSqr();
	return sqrt( length_squared );
}

float Vector4D::Normalize()
{
	auto& vector( *this );
	const auto length = Length();

	if( length != 0.f )
		vector /= length;
	else
		vector.Init();

	return length;
}

float Vector4D::operator[]( const std::size_t index ) const
{
	const auto vector( reinterpret_cast< const float* >( this ) );
	return vector[ index ];
}

float& Vector4D::operator[]( const std::size_t index )
{
	auto vector( reinterpret_cast< float* >( this ) );
	return vector[ index ];
}

Vector4D& Vector4D::operator=( const Vector4D& vector )
{
	x = vector[ 0 ];
	y = vector[ 1 ];
	z = vector[ 2 ];
	w = vector[ 3 ];

	return *this;
}

bool Vector4D::operator==( const Vector4D& vector ) const
{
	return ( ( x == vector[ 0 ] ) &&
		( y == vector[ 1 ] ) &&
		( z == vector[ 2 ] ) &&
		( w == vector[ 3 ] ) );
}

bool Vector4D::operator!=( const Vector4D& vector ) const
{
	return ( ( x != vector[ 0 ] ) ||
			 ( y != vector[ 1 ] ) ||
			 ( z != vector[ 2 ] ) ||
			 ( w != vector[ 3 ] ) );
}

Vector4D& Vector4D::operator+=( const Vector4D& vector )
{
	x += vector[ 0 ];
	y += vector[ 1 ];
	z += vector[ 2 ];
	w += vector[ 3 ];

	return *this;
}

Vector4D& Vector4D::operator-=( const Vector4D& vector )
{
	x -= vector[ 0 ];
	y -= vector[ 1 ];
	z -= vector[ 2 ];
	w -= vector[ 3 ];

	return *this;
}

Vector4D& Vector4D::operator*=( const Vector4D& vector )
{
	x *= vector[ 0 ];
	y *= vector[ 1 ];
	z *= vector[ 2 ];
	w *= vector[ 3 ];

	return *this;
}

Vector4D& Vector4D::operator/=( const Vector4D& vector )
{
	x /= vector[ 0 ];
	y /= vector[ 1 ];
	z /= vector[ 2 ];
	w /= vector[ 3 ];

	return *this;
}

Vector4D& Vector4D::operator+=( const float value )
{
	x += value;
	y += value;
	z += value;
	w += value;

	return *this;
}

Vector4D& Vector4D::operator-=( const float value )
{
	x -= value;
	y -= value;
	z -= value;
	w -= value;

	return *this;
}

Vector4D& Vector4D::operator*=( const float value )
{
	x *= value;
	y *= value;
	z *= value;
	w *= value;

	return *this;
}

Vector4D& Vector4D::operator/=( const float value )
{
	x /= value;
	y /= value;
	z /= value;
	w /= value;

	return *this;
}

Vector4D Vector4D::operator+( const Vector4D& vector ) const
{
	return { ( x + vector[ 0 ] ),
			 ( y + vector[ 1 ] ),
			 ( z + vector[ 2 ] ),
			 ( w + vector[ 3 ] ) };
}

Vector4D Vector4D::operator-( const Vector4D& vector ) const
{
	return { ( x - vector[ 0 ] ),
			 ( y - vector[ 1 ] ),
			 ( z - vector[ 2 ] ),
			 ( w - vector[ 3 ] ) };
}

Vector4D Vector4D::operator*( const Vector4D& vector ) const
{
	return { ( x * vector[ 0 ] ),
			 ( y * vector[ 1 ] ),
			 ( z * vector[ 2 ] ),
			 ( w * vector[ 3 ] ) };
}

Vector4D Vector4D::operator/( const Vector4D& vector ) const
{
	return { ( x / vector[ 0 ] ),
			 ( y / vector[ 1 ] ),
			 ( z / vector[ 2 ] ),
			 ( w / vector[ 3 ] ) };
}

Vector4D Vector4D::Zero( 0.f, 0.f, 0.f, 0.f );