#pragma once

#include "shared/auto.hpp"

#include "sdk/math/vector.hpp"

class QAngle
{
public:
	QAngle();
	QAngle( const float angles_x, const float angles_y, const float angles_z );
	QAngle( const QAngle& angles );

public:
	void Init( const float angles_x = 0.f, const float angles_y = 0.f, const float angles_z = 0.f );
	void Invalidate();

	bool IsValid() const;
	bool IsZero() const;

	float Dot( const QAngle& angles ) const;

	float LengthSqr() const;
	float Length() const;

	QAngle& Normalize();
	QAngle Normalized() const;

	QAngle& Clamp();
	QAngle Clamped() const;

	Vector ToVector( Vector* side = nullptr, Vector* up = nullptr ) const;

public:
	float operator[]( const std::size_t index ) const;
	float& operator[]( const std::size_t index );

public:
	QAngle& operator=( const QAngle& angles );

public:
	bool operator==( const QAngle& angles ) const;
	bool operator!=( const QAngle& angles ) const;

public:
	QAngle& operator+=( const QAngle& angles );
	QAngle& operator-=( const QAngle& angles );
	QAngle& operator*=( const QAngle& angles );
	QAngle& operator/=( const QAngle& angles );

public:
	QAngle& operator+=( const float value );
	QAngle& operator-=( const float value );
	QAngle& operator*=( const float value );
	QAngle& operator/=( const float value );

public:
	QAngle operator+( const QAngle& angles ) const;
	QAngle operator-( const QAngle& angles ) const;
	QAngle operator*( const QAngle& angles ) const;
	QAngle operator/( const QAngle& angles ) const;

public:
	QAngle operator+( const float value ) const;
	QAngle operator-( const float value ) const;
	QAngle operator*( const float value ) const;
	QAngle operator/( const float value ) const;

public:
	static QAngle Zero;

public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};
