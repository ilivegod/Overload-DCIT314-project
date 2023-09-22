

#ifndef INCLUDED_ASSIMP_XML_TOOLS_H
#define INCLUDED_ASSIMP_XML_TOOLS_H

#include <string>

namespace Assimp
{
    // XML escape the 5 XML special characters (",',<,> and &) in |data|
    // Based on http://stackoverflow.com/questions/5665231
    std::string XMLEscape(const std::string &data)
    {
        std::string buffer;

        const size_t size = data.size();
        buffer.reserve(size + size / 8);
        for (size_t i = 0; i < size; ++i)
        {
            const char c = data[i];
            switch (c)
            {
            case '&':
                buffer.append("&amp;");
                break;
            case '\"':
                buffer.append("&quot;");
                break;
            case '\'':
                buffer.append("&apos;");
                break;
            case '<':
                buffer.append("&lt;");
                break;
            case '>':
                buffer.append("&gt;");
                break;
            default:
                buffer.append(&c, 1);
                break;
            }
        }
        return buffer;
    }
}

#endif // INCLUDED_ASSIMP_XML_TOOLS_H
