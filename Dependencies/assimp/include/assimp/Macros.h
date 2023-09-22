

/* Helper macro to set a pointer to NULL in debug builds
 */
#if (defined ASSIMP_BUILD_DEBUG)
#define AI_DEBUG_INVALIDATE_PTR(x) x = NULL;
#else
#define AI_DEBUG_INVALIDATE_PTR(x)
#endif
