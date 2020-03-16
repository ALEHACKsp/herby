#pragma once

#define CONCATENATE_DETAIL( left, right ) left ## right
#define CONCATENATE( left, right ) CONCATENATE_DETAIL( left, right )

#define PAD( size ) \
	private: \
		char CONCATENATE( __pad, __COUNTER__ )[ size ] = { }; \
	public: