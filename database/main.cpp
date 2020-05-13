#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include "group.h"
using namespace std;

#define PORT 1234

void write_on_socket(int fd, char * buf, int len) 
{
	write(fd, &len, sizeof(int));
	if (len > 0) write(fd, buf, len);
}

int read_from_socket(int fd, char * buf, int len) 
{
	if (read(fd, &len, sizeof(int)) != (int)sizeof(int)) 
	{
		perror("read_from_socket() read_length error");
		return -1;
	}
	int l = len;
	int i = 0;
	int nbytes = 0;
	for (i = 0; len > 0; i += nbytes, len -= nbytes) 
	{
		nbytes = read(fd, buf + i, len);
		if (nbytes < 0) 
		{
			perror("read_from_socket() read() error");
			return -1;
		} 
		else if (nbytes == 0) 
		{
			perror("read truncated");
			return -1;
		}
	}
	buf[i] = 0;
//	printf("read\n\tbytes: %d\n\t_msg_: %s\n\t_len_: %d\n", i, (i > 0) ? buf : "empty", l);
	return l;
}

int main(int argc, char *argv[])
{
	char *name;
	(void) argc;
	name = argv[1];
	FILE *fp = fopen(name, "r");
	if (!fp) 
	{
		cout << "Error" << endl;
		return 1;
	}

	gr<record> b;
	if (b.gr_read(fp))
	{
		cout << "Error" << endl;
		return 2;
	}
	cout << "was read\n";

	fclose(fp);

	struct sockaddr_in addr;
	int sock = 0;
	int opt = 1;
//
	sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (sock < 0) 
	{
		perror("socket() error");
		return 1;
	}
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof(opt));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0) 
	{
		perror("bind() error");
		close(sock);
		return 2;
	}
	if (listen(sock, 3) < 0) 
	{
		perror("listen() error");
		close(sock);
		return 2;
	}

	fd_set active_set, read_set;
	FD_ZERO(&active_set);
	FD_SET(sock, &active_set);
//

	while (true)
	{
		read_set = active_set;
		if (select(FD_SETSIZE, &read_set, 0, 0, 0) < 0) 
		{
			perror("select() error");
			close(sock);
			return 3;
		}
		for (int i = 0; i < FD_SETSIZE; i++) 
		{
			if (FD_ISSET(i, &read_set)) 
			{
				if (i == sock) 
				{
					struct sockaddr_in client;
					socklen_t size = sizeof(client);
					int new_sock = accept(sock, (struct sockaddr *)&client, &size);
					if (new_sock < 0) 
					{
						perror("accept error");
						close(sock);
						return 3;
					}
					FD_SET(new_sock, &active_set);
//	printf("Server connect\n\thost: %s\n\tport: %d\n", \
			inet_ntoa(client.sin_addr), \
			(unsigned)ntohs(client.sin_port));
				} 
				else 
				{
					char buf[LEN];
					int q = -1;
					if (read_from_socket(i, buf, LEN) < 0) 
					{
						write(i, &q, sizeof(int));
						close(i);
						FD_CLR(i, &active_set);
					} 
					else 
					{
						command a;
						int f = 0, res = a.parse(buf);
						if (res == 0) 
						{
							b.just_do_it(&a, i);
							write_on_socket(i, 0, 0);
						}
						else if (a.get_type() == STOP)
						{
							write_on_socket(i, 0, -1);
							close(sock);
							return 0;
						}
						else if (a.get_type() == QUIT) 
						{
							write(i, &q, sizeof(int));
							close(i);
							FD_CLR(i, &active_set);
						}
					}
				}
			}
		}
	}

	close(sock);
	return 0;
}



