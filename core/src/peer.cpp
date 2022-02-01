#include "chatty/core/peer.h"

namespace core {

Peer::Peer(boost::asio::io_context& io_context,
           const boost::asio::ip::address& chat_room,
           const std::string& nickname)
    : socket_(io_context)
    , room_endpoint_(chat_room, chatty_port_)
    , nickname_(nickname)
{
    socket_.open(room_endpoint_.protocol());
    socket_.set_option(boost::asio::ip::udp::socket::reuse_address(true));
    socket_.bind(room_endpoint_);

    socket_.set_option(boost::asio::ip::multicast::join_group(chat_room));

    auto welcome_message = std::string(nickname_ + " connected to the chat");

    socket_.async_send_to(boost::asio::buffer(welcome_message), room_endpoint_,
                          [this](const boost::system::error_code& error_code, std::size_t bytes_sent){
        if (!error_code.failed() && bytes_sent > 0U){
            std::cout << "Entered chat room successfully" << std::endl;
        }
    });
}

void Peer::do_receive(){
    socket_.async_receive_from(boost::asio::buffer(receiving_buffer_), remote_endpoint_,
                          [this](const boost::system::error_code& error_code, std::size_t bytes_received){
        if (!error_code.failed() && bytes_received > 0){
            auto received_message_string = std::string(receiving_buffer_.begin(), receiving_buffer_.begin() + bytes_received);
            if (received_message_string.find(nickname_) != 0){
                std::cout.write(receiving_buffer_.data(), bytes_received);
                std::cout << "" << std::endl;
            }
            do_receive();
        }
    });
}

void Peer::do_send(){
    std::string nickname = nickname_;
    std::string message;
    std::getline(std::cin, message);
    std::string buffer = nickname.append(": " + message);
    socket_.async_send_to(boost::asio::buffer(buffer, maximum_message_size_), room_endpoint_,
                       [this, message](const boost::system::error_code& /*error_code*/, std::size_t bytes_sent){
        std::cout << "You: " << message << std::endl;
        std::cout << "";
        do_send();
    });
}

} // namespace core
