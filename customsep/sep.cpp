#include <iostream>
#include <streambuf>

class string_delimited_output_buffer : public std::streambuf
{
public:
    string_delimited_output_buffer(std::streambuf* sbuf, const std::string& delim)
        : m_sbuf(sbuf)
        , delim(delim)
    { }
 
    virtual int_type overflow(int_type c)
    {
        return m_sbuf->sputc(c);
    }
 
    virtual int sync()
    {
        if (ok_to_write)
            this->sputn(delim.data(), delim.size());
        else
            ok_to_write = true;
 
        return internal_sync();
    }
private:
    std::streambuf* m_sbuf;
    std::string delim;
    bool ok_to_write = false;
 
    int internal_sync()
    {
        return m_sbuf->pubsync();
    }
};
 
class string_delimited_output_stream
    : public std::ostream
    , private virtual string_delimited_output_buffer
{
public:
    string_delimited_output_stream(std::ostream& os, const std::string& delim = " ")
        : string_delimited_output_buffer(os.rdbuf(), delim)
        , std::ostream(this)
    {
        this->tie(this); 
    }
};

/*
int main()
{
    string_delimited_output_stream str(std::cout, ", ");
    str << "Hello" << "World"; // Prints "Hello, World"
}
*/
