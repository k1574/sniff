#include <stdlib.h>
#include <stdio.h>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/udp.h>
#include <netinet/tcp.h>
#include <netinet/ip.h>

#include <unistd.h>

enum {
	BufSiz = 256*256,
} ;

char *argv0;
unsigned char *buf;
int sock, sock_type = SOCK_RAW ,
	sock_domain = AF_INET ,
	sock_proto = IPPROTO_TCP ;

void
usage(void)
{
	fprintf(stderr, "usage: %s\n", argv0);
	exit(1);
}

int
main(int argc, char *argv[])
{
	int ndata, naddr;
	struct sockaddr saddr;
	struct in_addr in;
	argv0 = argv[0] ;
	buf = malloc(BufSiz) ;

	if( (sock=socket(sock_domain, sock_type, sock_proto)) < 1) {
		fprintf(stderr, "%s: could not create socket\n", argv0);
		exit(1);
	}

	while(1){
		ndata = recvfrom(sock, buf, BufSiz, 0, &saddr, &naddr) ;
		if(ndata < 0){
			fprintf(stderr, "%s: failed to get packets\n", argv0);
			return 1 ;
		}
		write(1, buf, ndata);
	}

	return 0 ;
}

