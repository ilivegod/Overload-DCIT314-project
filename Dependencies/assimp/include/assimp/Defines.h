

// We need those constants, workaround for any platforms where nobody defined them yet
#if (!defined SIZE_MAX)
#define SIZE_MAX (~((size_t)0))
#endif

#if (!defined UINT_MAX)
#define UINT_MAX (~((unsigned int)0))
#endif
