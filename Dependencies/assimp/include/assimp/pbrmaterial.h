

/** @file pbrmaterial.h
 *  @brief Defines the material system of the library
 */
#ifndef AI_PBRMATERIAL_H_INC
#define AI_PBRMATERIAL_H_INC

#define AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_FACTOR "$mat.gltf.pbrMetallicRoughness.baseColorFactor", 0, 0
#define AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR "$mat.gltf.pbrMetallicRoughness.metallicFactor", 0, 0
#define AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_ROUGHNESS_FACTOR "$mat.gltf.pbrMetallicRoughness.roughnessFactor", 0, 0
#define AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_BASE_COLOR_TEXTURE aiTextureType_DIFFUSE, 1
#define AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE aiTextureType_UNKNOWN, 0
#define AI_MATKEY_GLTF_ALPHAMODE "$mat.gltf.alphaMode", 0, 0
#define AI_MATKEY_GLTF_ALPHACUTOFF "$mat.gltf.alphaCutoff", 0, 0
#define AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS "$mat.gltf.pbrSpecularGlossiness", 0, 0
#define AI_MATKEY_GLTF_PBRSPECULARGLOSSINESS_GLOSSINESS_FACTOR "$mat.gltf.pbrMetallicRoughness.glossinessFactor", 0, 0
#define AI_MATKEY_GLTF_UNLIT "$mat.gltf.unlit", 0, 0

#define _AI_MATKEY_GLTF_TEXTURE_TEXCOORD_BASE "$tex.file.texCoord"
#define _AI_MATKEY_GLTF_MAPPINGNAME_BASE "$tex.mappingname"
#define _AI_MATKEY_GLTF_MAPPINGID_BASE "$tex.mappingid"
#define _AI_MATKEY_GLTF_MAPPINGFILTER_MAG_BASE "$tex.mappingfiltermag"
#define _AI_MATKEY_GLTF_MAPPINGFILTER_MIN_BASE "$tex.mappingfiltermin"
#define _AI_MATKEY_GLTF_SCALE_BASE "$tex.scale"
#define _AI_MATKEY_GLTF_STRENGTH_BASE "$tex.strength"

#define AI_MATKEY_GLTF_TEXTURE_TEXCOORD(type, N) _AI_MATKEY_GLTF_TEXTURE_TEXCOORD_BASE, type, N
#define AI_MATKEY_GLTF_MAPPINGNAME(type, N) _AI_MATKEY_GLTF_MAPPINGNAME_BASE, type, N
#define AI_MATKEY_GLTF_MAPPINGID(type, N) _AI_MATKEY_GLTF_MAPPINGID_BASE, type, N
#define AI_MATKEY_GLTF_MAPPINGFILTER_MAG(type, N) _AI_MATKEY_GLTF_MAPPINGFILTER_MAG_BASE, type, N
#define AI_MATKEY_GLTF_MAPPINGFILTER_MIN(type, N) _AI_MATKEY_GLTF_MAPPINGFILTER_MIN_BASE, type, N
#define AI_MATKEY_GLTF_TEXTURE_SCALE(type, N) _AI_MATKEY_GLTF_SCALE_BASE, type, N
#define AI_MATKEY_GLTF_TEXTURE_STRENGTH(type, N) _AI_MATKEY_GLTF_STRENGTH_BASE, type, N

#endif //!!AI_PBRMATERIAL_H_INC
