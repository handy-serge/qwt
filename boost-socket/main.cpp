#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include "Deframer.hpp"

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    Deframer deframer(8);

    try
    {
        if (argc != 3)
        {
            std::cerr << "Usage: boost-socket <host> <port>" << std::endl;
            return 1;
        }

        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(argv[1], argv[2]);
        tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

        tcp::socket socket(io_service);
        boost::asio::connect(socket, endpoint_iterator);

        for (;;)
        {
            boost::array<unsigned short, 128> buf;
            boost::system::error_code error;

            size_t cb = socket.read_some(boost::asio::buffer(buf), error);
            size_t cw = cb / sizeof(unsigned short);

            for (size_t i = 0; i < cw; ++i)
            {
                deframer.ValidateNextWord(buf[i]);
            }

            if (error == boost::asio::error::eof)
                break; // Connection closed cleanly by peer.
            else if (error)
                throw boost::system::system_error(error); // Some other error.
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << "Number of correct frames: " << deframer.m_cFrames << std::endl;
    std::cout << "Number of words skipped: " << deframer.m_cwSkipped << std::endl;
    std::cout << "Total number of words: " << deframer.m_cwTotal << std::endl;

    return 0;
}
