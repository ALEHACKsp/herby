#pragma once

#include "shared/auto.hpp"

class Vector2D
{
public:
	Vector2D();
	Vector2D( const float vector_x, const float vector_y );
	Vector2D( const Vector2D& vector );
	Vector2D( const float* vector );

public:
	void Init( const float vector_x = 0.f, const float vector_y = 0.f );
	void Invalidate();

	bool IsValid() const;
	bool IsZero() const;

	float Dot( const Vector2D& vector ) const;
	
	float LengthSqr() const;
	float Length() const;

	float DistToSqr( const Vector2D& vector ) const;
	float DistTo( const Vector2D& vector ) const;

	float Normalize();
	Vector2D Normalized();
	
public:
	float operator[]( const std::size_t index ) const;
	float& operator[]( const std::size_t index );

public:
	Vector2D& operator=( const Vector2D& vector );

public:
	bool operator==( const Vector2D& vector ) const;
	bool operator!=( const Vector2D& vector ) const;

public:
	Vector2D& operator+=( const Vector2D& vector );
	Vector2D& operator-=( const Vector2D& vector );
	Vector2D& operator*=( const Vector2D& vector );
	Vector2D& operator/=( const Vector2D& vector );

public:
	Vector2D& operator+=( const float value );
	Vector2D& operator-=( const float value );
	Vector2D& operator*=( const float value );
	Vector2D& operator/=( const float value );

public:
	Vector2D operator+( const Vector2D& vector ) const;
	Vector2D operator-( const Vector2D& vector ) const;
	Vector2D operator*( const Vector2D& vector ) const;
	Vector2D operator/( const Vector2D& vector ) const;

public:
	Vector2D operator+( const float vector ) const;
	Vector2D operator-( const float vector ) const;
	Vector2D operator*( const float vector ) const;
	Vector2D operator/( const float vector ) const;

public:
	static Vector2D Zero;

public:
	float x = 0.f;
	float y = 0.f;
};
