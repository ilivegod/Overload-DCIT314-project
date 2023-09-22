
-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --* /

/** @file ProgressHandler.hpp
 *  @brief Abstract base class 'ProgressHandler'.
 */
#pragma once
#ifndef AI_PROGRESSHANDLER_H_INC
#define AI_PROGRESSHANDLER_H_INC

#include "types.h"

    namespace Assimp
{

    // ------------------------------------------------------------------------------------
    /** @brief CPP-API: Abstract interface for custom progress report receivers.
     *
     *  Each #Importer instance maintains its own #ProgressHandler. The default
     *  implementation provided by Assimp doesn't do anything at all. */
    class ASSIMP_API ProgressHandler
#ifndef SWIG
        : public Intern::AllocateFromAssimpHeap
#endif
    {
    protected:
        /// @brief  Default constructor
        ProgressHandler() AI_NO_EXCEPT
        {
            // empty
        }

    public:
        /// @brief  Virtual destructor.
        virtual ~ProgressHandler()
        {
        }

        // -------------------------------------------------------------------
        /** @brief Progress callback.
         *  @param percentage An estimate of the current loading progress,
         *    in percent. Or -1.f if such an estimate is not available.
         *
         *  There are restriction on what you may do from within your
         *  implementation of this method: no exceptions may be thrown and no
         *  non-const #Importer methods may be called. It is
         *  not generally possible to predict the number of callbacks
         *  fired during a single import.
         *
         *  @return Return false to abort loading at the next possible
         *   occasion (loaders and Assimp are generally allowed to perform
         *   all needed cleanup tasks prior to returning control to the
         *   caller). If the loading is aborted, #Importer::ReadFile()
         *   returns always NULL.
         *   */
        virtual bool Update(float percentage = -1.f) = 0;

        // -------------------------------------------------------------------
        /** @brief Progress callback for file loading steps
         *  @param numberOfSteps The number of total post-processing
         *   steps
         *  @param currentStep The index of the current post-processing
         *   step that will run, or equal to numberOfSteps if all of
         *   them has finished. This number is always strictly monotone
         *   increasing, although not necessarily linearly.
         *
         *  @note This is currently only used at the start and the end
         *   of the file parsing.
         *   */
        virtual void UpdateFileRead(int currentStep /*= 0*/, int numberOfSteps /*= 0*/)
        {
            float f = numberOfSteps ? currentStep / (float)numberOfSteps : 1.0f;
            Update(f * 0.5f);
        }

        // -------------------------------------------------------------------
        /** @brief Progress callback for post-processing steps
         *  @param numberOfSteps The number of total post-processing
         *   steps
         *  @param currentStep The index of the current post-processing
         *   step that will run, or equal to numberOfSteps if all of
         *   them has finished. This number is always strictly monotone
         *   increasing, although not necessarily linearly.
         *   */
        virtual void UpdatePostProcess(int currentStep /*= 0*/, int numberOfSteps /*= 0*/)
        {
            float f = numberOfSteps ? currentStep / (float)numberOfSteps : 1.0f;
            Update(f * 0.5f + 0.5f);
        }

        // -------------------------------------------------------------------
        /** @brief Progress callback for export steps.
         *  @param numberOfSteps The number of total processing
         *   steps
         *  @param currentStep The index of the current post-processing
         *   step that will run, or equal to numberOfSteps if all of
         *   them has finished. This number is always strictly monotone
         *   increasing, although not necessarily linearly.
         *   */
        virtual void UpdateFileWrite(int currentStep /*= 0*/, int numberOfSteps /*= 0*/)
        {
            float f = numberOfSteps ? currentStep / (float)numberOfSteps : 1.0f;
            Update(f * 0.5f);
        }
    }; // !class ProgressHandler

    // ------------------------------------------------------------------------------------

} // Namespace Assimp

#endif // AI_PROGRESSHANDLER_H_INC
