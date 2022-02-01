#include "chatty/core/peer.h"

#include <boost/asio/thread_pool.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/post.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
    boost::asio::thread_pool thread_pool(2);

    if(argc != 3){
        std::cerr << "Usage: ./chatty <your_nickname> <chat_room>" << std::endl;
        std::exit(1);
    }

    boost::asio::io_context io_context;
    boost::asio::ip::address chat_room(boost::asio::ip::make_address(argv[2]));
    core::Peer peer(io_context, chat_room, argv[1]);

    boost::asio::post(thread_pool, [&]{
        peer.do_receive();
        io_context.run();
    });
    boost::asio::post(thread_pool, [&]{
        peer.do_send();
        io_context.run();
    });
    thread_pool.join();

    return 0;
}
