/**
 * ============================================================================
 * @file    rtmfpcli.cpp
 *
 * @brief   
 * @details 
 *
 * @version 1.0  
 * @date    2013-06-08 17:31:05
 *
 * @author  shizhijie, shizhijie@baofeng.com
 * ============================================================================
 */

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include "rtmfp_protocol.h"
using boost::asio::ip::udp;

int main(int argc, char *argv[])
{
  if (argc != 3)
    {
      std::cerr << "Usage: " << argv[0] << " <host> <port>" << std::endl;
      return -1;
    }

  try
    {
      boost::asio::io_service ios;

      udp::socket sock(ios, udp::endpoint(udp::v4(), 4));
      udp::resolver resolver(ios);
      udp::resolver::query query(udp::v4(), argv[1], argv[2]);
      udp::resolver::iterator iter = resolver.resolve(query);

      static uint8_t epd_data[] = "rtmfp://192.168.202.92/";
      static uint8_t tag[] = {
		0x04, 0x83, 0x5E, 0xE7, 0x3E, 0x25, 0x81, 0xEE,
		0x1C, 0x49, 0x4D, 0x7F, 0x10, 0x66, 0xBA, 0xBD
      };
      uint32_t snd_buf_size = 0;
      uint8_t *p_snd_buf = NULL;
      p_snd_buf = const_cast<uint8_t *>(generate_handshake1(0x0a, epd_data, sizeof(epd_data),
							    tag, sizeof(tag),	&p_snd_buf,
							    snd_buf_size));
      sock.send_to(boost::asio::buffer(p_snd_buf, snd_buf_size), *iter);

      enum { MAX_LEN = 1024 * 10 };
      uint8_t recv_buf[MAX_LEN] = { 0xff };
      udp::endpoint snd_endpoint;
      size_t recv_len = sock.receive_from(boost::asio::buffer(recv_buf, MAX_LEN),
					  snd_endpoint);
      std::cout.write(reinterpret_cast<const char *>(recv_buf), recv_len);
    }
  catch (std::exception &ex)
    {
      std::cout << ex.what() << std::endl;
    }
	
  return 0;
}
