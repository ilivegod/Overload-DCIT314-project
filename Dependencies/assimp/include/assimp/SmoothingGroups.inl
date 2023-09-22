

/** @file Generation of normal vectors basing on smoothing groups */

#ifndef AI_SMOOTHINGGROUPS_INL_INCLUDED
#define AI_SMOOTHINGGROUPS_INL_INCLUDED

// internal headers
#include <assimp/SGSpatialSort.h>

// CRT header
#include <algorithm>

using namespace Assimp;

// ------------------------------------------------------------------------------------------------
template <class T>
void ComputeNormalsWithSmoothingsGroups(MeshWithSmoothingGroups<T> &sMesh)
{
    // First generate face normals
    sMesh.mNormals.resize(sMesh.mPositions.size(), aiVector3D());
    for (unsigned int a = 0; a < sMesh.mFaces.size(); a++)
    {
        T &face = sMesh.mFaces[a];

        aiVector3D *pV1 = &sMesh.mPositions[face.mIndices[0]];
        aiVector3D *pV2 = &sMesh.mPositions[face.mIndices[1]];
        aiVector3D *pV3 = &sMesh.mPositions[face.mIndices[2]];

        aiVector3D pDelta1 = *pV2 - *pV1;
        aiVector3D pDelta2 = *pV3 - *pV1;
        aiVector3D vNor = pDelta1 ^ pDelta2;

        for (unsigned int c = 0; c < 3; ++c)
            sMesh.mNormals[face.mIndices[c]] = vNor;
    }

    // calculate the position bounds so we have a reliable epsilon to check position differences against
    aiVector3D minVec(1e10f, 1e10f, 1e10f), maxVec(-1e10f, -1e10f, -1e10f);
    for (unsigned int a = 0; a < sMesh.mPositions.size(); a++)
    {
        minVec.x = std::min(minVec.x, sMesh.mPositions[a].x);
        minVec.y = std::min(minVec.y, sMesh.mPositions[a].y);
        minVec.z = std::min(minVec.z, sMesh.mPositions[a].z);
        maxVec.x = std::max(maxVec.x, sMesh.mPositions[a].x);
        maxVec.y = std::max(maxVec.y, sMesh.mPositions[a].y);
        maxVec.z = std::max(maxVec.z, sMesh.mPositions[a].z);
    }
    const float posEpsilon = (maxVec - minVec).Length() * 1e-5f;
    std::vector<aiVector3D> avNormals;
    avNormals.resize(sMesh.mNormals.size());

    // now generate the spatial sort tree
    SGSpatialSort sSort;
    for (typename std::vector<T>::iterator i = sMesh.mFaces.begin();
         i != sMesh.mFaces.end(); ++i)
    {
        for (unsigned int c = 0; c < 3; ++c)
            sSort.Add(sMesh.mPositions[(*i).mIndices[c]], (*i).mIndices[c], (*i).iSmoothGroup);
    }
    sSort.Prepare();

    std::vector<bool> vertexDone(sMesh.mPositions.size(), false);
    for (typename std::vector<T>::iterator i = sMesh.mFaces.begin();
         i != sMesh.mFaces.end(); ++i)
    {
        std::vector<unsigned int> poResult;
        for (unsigned int c = 0; c < 3; ++c)
        {
            unsigned int idx = (*i).mIndices[c];
            if (vertexDone[idx])
                continue;

            sSort.FindPositions(sMesh.mPositions[idx], (*i).iSmoothGroup,
                                posEpsilon, poResult);

            aiVector3D vNormals;
            for (std::vector<unsigned int>::const_iterator
                     a = poResult.begin();
                 a != poResult.end(); ++a)
            {
                vNormals += sMesh.mNormals[(*a)];
            }
            vNormals.NormalizeSafe();

            // write back into all affected normals
            for (std::vector<unsigned int>::const_iterator
                     a = poResult.begin();
                 a != poResult.end(); ++a)
            {
                idx = *a;
                avNormals[idx] = vNormals;
                vertexDone[idx] = true;
            }
        }
    }
    sMesh.mNormals = avNormals;
}

#endif // !! AI_SMOOTHINGGROUPS_INL_INCLUDED
