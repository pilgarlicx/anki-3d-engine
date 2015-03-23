// Copyright (C) 2009-2015, Panagiotis Christopoulos Charitos.
// All rights reserved.
// Code licensed under the BSD License.
// http://www.anki3d.org/LICENSE

#ifndef ANKI_SCENE_SECTOR_H
#define ANKI_SCENE_SECTOR_H

#include "anki/scene/Common.h"
#include "anki/scene/Visibility.h"
#include "anki/Collision.h"

namespace anki {

// Forward
class SceneNode;
class Sector;
class SectorGroup;

/// @addtogroup Scene
/// @{

/// 2 way Portal
class Portal
{
public:
	Portal(SectorGroup* sectorGroup)
	:	m_group(sectorGroup)
	{}

	~Portal();

	ANKI_USE_RESULT Error create(const SArray<Vec4>& vertPositions);

	const CollisionShape& getCollisionShape() const
	{
		return *m_shape;
	}

	ANKI_USE_RESULT Error addSector(Sector* sector);

private:
	SectorGroup* m_group;
	List<Sector*> m_sectors;
	CollisionShape* m_shape = nullptr;
	DArray<Vec4> m_shapeStorage;
	Bool8 m_open = true;
};

/// A sector. It consists of an octree and some portals
class Sector
{
	friend class SectorGroup;

public:
	/// Used to reserve some space on the portals vector to save memory
	static const U AVERAGE_PORTALS_PER_SECTOR = 4;

	/// Default constructor
	Sector(SectorGroup* group)
	:	m_group(group)
	{}

	~Sector();

	ANKI_USE_RESULT Error create(const SArray<Vec4>& vertPositions);

	const CollisionShape& getCollisionShape() const
	{
		return *m_shape;
	}

	ANKI_USE_RESULT Error addPortal(Portal* portal);

	ANKI_USE_RESULT Error addSceneNode(SceneNode* node);
	void removeSceneNode(SceneNode* node);

private:
	SectorGroup* m_group; ///< Know your father
	CollisionShape* m_shape;
	DArray<Vec4> m_shapeStorage;

	List<Portal*> m_portals;
	List<SceneNode*> m_nodes;

	List<SceneNode*>::Iterator findSceneNode(SceneNode* node);
};

/// Sector group. This is supposed to represent the whole scene
class SectorGroup
{
public:
	/// Default constructor
	SectorGroup(SceneGraph* scene)
	:	m_scene(scene)
	{}

	/// Destructor
	~SectorGroup();

	SceneAllocator<U8> getAllocator() const;

	/// The owner of the pointer is the sector group
	Sector* createNewSector(const SArray<Vec4>& vertexPositions);

	/// The owner of the pointer is the sector group
	Portal* createNewPortal(const SArray<Vec4>& vertexPositions);

	ANKI_USE_RESULT Error bake();

	/// @privatesection
	/// @{
	ConvexHullShape* createConvexHull(const SArray<Vec4>& vertPositions,
		DArray<Vec4>& shapeStorage);
	/// @}

private:
	SceneGraph* m_scene; ///< Keep it here to access various allocators
	List<Sector*> m_sectors;
	List<Portal*> m_portals;
};
/// @}

} // end namespace anki

#endif
