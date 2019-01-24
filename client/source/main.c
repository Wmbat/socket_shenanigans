/*
 *  Copyright (C) 2019 Wmbat
 *
 *  wmbat@protonmail.com
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <ifaddrs.h>

const char* const ip_address = "127.0.0.1";
const int port_number = 10000;

int main( )
{
    int index;
    int socket_fd;
    char receive_buffer[1024];
    struct sockaddr_in serv_address;
    
    if( ( socket_fd = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        return EXIT_FAILURE;
    }
    
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons( port_number );
    serv_address.sin_addr.s_addr = inet_addr( ip_address );
    
    if( connect( socket_fd, ( struct sockaddr* )&serv_address, sizeof( serv_address ) ) < 0 )
    {
        return EXIT_FAILURE;
    }
    
    recv( socket_fd, receive_buffer, sizeof( receive_buffer ), 0 );
    
    printf( receive_buffer );
    
    return 0;
}
