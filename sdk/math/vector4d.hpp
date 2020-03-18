#pragma once

#include "shared/auto.hpp"

class Vector4D
{
public:
	Vector4D();
	Vector4D( const float vector_x, const float vector_y, const float vector_z, const float vector_w );
	Vector4D( const Vector4D& vector );

public:
	void Init( const float vector_x = 0.f, const float vector_y = 0.f, const float vector_z = 0.f, const float vector_w = 0.f );
	void Invalidate();

	bool IsValid() const;
	bool IsZero() const;

	float Dot( const Vector4D& vector ) const;

	float LengthSqr() const;
	float Length() const;

	float Normalize();

public:
	float operator[]( const std::size_t index ) const;
	float& operator[]( const std::size_t index );

public:
	Vector4D& operator=( const Vector4D& vector );

public:
	bool operator==( const Vector4D& vector ) const;
	bool operator!=( const Vector4D& vector ) const;

public:
	Vector4D& operator+=( const Vector4D& vector );
	Vector4D& operator-=( const Vector4D& vector );
	Vector4D& operator*=( const Vector4D& vector );
	Vector4D& operator/=( const Vector4D& vector );

public:
	Vector4D& operator+=( const float value );
	Vector4D& operator-=( const float value );
	Vector4D& operator*=( const float value );
	Vector4D& operator/=( const float value );

public:
	Vector4D operator+( const Vector4D& vector ) const;
	Vector4D operator-( const Vector4D& vector ) const;
	Vector4D operator*( const Vector4D& vector ) const;
	Vector4D operator/( const Vector4D& vector ) const;

public:
	static Vector4D Zero;

public:
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float w = 0.f;
};
