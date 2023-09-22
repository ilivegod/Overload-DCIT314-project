

/** @file  NullLogger.hpp
 *  @brief Dummy logger
 */

#ifndef INCLUDED_AI_NULLLOGGER_H
#define INCLUDED_AI_NULLLOGGER_H

#include "Logger.hpp"

namespace Assimp
{

    // ---------------------------------------------------------------------------
    /** @brief CPP-API: Empty logging implementation.
     *
     * Does nothing! Used by default if the application hasn't requested a
     * custom logger via #DefaultLogger::set() or #DefaultLogger::create(); */
    class ASSIMP_API NullLogger
        : public Logger
    {

    public:
        /** @brief  Logs a debug message */
        void OnDebug(const char *message)
        {
            (void)message; // this avoids compiler warnings
        }

        /** @brief  Logs an info message */
        void OnInfo(const char *message)
        {
            (void)message; // this avoids compiler warnings
        }

        /** @brief  Logs a warning message */
        void OnWarn(const char *message)
        {
            (void)message; // this avoids compiler warnings
        }

        /** @brief  Logs an error message */
        void OnError(const char *message)
        {
            (void)message; // this avoids compiler warnings
        }

        /** @brief  Detach a still attached stream from logger */
        bool attachStream(LogStream *pStream, unsigned int severity)
        {
            (void)pStream;
            (void)severity; // this avoids compiler warnings
            return false;
        }

        /** @brief  Detach a still attached stream from logger */
        bool detatchStream(LogStream *pStream, unsigned int severity)
        {
            (void)pStream;
            (void)severity; // this avoids compiler warnings
            return false;
        }

    private:
    };
}
#endif // !! AI_NULLLOGGER_H_INCLUDED
