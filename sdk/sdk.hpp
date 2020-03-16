#pragma once

#include "sdk/math/base.hpp"

//
// functions
//

VMatrix WorldToScreenMatrix();
bool WorldToScreen( const Vector& world, Vector2D& screen );

//
// typedefs
//

using InstantiateInterfaceFn = void* ( * )( );
using RecvVarProxyFn = void( * )( const void*, void*, void* );
using ArrayLengthRecvProxyFn = void( * )( void*, int, int );
using DataTableRecvVarProxyFn = void( * )( const void*, void**, void*, int );
using CreateClientClassFn = void* ( * )( int, int );
using CreateEventFn = void* ( * )( );

using VectorAligned = Vector4D;

//
// structs
//

struct model_t;
struct player_info_t;

class RecvProp;
class RecvTable;
class ClientClass;

class CGlobalVarsBase;

class IBaseClientDLL;
class IClientEntityList;
class IVEngineClient;

struct player_info_t
{
	PAD( 0x0008 );

	union
	{
		__int64 steamID64;

		struct
		{
			__int32 xuid_low;
			__int32 xuid_high;
		};
	};

	char name[ 128 ] = { };
	int userID = 0;
	char guid[ 20 ] = { };
	PAD( 0x0010 );
	std::uint32_t friendsID = 0;
	char friendsName[ 128 ] = { };
	bool fakeplayer = false;
	bool ishltv = false;
	std::uint32_t customFiles[ 4 ] = { };
	std::uint8_t filesDownloaded = { };
};

class RecvProp
{
public:
	const char* m_pVarName = nullptr;
	unsigned m_RecvType = { };
	int m_Flags = 0;
	int m_StringBufferSize = 0;
	bool m_bInsideArray = false;
	const void* m_pExtraData = nullptr;
	RecvProp* m_pArrayProp = nullptr;
	ArrayLengthRecvProxyFn m_ArrayLengthProxy = nullptr;
	RecvVarProxyFn m_ProxyFn = nullptr;
	DataTableRecvVarProxyFn m_DataTableProxyFn = nullptr;
	RecvTable* m_pDataTable = nullptr;
	int m_Offset = 0;
	int m_ElementStride = 0;
	int m_nElements = 0;
	const char* m_pParentArrayPropName = nullptr;
};

class RecvTable
{
public:
	RecvProp* m_pProps = nullptr;
	int m_nProps = 0;
	void* m_pDecoder = nullptr;
	const char* m_pNetTableName = nullptr;
	bool m_bInitialized = false;
	bool m_bInMainList = false;
};

class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn = nullptr;
	CreateEventFn m_pCreateEventFn = nullptr;
	char* m_pNetworkName = nullptr;
	RecvTable* m_pRecvTable = nullptr;
	ClientClass* m_pNext = nullptr;
	int m_ClassID = 0;
};

class CGlobalVarsBase
{
public:
	float realtime = 0.f;
	int framecount = 0;
	float absoluteframetime = 0.f;
	float absoluteframestarttimestddev = 0.f;
	float curtime = 0.f;
	float frametime = 0.f;
	int maxClients = 0;
	int tickcount = 0;
	float interval_per_tick = 0.f;
	float interpolation_amount = 0.f;
	int simTicksThisFrame = 0;
	int network_protocol = 0;
	void* pSaveData = nullptr;
	bool m_bClient = false;
	int nTimestampNetworkingBase = 0;
	int nTimestampRandomizeWindow = 0;
};

//
// interfaces
//

class IBaseClientDLL
{
public:
	ClientClass* GetAllClasses()
	{
		return memory::Call< 8, ClientClass* >( this );
	}
};

class IClientEntityList
{
public:
	void* GetClientEntity( int index )
	{
		return memory::Call< 3, void* >( this, index );
	}

	void* GetClientEntityFromHandle( unsigned long hEnt )
	{
		return memory::Call< 4, void* >( this, hEnt );
	}

	int GetHighestEntityIndex()
	{
		return memory::Call< 6, int >( this );
	}
};

class IVEngineClient
{
public:
	void GetScreenSize( int& width, int& height )
	{
		return memory::Call< 5, void >( this, std::ref( width ), std::ref( height ) );
	}

	bool GetPlayerInfo( int ent_num, player_info_t* pinfo )
	{
		return memory::Call< 8, bool >( this, ent_num, pinfo );
	}

	int GetPlayerForUserID( int userID )
	{
		return memory::Call< 9, int >( this, userID );
	}

	int GetLocalPlayer()
	{
		return memory::Call< 12, int >( this );
	}

	void GetViewAngles( QAngle& va )
	{
		return memory::Call< 18, void >( this, std::ref( va ) );
	}

	void SetViewAngles( QAngle& va )
	{
		return memory::Call< 19, void >( this, std::ref( va ) );
	}

	int GetMaxClients()
	{
		return memory::Call< 20, int >( this );
	}
};

//
// other structs
//

#include "shared/imgui/imgui.hpp"

struct render_line_data_t
{
public:
	render_line_data_t() = default;

public:
	render_line_data_t( const ImVec2& begin, const ImVec2& end, const ImColor& color, float width = 1.f )
	{
		m_begin = begin;
		m_end = end;
		m_color = color;
		m_width = width;
	};

public:
	ImVec2 m_begin = { };
	ImVec2 m_end = { };
	ImColor m_color = { };
	float m_width = 0.f;
};

struct render_rect_data_t
{
public:
	render_rect_data_t() = default;

public:
	render_rect_data_t( const ImVec2& begin, const ImVec2& size, const ImColor& color, bool rected = true )
	{
		m_begin = begin;
		m_size = size;
		m_color = color;
		m_rected = rected;
	};

public:
	ImVec2 m_begin = { };
	ImVec2 m_size = { };
	ImColor m_color = { };
	bool m_rected = false;
};

struct render_text_data_t
{
public:
	render_text_data_t() = default;

public:
	render_text_data_t( const ImVec2& begin, const std::uint32_t layout, const ImColor& color, const char* message )
	{
		m_begin = begin;
		m_layout = layout;
		m_color = color;
		m_message = message;
	};

public:
	ImVec2 m_begin = { };
	std::uint32_t m_layout = 0;
	ImColor m_color = { };
	std::string m_message = { };
};

extern std::vector< render_text_data_t > m_renderer_text_array;
extern std::vector< render_line_data_t > m_renderer_line_array;
extern std::vector< render_rect_data_t > m_renderer_rect_array;