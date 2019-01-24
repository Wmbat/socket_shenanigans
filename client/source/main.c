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
    char buffer[1024];
    
    struct sockaddr_in serv_address;
    struct hostent* p_server;
    
    if( ( socket_fd = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        perror( "Failed to open Socket!" );
        return EXIT_FAILURE;
    }
    
    p_server = gethostbyname( ip_address );
    if( p_server == NULL )
    {
        perror( "No such host found" );
    }
    
    memset( &serv_address, '0', sizeof( serv_address ) );
    serv_address.sin_family = AF_INET;
    serv_address.sin_port = htons( port_number );
    memcpy( &serv_address.sin_addr.s_addr, p_server->h_addr, p_server->h_length );
    
    if( connect( socket_fd, ( struct sockaddr* )&serv_address, sizeof( serv_address ) ) < 0 )
    {
        perror( "Failed to connect to server!" );
        return EXIT_FAILURE;
    }

    printf( "Connection to server (%s)\n", p_server->h_name );
    
    recv( socket_fd, buffer, sizeof( buffer ), 0 );
    printf( "%s", buffer );
    
    memset( &buffer, '0', sizeof( buffer ) );
    scanf( "%s", &buffer  );
    send( socket_fd, &buffer, sizeof( buffer ), 0 );
    printf( "\n" );
    
    return 0;
}
