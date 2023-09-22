

/** @file Declares a helper class, "StandardShapes" which generates
 *  vertices for standard shapes, such as cylnders, cones, spheres ..
 */
#ifndef AI_STANDARD_SHAPES_H_INC
#define AI_STANDARD_SHAPES_H_INC

#include <assimp/vector3.h>
#include <vector>

struct aiMesh;

namespace Assimp
{

    // ---------------------------------------------------------------------------
    /** \brief Helper class to generate vertex buffers for standard geometric
     *  shapes, such as cylinders, cones, boxes, spheres, elipsoids ... .
     */
    class ASSIMP_API StandardShapes
    {
        // class cannot be instanced
        StandardShapes() {}

    public:
        // ----------------------------------------------------------------
        /** Generates a mesh from an array of vertex positions.
         *
         *  @param positions List of vertex positions
         *  @param numIndices Number of indices per primitive
         *  @return Output mesh
         */
        static aiMesh *MakeMesh(const std::vector<aiVector3D> &positions,
                                unsigned int numIndices);

        static aiMesh *MakeMesh(unsigned int (*GenerateFunc)(std::vector<aiVector3D> &));

        static aiMesh *MakeMesh(unsigned int (*GenerateFunc)(std::vector<aiVector3D> &, bool));

        static aiMesh *MakeMesh(unsigned int n, void (*GenerateFunc)(unsigned int, std::vector<aiVector3D> &));

        // ----------------------------------------------------------------
        /** @brief Generates a hexahedron (cube)
         *
         *  Hexahedrons can be scaled on all axes.
         *  @param positions Receives output triangles.
         *  @param polygons If you pass true here quads will be returned
         *  @return Number of vertices per face
         */
        static unsigned int MakeHexahedron(
            std::vector<aiVector3D> &positions,
            bool polygons = false);

        // ----------------------------------------------------------------
        /** @brief Generates an icosahedron
         *
         *  @param positions Receives output triangles.
         *  @return Number of vertices per face
         */
        static unsigned int MakeIcosahedron(
            std::vector<aiVector3D> &positions);

        // ----------------------------------------------------------------
        /** @brief Generates a dodecahedron
         *
         *  @param positions Receives output triangles
         *  @param polygons If you pass true here pentagons will be returned
         *  @return Number of vertices per face
         */
        static unsigned int MakeDodecahedron(
            std::vector<aiVector3D> &positions,
            bool polygons = false);

        // ----------------------------------------------------------------
        /** @brief Generates an octahedron
         *
         *  @param positions Receives output triangles.
         *  @return Number of vertices per face
         */
        static unsigned int MakeOctahedron(
            std::vector<aiVector3D> &positions);

        // ----------------------------------------------------------------
        /** @brief Generates a tetrahedron
         *
         *  @param positions Receives output triangles.
         *  @return Number of vertices per face
         */
        static unsigned int MakeTetrahedron(
            std::vector<aiVector3D> &positions);

        // ----------------------------------------------------------------
        /** @brief Generates a sphere
         *
         *  @param tess Number of subdivions - 0 generates a octahedron
         *  @param positions Receives output triangles.
         */
        static void MakeSphere(unsigned int tess,
                               std::vector<aiVector3D> &positions);

        // ----------------------------------------------------------------
        /** @brief Generates a cone or a cylinder, either open or closed.
         *
         *  @code
         *
         *       |-----|       <- radius 1
         *
         *        __x__        <- ]               ^
         *       /     \          | height        |
         *      /       \         |               Y
         *     /         \        |
         *    /           \       |
         *   /______x______\   <- ] <- end cap
         *
         *   |-------------|   <- radius 2
         *
         *  @endcode
         *
         *  @param height Height of the cone
         *  @param radius1 First radius
         *  @param radius2 Second radius
         *  @param tess Number of triangles.
         *  @param bOpened true for an open cone/cylinder. An open shape has
         *    no 'end caps'
         *  @param positions Receives output triangles
         */
        static void MakeCone(ai_real height, ai_real radius1,
                             ai_real radius2, unsigned int tess,
                             std::vector<aiVector3D> &positions, bool bOpen = false);

        // ----------------------------------------------------------------
        /** @brief Generates a flat circle
         *
         *  The circle is constructed in the planned formed by the x,z
         *  axes of the cartesian coordinate system.
         *
         *  @param radius Radius of the circle
         *  @param tess Number of segments.
         *  @param positions Receives output triangles.
         */
        static void MakeCircle(ai_real radius, unsigned int tess,
                               std::vector<aiVector3D> &positions);
    };
} // ! Assimp

#endif // !! AI_STANDARD_SHAPES_H_INC
