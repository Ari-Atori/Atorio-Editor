#ifndef ATORIO_PACKET
#define ATORIO_PACKET

#include <stdint.h>
#include <cstring>
#include "math/Vector.hpp"
#include "math/Matrix.hpp"
#include "io/JSON_W.hpp"

/* Here is the core object for communication between
 * the main editor, and the filter libraries. The data
 * the packets share are actually agreed before-hand
 * when the editor reads the dll and the json configuration
 * files associated with each filter. The types cooincide with
 * Shader.hpp to insure smooth unifrom loading from ouptuts
 */

#define PACKET_PACKET 0
#define PACKET_FLOAT 1
#define PACKET_VEC2 2
#define PACKET_VEC3 3
#define PACKET_VEC4 4
#define PACKET_MAT4 5
#define PACKET_INT32 6
#define PACKET_INT64 7
#define PACKET_VOID  8
#define PACKET_STRING 9

struct Packet {
	char name[32];
	uint32_t type;
	uint32_t count;
	union {
		float f;
		vec2 v2; vec3 v3; vec4 v4; mat4 m4;
		int32_t i32; int64_t i64;
		void* v;
	} value;

	Packet& operator[](const char* name);
	static Packet* json(JSON json);
	static Packet* copy(Packet*);
	static void clean(Packet*);
};

#endif
