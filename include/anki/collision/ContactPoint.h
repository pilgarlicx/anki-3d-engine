#ifndef ANKI_COLLISION_CONTACT_POINT_H
#define ANKI_COLLISION_CONTACT_POINT_H

#include "anki/Math.h"

namespace anki {

/// @addtogroup collision
/// @{

/// Collision test contact point
class ContactPoint
{
public:
	Vec3 m_position;
	Vec3 m_normal;
	F32 m_depth;
};

/// @}

} // end namespace anki

#endif
