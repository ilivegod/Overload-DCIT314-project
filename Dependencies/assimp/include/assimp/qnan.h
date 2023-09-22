

/**  @file  qnan.h
 *   @brief Some utilities for our dealings with qnans.
 *
 *   @note Some loaders use qnans to mark invalid values tempoarily, also
 *     Assimp explicitly enforces undefined normals to be set to qnan.
 *     qnan utilities are available in standard libraries (C99 for example)
 *     but last time I checked compiler coverage was so bad that I decided
 *     to reinvent the wheel.
 */

#ifndef AI_QNAN_H_INCLUDED
#define AI_QNAN_H_INCLUDED

#include <assimp/defs.h>
#include <limits>
#include <stdint.h>

// ---------------------------------------------------------------------------
/** Data structure to represent the bit pattern of a 32 Bit
 *         IEEE 754 floating-point number. */
union _IEEESingle
{
    float Float;
    struct
    {
        uint32_t Frac : 23;
        uint32_t Exp : 8;
        uint32_t Sign : 1;
    } IEEE;
};

// ---------------------------------------------------------------------------
/** Data structure to represent the bit pattern of a 64 Bit
 *         IEEE 754 floating-point number. */
union _IEEEDouble
{
    double Double;
    struct
    {
        uint64_t Frac : 52;
        uint64_t Exp : 11;
        uint64_t Sign : 1;
    } IEEE;
};

// ---------------------------------------------------------------------------
/** Check whether a given float is qNaN.
 *  @param in Input value */
AI_FORCE_INLINE bool is_qnan(float in)
{
    // the straightforward solution does not work:
    //   return (in != in);
    // compiler generates code like this
    //   load <in> to <register-with-different-width>
    //   compare <register-with-different-width> against <in>

    // FIXME: Use <float> stuff instead? I think fpclassify needs C99
    _IEEESingle temp;
    memcpy(&temp, &in, sizeof(float));
    return (temp.IEEE.Exp == (1u << 8) - 1 &&
            temp.IEEE.Frac);
}

// ---------------------------------------------------------------------------
/** Check whether a given double is qNaN.
 *  @param in Input value */
AI_FORCE_INLINE bool is_qnan(double in)
{
    // the straightforward solution does not work:
    //   return (in != in);
    // compiler generates code like this
    //   load <in> to <register-with-different-width>
    //   compare <register-with-different-width> against <in>

    // FIXME: Use <float> stuff instead? I think fpclassify needs C99
    _IEEEDouble temp;
    memcpy(&temp, &in, sizeof(in));
    return (temp.IEEE.Exp == (1u << 11) - 1 &&
            temp.IEEE.Frac);
}

// ---------------------------------------------------------------------------
/** @brief check whether a float is either NaN or (+/-) INF.
 *
 *  Denorms return false, they're treated like normal values.
 *  @param in Input value */
AI_FORCE_INLINE bool is_special_float(float in)
{
    _IEEESingle temp;
    memcpy(&temp, &in, sizeof(float));
    return (temp.IEEE.Exp == (1u << 8) - 1);
}

// ---------------------------------------------------------------------------
/** @brief check whether a double is either NaN or (+/-) INF.
 *
 *  Denorms return false, they're treated like normal values.
 *  @param in Input value */
AI_FORCE_INLINE bool is_special_float(double in)
{
    _IEEESingle temp;
    memcpy(&temp, &in, sizeof(float));
    return (temp.IEEE.Exp == (1u << 11) - 1);
}

// ---------------------------------------------------------------------------
/** Check whether a float is NOT qNaN.
 *  @param in Input value */
template <class TReal>
AI_FORCE_INLINE bool is_not_qnan(TReal in)
{
    return !is_qnan(in);
}

// ---------------------------------------------------------------------------
/** @brief Get a fresh qnan.  */
AI_FORCE_INLINE ai_real get_qnan()
{
    return std::numeric_limits<ai_real>::quiet_NaN();
}

#endif // !! AI_QNAN_H_INCLUDED
