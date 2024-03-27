/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TCP_Connection.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amait-ou <amait-ou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 16:56:53 by amait-ou          #+#    #+#             */
/*   Updated: 2024/03/27 05:53:51 by amait-ou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include "TCP_Exceptions.hpp"
#include "HTTP_Request.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <map>
#include <poll.h>

// Colors

#define RED     "\x1B[31m"
#define BLUE    "\x1B[34m"
#define GREEN   "\x1B[32m"
#define GREY    "\x1B[90m"
#define CYAN	"\x1b[36m"
#define YELLOW  "\x1B[33m"
#define RESET   "\x1B[0m"

// Buffer Size for reading from socket

#ifndef BUFFER_SIZE
	#define BUFFER_SIZE 1024
#endif
#ifndef NUMBER_OF_CLIENTS
	#define NUMBER_OF_CLIENTS 1024
#endif

// Typedefs for readability

typedef unsigned long t_ul;
typedef struct sockaddr _sockaddr;
typedef struct sockaddr_in _sockaddr_in;

// TCP Connection Class

class TCP_Connection
{
	private:
		std::map<int, HTTP_Request> clients;
		char						buffer[BUFFER_SIZE];
		socklen_t					address_len;
		struct pollfd				fds[NUMBER_OF_CLIENTS];
		_sockaddr_in				address_s;
		int							server_fd;
		int							client_fd;
		
	
	public:
		// Constructors
		TCP_Connection(int domain, int service, int protocol, int port, t_ul interface);
		
		// Getters
		int				getSocketFd(void) const;
		socklen_t		getAddressLen(void) const;
		_sockaddr_in	getStructSockAddrIn(void) const;
		
		// SysCalls
		void			socketBind(void);
		void			socketListen(void);
		void			socketAccept(void);

		// Setters
		void			socketSetOptions(void);

		// Printers
		void			printListener(void) const;
		void			printBanner(void) const;

		// Server
		void			serve(void);
};

#endif