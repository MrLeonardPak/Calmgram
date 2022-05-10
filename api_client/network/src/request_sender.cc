#include "request_sender.h"

using  boost::asio::ip::tcp;

namespace calmgram::api_client::network {

    std::string RequestSender::Execute(std::string request) {
        boost::asio::io_service io_service;
        tcp::endpoint ep(boost::asio::ip::address::from_string("127.0.0.1"),1234);
        tcp::socket socket(io_service);
        socket.connect(ep);
        std::string data;
        if(socket.is_open())
        {
            boost::system::error_code error;
            boost::asio::write( socket, boost::asio::buffer(request), error);
            if (error) {
                // кинуть ошибку
            }
            boost::asio::streambuf receive_buffer;
            boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);
            if( error && error != boost::asio::error::eof ) {
                // кинуть ошибку
            }
            else {
                std::istream(&receive_buffer) >> data;
                return data;
            }
        } else {
            // кинуть ошибку
        }
        
        return data;
    }

} // namespace calmgram::api_client::network


