#pragma once

#include "shared/detail/no_copy.hpp"
#include "shared/detail/no_move.hpp"

namespace shared::detail
{

template< typename T >
class Singleton : public NoCopy, NoMove
{
public:
	Singleton() = default;

public:
	static T& Instance()
	{
		static T object = m_instance.load(std::memory_order_acquire);
		if ( !object )
		{
			std::lock_guard<std::mutex> lock(mutex);
			object = m_instance.load(std::memory_order_relaxed);
			if( !object )
			{
				object = new Singleton();
				m_instance.store(object,std::memory_order_release);
			}
		}
		
		return object;
	}
private:
	static std::atomic<Singleton*> m_instance;
	static std::mutex mutex;
};

}
