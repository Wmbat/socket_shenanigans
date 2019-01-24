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
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>

const char* const ip_address = "127.0.1.1";
const int port_number = 10000;

int main( )
{
    int socket_fd;
    int connection_fd;
    struct sockaddr_in address;
    
    char send_buffer[1024];
    memset( &send_buffer, '0', sizeof( send_buffer ) );
    
    if ( ( socket_fd = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        fprintf( stderr, "Could not create socket!" );
        return EXIT_FAILURE;
    }
    
    memset( &address, '0', sizeof( address ) );
    address.sin_family = AF_INET;
    address.sin_port = htons( port_number );
    address.sin_addr.s_addr = htonl( INADDR_ANY );
    
    if( bind( socket_fd, ( struct sockaddr* )&address, sizeof( address ) ) < 0 )
    {
        perror( "Can't bind socket: " );
        return EXIT_FAILURE;
    }
    
    if( listen( socket_fd, 10 ) < 0 )
    {
        perror( "Cant listen: " );
        return EXIT_FAILURE;
    }
    
    while( 1 )
    {
        connection_fd = accept( socket_fd, ( struct sockaddr* )NULL, NULL );
        
        
        
        strcpy( send_buffer, "Hello From server." );
        send( connection_fd, send_buffer, sizeof( send_buffer ), 0 );
        
        
        close( connection_fd );
    }
    
    
    return 0;
}