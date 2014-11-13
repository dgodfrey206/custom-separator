custom-separator
================

A program that allows an arbitrary separator between sequences of output data. When writing to an output stream the text is bundled together unless there is a separator (like whitespace) between them. It's very unintuitive to do, for example:

    std::cout << a <<  " " << b << " " << c;
    
just to get the output `1 2 3`. Instead, this stream uses a custom `std::streambuf` that writes the separator when the stream is flushed. This functionality can be turned off my simply untieing the stream from itself (i.e `str.tie(nullptr)`). To initialize the stream, simply provide an output stream for it to manipulate:

    string_delimited_output_stream str(std::cout);
    
The default separator is a space character but it can be specified by a second argument. When the custom functionality is turned off (calling `tie()` will `nullptr`), this stream (for the most part) acts exactly like the stream that it wraps.
