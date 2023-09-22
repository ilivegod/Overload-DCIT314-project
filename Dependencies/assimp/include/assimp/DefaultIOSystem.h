

/** @file Default implementation of IOSystem using the standard C file functions */
#ifndef AI_DEFAULTIOSYSTEM_H_INC
#define AI_DEFAULTIOSYSTEM_H_INC

#include <assimp/IOSystem.hpp>

namespace Assimp
{

  // ---------------------------------------------------------------------------
  /** Default implementation of IOSystem using the standard C file functions */
  class ASSIMP_API DefaultIOSystem : public IOSystem
  {
  public:
    // -------------------------------------------------------------------
    /** Tests for the existence of a file at the given path. */
    bool Exists(const char *pFile) const;

    // -------------------------------------------------------------------
    /** Returns the directory separator. */
    char getOsSeparator() const;

    // -------------------------------------------------------------------
    /** Open a new file with a given path. */
    IOStream *Open(const char *pFile, const char *pMode = "rb");

    // -------------------------------------------------------------------
    /** Closes the given file and releases all resources associated with it. */
    void Close(IOStream *pFile);

    // -------------------------------------------------------------------
    /** Compare two paths */
    bool ComparePaths(const char *one, const char *second) const;

    /** @brief get the file name of a full filepath
     * example: /tmp/archive.tar.gz -> archive.tar.gz
     */
    static std::string fileName(const std::string &path);

    /** @brief get the complete base name of a full filepath
     * example: /tmp/archive.tar.gz -> archive.tar
     */
    static std::string completeBaseName(const std::string &path);

    /** @brief get the path of a full filepath
     * example: /tmp/archive.tar.gz -> /tmp/
     */
    static std::string absolutePath(const std::string &path);
  };

} //! ns Assimp

#endif // AI_DEFAULTIOSYSTEM_H_INC
