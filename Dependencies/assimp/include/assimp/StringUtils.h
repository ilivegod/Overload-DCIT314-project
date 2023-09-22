
#ifndef INCLUDED_AI_STRINGUTILS_H
#define INCLUDED_AI_STRINGUTILS_H

#include <assimp/defs.h>

#include <sstream>
#include <stdarg.h>
#include <cstdlib>

///	@fn		ai_snprintf
///	@brief	The portable version of the function snprintf ( C99 standard ), which works on visual studio compilers 2013 and earlier.
///	@param	outBuf		The buffer to write in
///	@param	size		The buffer size
///	@param	format		The format string
///	@param	ap			The additional arguments.
///	@return	The number of written characters if the buffer size was big enough. If an encoding error occurs, a negative number is returned.
#if defined(_MSC_VER) && _MSC_VER < 1900

AI_FORCE_INLINE
int c99_ai_vsnprintf(char *outBuf, size_t size, const char *format, va_list ap)
{
    int count(-1);
    if (0 != size)
    {
        count = _vsnprintf_s(outBuf, size, _TRUNCATE, format, ap);
    }
    if (count == -1)
    {
        count = _vscprintf(format, ap);
    }

    return count;
}

AI_FORCE_INLINE
int ai_snprintf(char *outBuf, size_t size, const char *format, ...)
{
    int count;
    va_list ap;

    va_start(ap, format);
    count = c99_ai_vsnprintf(outBuf, size, format, ap);
    va_end(ap);

    return count;
}

#else
#define ai_snprintf snprintf
#endif

///	@fn		to_string
///	@brief	The portable version of to_string ( some gcc-versions on embedded devices are not supporting this).
///	@param	value   The value to write into the std::string.
///	@return	The value as a std::string
template <typename T>
AI_FORCE_INLINE
    std::string
    to_string(T value)
{
    std::ostringstream os;
    os << value;

    return os.str();
}

///	@fn		ai_strtof
///	@brief	The portable version of strtof.
///	@param	begin   The first character of the string.
/// @param  end     The last character
///	@return	The float value, 0.0f in cas of an error.
AI_FORCE_INLINE
float ai_strtof(const char *begin, const char *end)
{
    if (nullptr == begin)
    {
        return 0.0f;
    }
    float val(0.0f);
    if (nullptr == end)
    {
        val = static_cast<float>(::atof(begin));
    }
    else
    {
        std::string::size_type len(end - begin);
        std::string token(begin, len);
        val = static_cast<float>(::atof(token.c_str()));
    }

    return val;
}

///	@fn		DecimalToHexa
///	@brief	The portable to convert a decimal value into a hexadecimal string.
///	@param	toConvert   Value to convert
///	@return	The hexadecimal string, is empty in case of an error.
template <class T>
AI_FORCE_INLINE
    std::string
    DecimalToHexa(T toConvert)
{
    std::string result;
    std::stringstream ss;
    ss << std::hex << toConvert;
    ss >> result;

    for (size_t i = 0; i < result.size(); ++i)
    {
        result[i] = toupper(result[i]);
    }

    return result;
}

#endif // INCLUDED_AI_STRINGUTILS_H
