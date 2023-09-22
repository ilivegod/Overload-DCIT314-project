

/** @file Profiler.h
 *  @brief Utility to measure the respective runtime of each import step
 */
#ifndef INCLUDED_PROFILER_H
#define INCLUDED_PROFILER_H

#include <chrono>
#include <assimp/DefaultLogger.hpp>
#include "TinyFormatter.h"

#include <map>

namespace Assimp
{
    namespace Profiling
    {

        using namespace Formatter;

        // ------------------------------------------------------------------------------------------------
        /** Simple wrapper around boost::timer to simplify reporting. Timings are automatically
         *  dumped to the log file.
         */
        class Profiler
        {
        public:
            Profiler()
            {
                // empty
            }

        public:
            /** Start a named timer */
            void BeginRegion(const std::string &region)
            {
                regions[region] = std::chrono::system_clock::now();
                ASSIMP_LOG_DEBUG((format("START `"), region, "`"));
            }

            /** End a specific named timer and write its end time to the log */
            void EndRegion(const std::string &region)
            {
                RegionMap::const_iterator it = regions.find(region);
                if (it == regions.end())
                {
                    return;
                }

                std::chrono::duration<double> elapsedSeconds = std::chrono::system_clock::now() - regions[region];
                ASSIMP_LOG_DEBUG((format("END   `"), region, "`, dt= ", elapsedSeconds.count(), " s"));
            }

        private:
            typedef std::map<std::string, std::chrono::time_point<std::chrono::system_clock>> RegionMap;
            RegionMap regions;
        };

    }
}

#endif
