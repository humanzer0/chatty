#include <iostream>
#include <string>

#include <boost/asio.hpp>

namespace core {

class Peer {
public:
    Peer(boost::asio::io_context& io_context,
         const boost::asio::ip::address& chat_room,
         const std::string& nickname);

    void do_receive();
    void do_send();

private:
    constexpr static std::uint16_t chatty_port_ = 8000U;
    constexpr static std::size_t maximum_message_size_ = 128;

    std::array<char, 128> receiving_buffer_;
    std::string nickname_;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint remote_endpoint_;
    boost::asio::ip::udp::endpoint room_endpoint_;
};

} // namespace core
