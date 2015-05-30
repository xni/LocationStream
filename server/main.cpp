#include <iostream>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

#include <chrono>
#include <thread>

using namespace std;


struct server {

    server(boost::asio::io_service& io_service)
        : io_service_(io_service),
          ep(boost::asio::ip::udp::v4(), 9898),
          socket_(io_service_, ep) {
        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length),
                sender_endpoint_,
                boost::bind(&server::handle_receive_from, this, _1, _2)
        );
    }

    void handle_receive_from(const boost::system::error_code& error,
                             size_t bytes_recvd) {
        std::cout << "Received a message " << data_ << "\n";

        socket_.async_receive_from(
                boost::asio::buffer(data_, max_length),
                sender_endpoint_,
                boost::bind(&server::handle_receive_from, this, _1, _2)
        );
    }

    enum { max_length = 30 };
    char data_[max_length];
    boost::asio::io_service& io_service_;
    boost::asio::ip::udp::endpoint ep;
    boost::asio::ip::udp::socket socket_;
    boost::asio::ip::udp::endpoint sender_endpoint_;
};





int main() {
    boost::asio::io_service service;
    server s(service);

    cout << "Hello, World!" << endl;
    service.run();
    return 0;
}