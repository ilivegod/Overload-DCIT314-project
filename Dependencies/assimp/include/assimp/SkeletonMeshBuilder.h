

/** @file SkeletonMeshBuilder.h
 *  Declares SkeletonMeshBuilder, a tiny utility to build dummy meshes
 *  for animation skeletons.
 */

#ifndef AI_SKELETONMESHBUILDER_H_INC
#define AI_SKELETONMESHBUILDER_H_INC

#include <vector>
#include <assimp/mesh.h>

struct aiMaterial;
struct aiScene;
struct aiNode;

namespace Assimp
{

    // ---------------------------------------------------------------------------
    /**
     * This little helper class constructs a dummy mesh for a given scene
     * the resembles the node hierarchy. This is useful for file formats
     * that don't carry any mesh data but only animation data.
     */
    class ASSIMP_API SkeletonMeshBuilder
    {
    public:
        // -------------------------------------------------------------------
        /** The constructor processes the given scene and adds a mesh there.
         *
         * Does nothing if the scene already has mesh data.
         * @param pScene The scene for which a skeleton mesh should be constructed.
         * @param root The node to start with. NULL is the scene root
         * @param bKnobsOnly Set this to true if you don't want the connectors
         *   between the knobs representing the nodes.
         */
        SkeletonMeshBuilder(aiScene *pScene, aiNode *root = NULL,
                            bool bKnobsOnly = false);

    protected:
        // -------------------------------------------------------------------
        /** Recursively builds a simple mesh representation for the given node
         * and also creates a joint for the node that affects this part of
         * the mesh.
         * @param pNode The node to build geometry for.
         */
        void CreateGeometry(const aiNode *pNode);

        // -------------------------------------------------------------------
        /** Creates the mesh from the internally accumulated stuff and returns it.
         */
        aiMesh *CreateMesh();

        // -------------------------------------------------------------------
        /** Creates a dummy material and returns it. */
        aiMaterial *CreateMaterial();

    protected:
        /** space to assemble the mesh data: points */
        std::vector<aiVector3D> mVertices;

        /** faces */
        struct Face
        {
            unsigned int mIndices[3];
            Face();
            Face(unsigned int p0, unsigned int p1, unsigned int p2)
            {
                mIndices[0] = p0;
                mIndices[1] = p1;
                mIndices[2] = p2;
            }
        };
        std::vector<Face> mFaces;

        /** bones */
        std::vector<aiBone *> mBones;

        bool mKnobsOnly;
    };

} // end of namespace Assimp

#endif // AI_SKELETONMESHBUILDER_H_INC
