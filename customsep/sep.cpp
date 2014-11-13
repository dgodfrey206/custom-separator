#include <iostream>
#include <streambuf>

class space_delimited_output_buffer : public std::streambuf
{
public:
    space_delimited_output_buffer(std::streambuf* sbuf)
        : m_sbuf(sbuf)
    { }
 
    virtual int_type overflow(int_type c)
    {
        return m_sbuf->sputc(c);
    }
 
    virtual int sync()
    {
        if (ok_to_write)
            this->sputc(' ');
        else
            ok_to_write = true;
 
        return internal_sync();
    }
private:
    std::streambuf* m_sbuf;
    bool ok_to_write = false;
 
    int internal_sync()
    {
        return m_sbuf->pubsync();
    }
};
 
class space_delimited_output_stream
    : public std::ostream
    , private virtual space_delimited_output_buffer
{
public:
    space_delimited_output_stream(std::ostream& os)
        : space_delimited_output_buffer(os.rdbuf())
        , std::ostream(this)
    {
        this->tie(this); 
    }
};
