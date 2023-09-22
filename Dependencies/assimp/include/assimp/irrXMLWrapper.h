

#ifndef INCLUDED_AI_IRRXML_WRAPPER
#define INCLUDED_AI_IRRXML_WRAPPER

// some long includes ....
#ifdef ASSIMP_USE_HUNTER
#include <irrXML/irrXML.h>
#else
#include <irrXML.h>
#endif
#include "IOStream.hpp"
#include "BaseImporter.h"
#include <vector>

namespace Assimp
{

    // ---------------------------------------------------------------------------------
    /** @brief Utility class to make IrrXML work together with our custom IO system
     *  See the IrrXML docs for more details.
     *
     *  Construct IrrXML-Reader in BaseImporter::InternReadFile():
     *  @code
     * // open the file
     * std::unique_ptr<IOStream> file( pIOHandler->Open( pFile));
     * if( file.get() == NULL) {
     *    throw DeadlyImportError( "Failed to open file " + pFile + ".");
     * }
     *
     * // generate a XML reader for it
     * std::unique_ptr<CIrrXML_IOStreamReader> mIOWrapper( new CIrrXML_IOStreamReader( file.get()));
     * mReader = irr::io::createIrrXMLReader( mIOWrapper.get());
     * if( !mReader) {
     *    ThrowException( "xxxx: Unable to open file.");
     * }
     * @endcode
     **/
    class CIrrXML_IOStreamReader : public irr::io::IFileReadCallBack
    {
    public:
        // ----------------------------------------------------------------------------------
        //! Construction from an existing IOStream
        explicit CIrrXML_IOStreamReader(IOStream *_stream)
            : stream(_stream), t(0)
        {

            // Map the buffer into memory and convert it to UTF8. IrrXML provides its
            // own conversion, which is merely a cast from uintNN_t to uint8_t. Thus,
            // it is not suitable for our purposes and we have to do it BEFORE IrrXML
            // gets the buffer. Sadly, this forces us to map the whole file into
            // memory.

            data.resize(stream->FileSize());
            stream->Read(&data[0], data.size(), 1);

            // Remove null characters from the input sequence otherwise the parsing will utterly fail
            // std::find is usually much faster than manually iterating
            // It is very unlikely that there will be any null characters
            auto null_char_iter = std::find(data.begin(), data.end(), '\0');

            while (null_char_iter != data.end())
            {
                null_char_iter = data.erase(null_char_iter);
                null_char_iter = std::find(null_char_iter, data.end(), '\0');
            }

            BaseImporter::ConvertToUTF8(data);
        }

        // ----------------------------------------------------------------------------------
        //! Virtual destructor
        virtual ~CIrrXML_IOStreamReader() {}

        // ----------------------------------------------------------------------------------
        //!   Reads an amount of bytes from the file.
        /**  @param buffer:       Pointer to output buffer.
         *   @param sizeToRead:   Amount of bytes to read
         *   @return              Returns how much bytes were read.  */
        virtual int read(void *buffer, int sizeToRead)
        {
            if (sizeToRead < 0)
            {
                return 0;
            }
            if (t + sizeToRead > data.size())
            {
                sizeToRead = static_cast<int>(data.size() - t);
            }

            memcpy(buffer, &data.front() + t, sizeToRead);

            t += sizeToRead;
            return sizeToRead;
        }

        // ----------------------------------------------------------------------------------
        //! Returns size of file in bytes
        virtual int getSize()
        {
            return (int)data.size();
        }

    private:
        IOStream *stream;
        std::vector<char> data;
        size_t t;

    }; // ! class CIrrXML_IOStreamReader

} // ! Assimp

#endif // !! INCLUDED_AI_IRRXML_WRAPPER
