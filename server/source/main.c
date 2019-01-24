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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

const int port_number = 10000;

typedef struct socket_t
{
    int fd_;
    char ip_str_[INET6_ADDRSTRLEN];
    struct sockaddr_in info_;
    socklen_t len_;

} socket_t;

int main( )
{
    struct socket_t server;
    struct socket_t client;

    char buffer[1024];

    memset( &server, '0', sizeof( server ) );
    memset( &client, '0', sizeof( client ) );
    memset( &buffer, '0', sizeof( buffer ) );

    if ( ( server.fd_ = socket( PF_INET, SOCK_STREAM, 0 ) ) < 0 )
    {
        fprintf( stderr, "Could not create socket!" );
        return EXIT_FAILURE;
    }
    
    server.info_.sin_family = AF_INET;
    server.info_.sin_port = htons( port_number );
    server.info_.sin_addr.s_addr = htonl( INADDR_ANY );
    server.len_ = sizeof( struct sockaddr_in );
    
    if( bind( server.fd_, ( struct sockaddr* )&server.info_, server.len_ ) < 0 )
    {
        perror( "Can't bind socket: " );
        return EXIT_FAILURE;
    }
    
    if( listen( server.fd_, 1 ) < 0 )
    {
        perror( "Cant listen: " );
        return EXIT_FAILURE;
    }

    while( 1 )
    {
        client.fd_ = accept( server.fd_, ( struct sockaddr* )&client.info_, &client.len_ );
        if( client.fd_ < 0 )
        {
            perror( "Failed to connect: " );
        }
        
        getpeername( client.fd_, ( struct sockaddr* )&client.info_, &client.len_ );

        if ( client.info_.sin_family == AF_INET )
        {
            inet_ntop( AF_INET, &client.info_.sin_addr, client.ip_str_, sizeof( client.ip_str_ ) );
        }

        printf( "Client (%s:%d) connected to server.\n", client.ip_str_, port_number );

        strcpy( &buffer[0], "password: " );
        send( client.fd_, &buffer, sizeof( buffer ), 0 );
        
        memset( &buffer, '0', sizeof( buffer ) );
        recv( client.fd_, &buffer, sizeof( buffer ), 0 );

        printf( "%s\n", buffer );

        printf( "Client (%s:%d) disconnected from server.\n", client.ip_str_, port_number );
        close( client.fd_ );  
    }

    close( server.fd_ );

    return 0;
}