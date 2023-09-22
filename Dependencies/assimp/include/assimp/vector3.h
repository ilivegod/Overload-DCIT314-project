
/** @file vector3.h
 *  @brief 3D vector structure, including operators when compiling in C++
 */
#pragma once
#ifndef AI_VECTOR3D_H_INC
#define AI_VECTOR3D_H_INC

#ifdef __cplusplus
#include <cmath>
#else
#include <math.h>
#endif

#include "defs.h"

#ifdef __cplusplus

template <typename TReal>
class aiMatrix3x3t;
template <typename TReal>
class aiMatrix4x4t;

// ---------------------------------------------------------------------------
/** Represents a three-dimensional vector. */
template <typename TReal>
class aiVector3t
{
public:
  aiVector3t() AI_NO_EXCEPT : x(), y(), z() {}
  aiVector3t(TReal _x, TReal _y, TReal _z) : x(_x), y(_y), z(_z) {}
  explicit aiVector3t(TReal _xyz) : x(_xyz), y(_xyz), z(_xyz) {}
  aiVector3t(const aiVector3t &o) = default;

public:
  // combined operators
  const aiVector3t &operator+=(const aiVector3t &o);
  const aiVector3t &operator-=(const aiVector3t &o);
  const aiVector3t &operator*=(TReal f);
  const aiVector3t &operator/=(TReal f);

  // transform vector by matrix
  aiVector3t &operator*=(const aiMatrix3x3t<TReal> &mat);
  aiVector3t &operator*=(const aiMatrix4x4t<TReal> &mat);

  // access a single element
  TReal operator[](unsigned int i) const;
  TReal &operator[](unsigned int i);

  // comparison
  bool operator==(const aiVector3t &other) const;
  bool operator!=(const aiVector3t &other) const;
  bool operator<(const aiVector3t &other) const;

  bool Equal(const aiVector3t &other, TReal epsilon = 1e-6) const;

  template <typename TOther>
  operator aiVector3t<TOther>() const;

public:
  /** @brief Set the components of a vector
   *  @param pX X component
   *  @param pY Y component
   *  @param pZ Z component  */
  void Set(TReal pX, TReal pY, TReal pZ);

  /** @brief Get the squared length of the vector
   *  @return Square length */
  TReal SquareLength() const;

  /** @brief Get the length of the vector
   *  @return length */
  TReal Length() const;

  /** @brief Normalize the vector */
  aiVector3t &Normalize();

  /** @brief Normalize the vector with extra check for zero vectors */
  aiVector3t &NormalizeSafe();

  /** @brief Componentwise multiplication of two vectors
   *
   *  Note that vec*vec yields the dot product.
   *  @param o Second factor */
  const aiVector3t SymMul(const aiVector3t &o);

  TReal x, y, z;
};

typedef aiVector3t<ai_real> aiVector3D;

#else

struct aiVector3D
{
  ai_real x, y, z;
};

#endif // __cplusplus

#ifdef __cplusplus

#endif // __cplusplus

#endif // AI_VECTOR3D_H_INC
