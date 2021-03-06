// Copyright (C) 2009-2018, Panagiotis Christopoulos Charitos and contributors.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#pragma once

#include <anki/scene/SceneNode.h>
#include <anki/collision/Frustum.h>
#include <anki/collision/Sphere.h>
#include <anki/Gr.h>

namespace anki
{

/// @addtogroup scene
/// @{

/// Probe used in realtime reflections.
class ReflectionProbeNode : public SceneNode
{
	friend class ReflectionProbeMoveFeedbackComponent;

public:
	const F32 FRUSTUM_NEAR_PLANE = 0.1f / 4.0f;
	const F32 EFFECTIVE_DISTANCE = 256.0f;

	ReflectionProbeNode(SceneGraph* scene, CString name)
		: SceneNode(scene, name)
	{
	}

	~ReflectionProbeNode();

	ANKI_USE_RESULT Error init(F32 radius);

	U getCubemapArrayIndex() const
	{
		ANKI_ASSERT(m_cubemapArrayIdx < 0xFF);
		return m_cubemapArrayIdx;
	}

	void setCubemapArrayIndex(U cubemapArrayIdx)
	{
		ANKI_ASSERT(cubemapArrayIdx < 0xFF);
		m_cubemapArrayIdx = cubemapArrayIdx;
	}

	ANKI_USE_RESULT Error frameUpdate(Second prevUpdateTime, Second crntTime) override;

private:
	class CubeSide
	{
	public:
		PerspectiveFrustum m_frustum;
		Transform m_localTrf;
	};

	Array<CubeSide, 6> m_cubeSides;
	Sphere m_spatialSphere;
	U8 m_cubemapArrayIdx = 0xFF; ///< Used by the renderer

	void onMoveUpdate(MoveComponent& move);
};
/// @}

} // end namespace anki
