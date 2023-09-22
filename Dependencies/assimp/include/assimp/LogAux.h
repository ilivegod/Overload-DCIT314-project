

/** @file  LogAux.h
 *  @brief Common logging usage patterns for importer implementations
 */
#ifndef INCLUDED_AI_LOGAUX_H
#define INCLUDED_AI_LOGAUX_H

#include <assimp/TinyFormatter.h>
#include <assimp/Exceptional.h>
#include <assimp/DefaultLogger.hpp>

namespace Assimp
{

    template <class TDeriving>
    class LogFunctions
    {
    public:
        // ------------------------------------------------------------------------------------------------
        static void ThrowException(const std::string &msg)
        {
            throw DeadlyImportError(Prefix() + msg);
        }

        // ------------------------------------------------------------------------------------------------
        static void LogWarn(const Formatter::format &message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                ASSIMP_LOG_WARN(Prefix() + (std::string)message);
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogError(const Formatter::format &message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                ASSIMP_LOG_ERROR(Prefix() + (std::string)message);
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogInfo(const Formatter::format &message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                ASSIMP_LOG_INFO(Prefix() + (std::string)message);
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogDebug(const Formatter::format &message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                ASSIMP_LOG_DEBUG(Prefix() + (std::string)message);
            }
        }

        // https://sourceforge.net/tracker/?func=detail&atid=1067632&aid=3358562&group_id=226462
#if !defined(__GNUC__) || !defined(__APPLE__) || __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)

        // ------------------------------------------------------------------------------------------------
        static void LogWarn(const char *message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                LogWarn(Formatter::format(message));
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogError(const char *message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                LogError(Formatter::format(message));
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogInfo(const char *message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                LogInfo(Formatter::format(message));
            }
        }

        // ------------------------------------------------------------------------------------------------
        static void LogDebug(const char *message)
        {
            if (!DefaultLogger::isNullLogger())
            {
                LogDebug(Formatter::format(message));
            }
        }

#endif

    private:
        static const char *Prefix();
    };
} // ! Assimp

#endif
