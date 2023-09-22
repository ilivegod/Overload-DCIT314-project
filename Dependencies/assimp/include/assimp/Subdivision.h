

/** @file Defines a helper class to evaluate subdivision surfaces.*/
#pragma once
#ifndef AI_SUBDISIVION_H_INC
#define AI_SUBDISIVION_H_INC

#include <cstddef>
#include <assimp/types.h>

struct aiMesh;

namespace Assimp
{

  // ------------------------------------------------------------------------------
  /** Helper class to evaluate subdivision surfaces. Different algorithms
   *  are provided for choice. */
  // ------------------------------------------------------------------------------
  class ASSIMP_API Subdivider
  {
  public:
    /** Enumerates all supported subvidision algorithms */
    enum Algorithm
    {
      CATMULL_CLARKE = 0x1
    };

    virtual ~Subdivider();

    // ---------------------------------------------------------------
    /** Create a subdivider of a specific type
     *
     *  @param algo Algorithm to be used for subdivision
     *  @return Subdivider instance. */
    static Subdivider *Create(Algorithm algo);

    // ---------------------------------------------------------------
    /** Subdivide a mesh using the selected algorithm
     *
     *  @param mesh First mesh to be subdivided. Must be in verbose
     *    format.
     *  @param out Receives the output mesh, allocated by me.
     *  @param num Number of subdivisions to perform.
     *  @param discard_input If true is passed, the input mesh is
     *    deleted after the subdivision is complete. This can
     *    improve performance because it allows the optimization
     *    to reuse the existing mesh for intermediate results.
     *  @pre out!=mesh*/
    virtual void Subdivide(aiMesh *mesh,
                           aiMesh *&out, unsigned int num,
                           bool discard_input = false) = 0;

    // ---------------------------------------------------------------
    /** Subdivide multiple meshes using the selected algorithm. This
     *  avoids erroneous smoothing on objects consisting of multiple
     *  per-material meshes. Usually, most 3d modellers smooth on a
     *  per-object base, regardless the materials assigned to the
     *  meshes.
     *
     *  @param smesh Array of meshes to be subdivided. Must be in
     *    verbose format.
     *  @param nmesh Number of meshes in smesh.
     *  @param out Receives the output meshes. The array must be
     *    sufficiently large (at least @c nmesh elements) and may not
     *    overlap the input array. Output meshes map one-to-one to
     *    their corresponding input meshes. The meshes are allocated
     *    by the function.
     *  @param discard_input If true is passed, input meshes are
     *    deleted after the subdivision is complete. This can
     *    improve performance because it allows the optimization
     *    of reusing existing meshes for intermediate results.
     *  @param num Number of subdivisions to perform.
     *  @pre nmesh != 0, smesh and out may not overlap*/
    virtual void Subdivide(
        aiMesh **smesh,
        size_t nmesh,
        aiMesh **out,
        unsigned int num,
        bool discard_input = false) = 0;
  };

  inline Subdivider::~Subdivider()
  {
    // empty
  }

} // end namespace Assimp

#endif // !!  AI_SUBDISIVION_H_INC
