

/** @file LogStream.hpp
 *  @brief Abstract base class 'LogStream', representing an output log stream.
 */
#ifndef INCLUDED_AI_LOGSTREAM_H
#define INCLUDED_AI_LOGSTREAM_H

#include "types.h"

namespace Assimp
{

  class IOSystem;

  // ------------------------------------------------------------------------------------
  /** @brief CPP-API: Abstract interface for log stream implementations.
   *
   *  Several default implementations are provided, see #aiDefaultLogStream for more
   *  details. Writing your own implementation of LogStream is just necessary if these
   *  are not enough for your purpose. */
  class ASSIMP_API LogStream
#ifndef SWIG
      : public Intern::AllocateFromAssimpHeap
#endif
  {
  protected:
    /** @brief  Default constructor */
    LogStream() AI_NO_EXCEPT;

  public:
    /** @brief  Virtual destructor  */
    virtual ~LogStream();

    // -------------------------------------------------------------------
    /** @brief  Overwrite this for your own output methods
     *
     *  Log messages *may* consist of multiple lines and you shouldn't
     *  expect a consistent formatting. If you want custom formatting
     *  (e.g. generate HTML), supply a custom instance of Logger to
     *  #DefaultLogger:set(). Usually you can *expect* that a log message
     *  is exactly one line and terminated with a single \n character.
     *  @param message Message to be written */
    virtual void write(const char *message) = 0;

    // -------------------------------------------------------------------
    /** @brief Creates a default log stream
     *  @param streams Type of the default stream
     *  @param name For aiDefaultLogStream_FILE: name of the output file
     *  @param io For aiDefaultLogStream_FILE: IOSystem to be used to open the output
     *   file. Pass NULL for the default implementation.
     *  @return New LogStream instance.  */
    static LogStream *createDefaultStream(aiDefaultLogStream stream,
                                          const char *name = "AssimpLog.txt",
                                          IOSystem *io = nullptr);

  }; // !class LogStream

  inline LogStream::LogStream() AI_NO_EXCEPT
  {
    // empty
  }

  inline LogStream::~LogStream()
  {
    // empty
  }

  // ------------------------------------------------------------------------------------
} // Namespace Assimp

#endif
