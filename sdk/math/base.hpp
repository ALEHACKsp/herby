#pragma once

#include "shared/auto.hpp"

#include "sdk/math/qangle.hpp"
#include "sdk/math/vector.hpp"
#include "sdk/math/vector2d.hpp"
#include "sdk/math/vector4d.hpp"

constexpr auto g_pi_radians = static_cast< float >( 3.14159265358979323846 );
constexpr auto g_pi_degrees = static_cast< float >( 180.0 );

struct matrix3x4_t;

class VMatrix;

class QAngle;
class Vector;
class Vector2D;
class Vector4D;

struct matrix3x4_t
{
public:
	const float* operator[]( const std::size_t index ) const;
	float* operator[]( const std::size_t index );

public:
	float m[ 3 ][ 4 ] = { };
};

class VMatrix
{
public:
	const float* operator[]( const std::size_t index ) const;
	float* operator[]( const std::size_t index );

public:
	float m_flMatVal[ 4 ][ 4 ] = { };
};

// 
// [ procedure ]
// 
float ToDegrees( const float radians );
float ToRadians( const float degrees );

float AngleNormalize( float angle );

void VectorTransform( const Vector& input, const matrix3x4_t& transform, Vector& output );

void VectorAngles( const Vector& forward, QAngle& angles );
void VectorAngles( const Vector& forward, const Vector& pseudoup, QAngle& angles );

void AngleVectors( const QAngle& angles, Vector* forward );
void AngleVectors( const QAngle& angles, Vector* forward, Vector* right, Vector* up );
void AngleVectorsTranspose( const QAngle& angles, Vector* forward, Vector* right, Vector* up );