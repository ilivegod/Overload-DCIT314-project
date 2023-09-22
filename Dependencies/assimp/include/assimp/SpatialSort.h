

/** Small helper classes to optimise finding vertizes close to a given location */
#ifndef AI_SPATIALSORT_H_INC
#define AI_SPATIALSORT_H_INC

#include <vector>
#include <assimp/types.h>

namespace Assimp
{

    // ------------------------------------------------------------------------------------------------
    /** A little helper class to quickly find all vertices in the epsilon environment of a given
     * position. Construct an instance with an array of positions. The class stores the given positions
     * by their indices and sorts them by their distance to an arbitrary chosen plane.
     * You can then query the instance for all vertices close to a given position in an average O(log n)
     * time, with O(n) worst case complexity when all vertices lay on the plane. The plane is chosen
     * so that it avoids common planes in usual data sets. */
    // ------------------------------------------------------------------------------------------------
    class ASSIMP_API SpatialSort
    {
    public:
        SpatialSort();

        // ------------------------------------------------------------------------------------
        /** Constructs a spatially sorted representation from the given position array.
         * Supply the positions in its layout in memory, the class will only refer to them
         * by index.
         * @param pPositions Pointer to the first position vector of the array.
         * @param pNumPositions Number of vectors to expect in that array.
         * @param pElementOffset Offset in bytes from the beginning of one vector in memory
         *   to the beginning of the next vector. */
        SpatialSort(const aiVector3D *pPositions, unsigned int pNumPositions,
                    unsigned int pElementOffset);

        /** Destructor */
        ~SpatialSort();

    public:
        // ------------------------------------------------------------------------------------
        /** Sets the input data for the SpatialSort. This replaces existing data, if any.
         *  The new data receives new indices in ascending order.
         *
         * @param pPositions Pointer to the first position vector of the array.
         * @param pNumPositions Number of vectors to expect in that array.
         * @param pElementOffset Offset in bytes from the beginning of one vector in memory
         *   to the beginning of the next vector.
         * @param pFinalize Specifies whether the SpatialSort's internal representation
         *   is finalized after the new data has been added. Finalization is
         *   required in order to use #FindPosition() or #GenerateMappingTable().
         *   If you don't finalize yet, you can use #Append() to add data from
         *   other sources.*/
        void Fill(const aiVector3D *pPositions, unsigned int pNumPositions,
                  unsigned int pElementOffset,
                  bool pFinalize = true);

        // ------------------------------------------------------------------------------------
        /** Same as #Fill(), except the method appends to existing data in the #SpatialSort. */
        void Append(const aiVector3D *pPositions, unsigned int pNumPositions,
                    unsigned int pElementOffset,
                    bool pFinalize = true);

        // ------------------------------------------------------------------------------------
        /** Finalize the spatial hash data structure. This can be useful after
         *  multiple calls to #Append() with the pFinalize parameter set to false.
         *  This is finally required before one of #FindPositions() and #GenerateMappingTable()
         *  can be called to query the spatial sort.*/
        void Finalize();

        // ------------------------------------------------------------------------------------
        /** Returns an iterator for all positions close to the given position.
         * @param pPosition The position to look for vertices.
         * @param pRadius Maximal distance from the position a vertex may have to be counted in.
         * @param poResults The container to store the indices of the found positions.
         *   Will be emptied by the call so it may contain anything.
         * @return An iterator to iterate over all vertices in the given area.*/
        void FindPositions(const aiVector3D &pPosition, ai_real pRadius,
                           std::vector<unsigned int> &poResults) const;

        // ------------------------------------------------------------------------------------
        /** Fills an array with indices of all positions identical to the given position. In
         *  opposite to FindPositions(), not an epsilon is used but a (very low) tolerance of
         *  four floating-point units.
         * @param pPosition The position to look for vertices.
         * @param poResults The container to store the indices of the found positions.
         *   Will be emptied by the call so it may contain anything.*/
        void FindIdenticalPositions(const aiVector3D &pPosition,
                                    std::vector<unsigned int> &poResults) const;

        // ------------------------------------------------------------------------------------
        /** Compute a table that maps each vertex ID referring to a spatially close
         *  enough position to the same output ID. Output IDs are assigned in ascending order
         *  from 0...n.
         * @param fill Will be filled with numPositions entries.
         * @param pRadius Maximal distance from the position a vertex may have to
         *   be counted in.
         *  @return Number of unique vertices (n).  */
        unsigned int GenerateMappingTable(std::vector<unsigned int> &fill,
                                          ai_real pRadius) const;

    protected:
        /** Normal of the sorting plane, normalized. The center is always at (0, 0, 0) */
        aiVector3D mPlaneNormal;

        /** An entry in a spatially sorted position array. Consists of a vertex index,
         * its position and its pre-calculated distance from the reference plane */
        struct Entry
        {
            unsigned int mIndex;  ///< The vertex referred by this entry
            aiVector3D mPosition; ///< Position
            ai_real mDistance;    ///< Distance of this vertex to the sorting plane

            Entry() AI_NO_EXCEPT
                : mIndex(999999999),
                  mPosition(),
                  mDistance(99999.)
            {
                // empty
            }
            Entry(unsigned int pIndex, const aiVector3D &pPosition, ai_real pDistance)
                : mIndex(pIndex), mPosition(pPosition), mDistance(pDistance)
            {
                // empty
            }

            bool operator<(const Entry &e) const { return mDistance < e.mDistance; }
        };

        // all positions, sorted by distance to the sorting plane
        std::vector<Entry> mPositions;
    };

} // end of namespace Assimp

#endif // AI_SPATIALSORT_H_INC
