#pragma once
#include <streambuf>
#include <fstream>

class CountingStreamBuffer : public std::streambuf
{
public:
    // constructor
    CountingStreamBuffer(std::streambuf* sbuf) :
        streamBuf_(sbuf),
        lineNumber_(1),
        lastLineNumber_(1),
        column_(0),
        prevColumn_(static_cast<unsigned int>(-1)),
        filePos_(0)
    {
    }

    // Get current line number
    unsigned int        lineNumber() const  { return lineNumber_; }

    // Get line number of previously read character
    unsigned int        prevLineNumber() const { return lastLineNumber_; }

    // Get current column
    unsigned int        column() const   { return column_; }

    // Get file position
    std::streamsize     filepos() const { return filePos_; }

protected:
    CountingStreamBuffer(const CountingStreamBuffer&);
    CountingStreamBuffer& operator=(const CountingStreamBuffer&);

    // extract next character from stream w/o advancing read pos
    std::streambuf::int_type underflow()
    {
        return streamBuf_->sgetc();
    }

    // extract next character from stream
    std::streambuf::int_type uflow()
    {
        int_type rc = streamBuf_->sbumpc();

        lastLineNumber_ = lineNumber_;
        if (traits_type::eq_int_type(rc, traits_type::to_int_type('\n')))
        {
            ++lineNumber_;
            prevColumn_ = column_ + 1;
            column_ = static_cast<unsigned int>(-1);
        }

        ++column_;
        ++filePos_;
        return rc;
    }

    // put back last character
    std::streambuf::int_type pbackfail(std::streambuf::int_type c)
    {
        if (traits_type::eq_int_type(c, traits_type::to_int_type('\n')))
        {
            --lineNumber_;
            lastLineNumber_ = lineNumber_;
            column_ = prevColumn_;
            prevColumn_ = 0;
        }

        --column_;
        --filePos_;

        if (c != traits_type::eof())
            return streamBuf_->sputbackc(traits_type::to_char_type(c));
        else
            return streamBuf_->sungetc();
    }

    // change position by offset, according to way and mode
    virtual std::ios::pos_type seekoff(std::ios::off_type pos,
                                  std::ios_base::seekdir dir,
                                  std::ios_base::openmode mode)
    {
        if (dir == std::ios_base::beg
         && pos == static_cast<std::ios::off_type>(0))
        {
            lastLineNumber_ = 1;
            lineNumber_ = 1;
            column_ = 0;
            prevColumn_ = static_cast<unsigned int>(-1);
            filePos_ = 0;

            return streamBuf_->pubseekoff(pos, dir, mode);
        }
        else
            return std::streambuf::seekoff(pos, dir, mode);
    }

    // change to specified position, according to mode
    virtual std::ios::pos_type seekpos(std::ios::pos_type pos,
                                  std::ios_base::openmode mode)
    {
        if (pos == static_cast<std::ios::pos_type>(0))
        {
            lastLineNumber_ = 1;
            lineNumber_ = 1;
            column_ = 0;
            prevColumn_ = static_cast<unsigned int>(-1);
            filePos_ = 0;

            return streamBuf_->pubseekpos(pos, mode);
        }
        else
            return std::streambuf::seekpos(pos, mode);
    }


private:
    std::streambuf*     streamBuf_;     // hosted streambuffer
    unsigned int        lineNumber_;    // current line number
    unsigned int        lastLineNumber_;// line number of last read character
    unsigned int        column_;        // current column
    unsigned int        prevColumn_;    // previous column
    std::streamsize     filePos_;       // file position
};