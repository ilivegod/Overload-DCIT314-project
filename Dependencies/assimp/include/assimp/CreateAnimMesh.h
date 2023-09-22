

/** @file CreateAnimMesh.h
 *  Create AnimMesh from Mesh
 */
#ifndef INCLUDED_AI_CREATE_ANIM_MESH_H
#define INCLUDED_AI_CREATE_ANIM_MESH_H

#include <assimp/mesh.h>

namespace Assimp
{

  /** Create aiAnimMesh from aiMesh. */
  ASSIMP_API aiAnimMesh *aiCreateAnimMesh(const aiMesh *mesh);

} // end of namespace Assimp
#endif // INCLUDED_AI_CREATE_ANIM_MESH_H
