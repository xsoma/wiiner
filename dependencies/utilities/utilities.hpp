#pragma once
#include <cstdint>
#include "../../source-sdk/math/vector3d.hpp"

#define sig_cam_think "85 C0 75 30 38 86"

namespace utilities {
	template< typename t >
	__forceinline static t call_virtual( void *name, int offset ) {
		int *table = *( int ** ) name;
		int address = table[ offset ];
		return ( t ) ( address );
	}

	std::uint8_t* pattern_scan(const char* module_name, const char* signature) noexcept;
}
