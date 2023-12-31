

/** @file  LineSplitter.h
 *  @brief LineSplitter, a helper class to iterate through all lines
 *    of a file easily. Works with StreamReader.
 */
#pragma once
#ifndef INCLUDED_LINE_SPLITTER_H
#define INCLUDED_LINE_SPLITTER_H

#include <stdexcept>
#include "StreamReader.h"
#include "ParsingUtils.h"

namespace Assimp
{

    // ------------------------------------------------------------------------------------------------
    /** Usage:
    @code
    for(LineSplitter splitter(stream);splitter;++splitter) {

        if (*splitter == "hi!") {
           ...
        }
        else if (splitter->substr(0,5) == "hello") {
           ...
           // access the third token in the line (tokens are space-separated)
           if (strtol(splitter[2]) > 5) { .. }
        }

        std::cout << "Current line is: " << splitter.get_index() << std::endl;
    }
    @endcode
    */
    // ------------------------------------------------------------------------------------------------
    class LineSplitter
    {
    public:
        typedef size_t line_idx;

        // -----------------------------------------
        /** construct from existing stream reader
        note: trim is *always* assumed true if skyp_empty_lines==true
        */
        LineSplitter(StreamReaderLE &stream, bool skip_empty_lines = true, bool trim = true);

        ~LineSplitter();

        // -----------------------------------------
        /** pseudo-iterator increment */
        LineSplitter &operator++();

        // -----------------------------------------
        LineSplitter &operator++(int);

        // -----------------------------------------
        /** get a pointer to the beginning of a particular token */
        const char *operator[](size_t idx) const;

        // -----------------------------------------
        /** extract the start positions of N tokens from the current line*/
        template <size_t N>
        void get_tokens(const char *(&tokens)[N]) const;

        // -----------------------------------------
        /** member access */
        const std::string *operator->() const;

        std::string operator*() const;

        // -----------------------------------------
        /** boolean context */
        operator bool() const;

        // -----------------------------------------
        /** line indices are zero-based, empty lines are included */
        operator line_idx() const;

        line_idx get_index() const;

        // -----------------------------------------
        /** access the underlying stream object */
        StreamReaderLE &get_stream();

        // -----------------------------------------
        /** !strcmp((*this)->substr(0,strlen(check)),check) */
        bool match_start(const char *check);

        // -----------------------------------------
        /** swallow the next call to ++, return the previous value. */
        void swallow_next_increment();

        LineSplitter(const LineSplitter &) = delete;
        LineSplitter(LineSplitter &&) = delete;
        LineSplitter &operator=(const LineSplitter &) = delete;

    private:
        line_idx mIdx;
        std::string mCur;
        StreamReaderLE &mStream;
        bool mSwallow, mSkip_empty_lines, mTrim;
    };

    inline LineSplitter::LineSplitter(StreamReaderLE &stream, bool skip_empty_lines, bool trim)
        : mIdx(0), mCur(), mStream(stream), mSwallow(), mSkip_empty_lines(skip_empty_lines), mTrim(trim)
    {
        mCur.reserve(1024);
        operator++();
        mIdx = 0;
    }

    inline LineSplitter::~LineSplitter()
    {
        // empty
    }

    inline LineSplitter &LineSplitter::operator++()
    {
        if (mSwallow)
        {
            mSwallow = false;
            return *this;
        }

        if (!*this)
        {
            throw std::logic_error("End of file, no more lines to be retrieved.");
        }

        char s;
        mCur.clear();
        while (mStream.GetRemainingSize() && (s = mStream.GetI1(), 1))
        {
            if (s == '\n' || s == '\r')
            {
                if (mSkip_empty_lines)
                {
                    while (mStream.GetRemainingSize() && ((s = mStream.GetI1()) == ' ' || s == '\r' || s == '\n'))
                        ;
                    if (mStream.GetRemainingSize())
                    {
                        mStream.IncPtr(-1);
                    }
                }
                else
                {
                    // skip both potential line terminators but don't read past this line.
                    if (mStream.GetRemainingSize() && (s == '\r' && mStream.GetI1() != '\n'))
                    {
                        mStream.IncPtr(-1);
                    }
                    if (mTrim)
                    {
                        while (mStream.GetRemainingSize() && ((s = mStream.GetI1()) == ' ' || s == '\t'))
                            ;
                        if (mStream.GetRemainingSize())
                        {
                            mStream.IncPtr(-1);
                        }
                    }
                }
                break;
            }
            mCur += s;
        }
        ++mIdx;

        return *this;
    }

    inline LineSplitter &LineSplitter::operator++(int)
    {
        return ++(*this);
    }

    inline const char *LineSplitter::operator[](size_t idx) const
    {
        const char *s = operator->()->c_str();

        SkipSpaces(&s);
        for (size_t i = 0; i < idx; ++i)
        {

            for (; !IsSpace(*s); ++s)
            {
                if (IsLineEnd(*s))
                {
                    throw std::range_error("Token index out of range, EOL reached");
                }
            }
            SkipSpaces(&s);
        }
        return s;
    }

    template <size_t N>
    inline void LineSplitter::get_tokens(const char *(&tokens)[N]) const
    {
        const char *s = operator->()->c_str();

        SkipSpaces(&s);
        for (size_t i = 0; i < N; ++i)
        {
            if (IsLineEnd(*s))
            {
                throw std::range_error("Token count out of range, EOL reached");
            }
            tokens[i] = s;

            for (; *s && !IsSpace(*s); ++s)
                ;
            SkipSpaces(&s);
        }
    }

    inline const std::string *LineSplitter::operator->() const
    {
        return &mCur;
    }

    inline std::string LineSplitter::operator*() const
    {
        return mCur;
    }

    inline LineSplitter::operator bool() const
    {
        return mStream.GetRemainingSize() > 0;
    }

    inline LineSplitter::operator line_idx() const
    {
        return mIdx;
    }

    inline LineSplitter::line_idx LineSplitter::get_index() const
    {
        return mIdx;
    }

    inline StreamReaderLE &LineSplitter::get_stream()
    {
        return mStream;
    }

    inline bool LineSplitter::match_start(const char *check)
    {
        const size_t len = ::strlen(check);

        return len <= mCur.length() && std::equal(check, check + len, mCur.begin());
    }

    inline void LineSplitter::swallow_next_increment()
    {
        mSwallow = true;
    }

} // Namespace Assimp

#endif // INCLUDED_LINE_SPLITTER_H
