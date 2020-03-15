#include "sdk/math/vector2d.hpp"

// 
// [ Vector2D ] implementation
// 
Vector2D::Vector2D()
	: x( 0.f )
	, y( 0.f )
{ }

Vector2D::Vector2D( const float vector_x, const float vector_y )
	: x( vector_x )
	, y( vector_y )
{ }

Vector2D::Vector2D( const Vector2D& vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
{ }

Vector2D::Vector2D( const float* vector )
	: x( vector[ 0 ] )
	, y( vector[ 1 ] )
{ }

void Vector2D::Init( const float vector_x /*= 0.f*/, const float vector_y /*= 0.f*/ )
{
	x = vector_x;
	y = vector_y;
}

void Vector2D::Invalidate()
{
	x = FLT_MAX;
	y = FLT_MAX;
}

bool Vector2D::IsValid() const
{
	return !( IsZero() );
}

bool Vector2D::IsZero() const
{
	return ( ( x == 0.f ) &&
			 ( y == 0.f ) );
}

float Vector2D::Dot( const Vector2D& vector ) const
{
	return ( ( x * vector[ 0 ] ) +
			 ( y * vector[ 1 ] ) );
}

float Vector2D::LengthSqr() const
{
	const auto vector( *this );
	return Dot( vector );
}

float Vector2D::Length() const
{
	const auto length_squared = LengthSqr();
	return sqrt( length_squared );
}

float Vector2D::DistToSqr( const Vector2D& vector ) const
{
	const auto direction( *this - vector );
	return direction.LengthSqr();
}

float Vector2D::DistTo( const Vector2D& vector ) const
{
	const auto direction( *this - vector );
	return direction.Length();
}

float Vector2D::Normalize()
{
	auto& vector( *this );
	const auto length = Length();

	if( length != 0.f )
		vector /= length;
	else
		vector.Init();

	return length;
}

Vector2D Vector2D::Normalized()
{
	auto& vector( *this );
	const auto length = Length();

	if( length != 0.f )
		vector /= length;
	else
		vector.Init();

	return vector;
}

float Vector2D::operator[]( const std::size_t index ) const
{
	const auto vector( reinterpret_cast< const float* >( this ) );
	return vector[ index ];
}

float& Vector2D::operator[]( const std::size_t index )
{
	auto vector( reinterpret_cast< float* >( this ) );
	return vector[ index ];
}

Vector2D& Vector2D::operator=( const Vector2D& vector )
{
	x = vector[ 0 ];
	y = vector[ 1 ];

	return *this;
}

bool Vector2D::operator==( const Vector2D& vector ) const
{
	return ( ( x == vector[ 0 ] ) &&
			 ( y == vector[ 1 ] ) );
}

bool Vector2D::operator!=( const Vector2D& vector ) const
{
	return ( ( x != vector[ 0 ] ) ||
			 ( y != vector[ 1 ] ) );
}

Vector2D& Vector2D::operator+=( const Vector2D& vector )
{
	x += vector[ 0 ];
	y += vector[ 1 ];

	return *this;
}

Vector2D& Vector2D::operator-=( const Vector2D& vector )
{
	x -= vector[ 0 ];
	y -= vector[ 1 ];

	return *this;
}

Vector2D& Vector2D::operator*=( const Vector2D& vector )
{
	x *= vector[ 0 ];
	y *= vector[ 1 ];

	return *this;
}

Vector2D& Vector2D::operator/=( const Vector2D& vector )
{
	x /= vector[ 0 ];
	y /= vector[ 1 ];

	return *this;
}

Vector2D& Vector2D::operator+=( const float value )
{
	x += value;
	y += value;

	return *this;
}

Vector2D& Vector2D::operator-=( const float value )
{
	x -= value;
	y -= value;

	return *this;
}

Vector2D& Vector2D::operator*=( const float value )
{
	x *= value;
	y *= value;

	return *this;
}

Vector2D& Vector2D::operator/=( const float value )
{
	x /= value;
	y /= value;

	return *this;
}

Vector2D Vector2D::operator+( const Vector2D& vector ) const
{
	return { ( x + vector[ 0 ] ),
			 ( y + vector[ 1 ] ) };
}

Vector2D Vector2D::operator-( const Vector2D& vector ) const
{
	return { ( x - vector[ 0 ] ),
			 ( y - vector[ 1 ] ) };
}

Vector2D Vector2D::operator*( const Vector2D& vector ) const
{
	return { ( x * vector[ 0 ] ),
			 ( y * vector[ 1 ] ) };
}

Vector2D Vector2D::operator/( const Vector2D& vector ) const
{
	return { ( x / vector[ 0 ] ),
			 ( y / vector[ 1 ] ) };
}

Vector2D Vector2D::operator+( const float vector ) const
{
	return { ( x + vector ),
			 ( y + vector ) };
}

Vector2D Vector2D::operator-( const float vector ) const
{
	return { ( x - vector ),
			 ( y - vector ) };
}

Vector2D Vector2D::operator*( const float vector ) const
{
	return { ( x * vector ),
			 ( y * vector ) };
}

Vector2D Vector2D::operator/( const float vector ) const
{
	return { ( x / vector ),
			 ( y / vector ) };
}

Vector2D Vector2D::Zero( 0.f, 0.f );