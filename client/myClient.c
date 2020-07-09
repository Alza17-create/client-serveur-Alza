#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <dirent.h>
#include <netdb.h>


int to_server_socket = -1;

int main (void)
{

char *server_name = "127.0.0.1";
struct sockaddr_in serverSockAddr;
struct hostent *serverHostEnt;
long hostAddr;
long status;
char buffer[512];
char addr[256];
int port;

printf("Addresse serveur (0 pour 127.0.0.1): ");
scanf("%s", addr);
if (strcmp(addr,"0") == 0){
	bzero(addr,sizeof(addr));
	strcpy(addr,"127.0.0.1");
}


char str_port[256];
printf("Port serveur (0 pour 30000): ");
scanf("%s", str_port);
port = atoi(str_port);

if (strcmp(str_port,"0") == 0)
	port = 30000;




bzero(&serverSockAddr,sizeof(serverSockAddr));

/*
serverSockAddr.sin_port = htons(port); //port par defaut 8080
inet_pton(AF_INET,addr,&serverSockAddr.sin_addr.s_addr); // adresse par defaut
*/
hostAddr = inet_addr(addr);
if ( (long)hostAddr != (long)-1)
  bcopy(&hostAddr,&serverSockAddr.sin_addr,sizeof(hostAddr));
else
{
  serverHostEnt = gethostbyname(addr);
  if (serverHostEnt == NULL)
  {
    printf("Erreur lors de la gethost\n");
    exit(0);
  }
  bcopy(serverHostEnt->h_addr,&serverSockAddr.sin_addr,serverHostEnt->h_length);
}
serverSockAddr.sin_port = htons(port);
serverSockAddr.sin_family = AF_INET;

/* creation de la socket */
if ( (to_server_socket = socket(AF_INET,SOCK_STREAM,0)) < 0)
{
  printf("Erreur lors de la creation socket client\n");
  exit(0);
}
/* requete de connexion */
if(connect( to_server_socket,
            (struct sockaddr *)&serverSockAddr,
            sizeof(serverSockAddr)) < 0 )
{
  printf("Erreur lors de la demande de connection\n");
  exit(0);
}
/* envoie de donne et reception */
char mess[] = "Bonjour serveur";
write(to_server_socket,mess,sizeof(mess));
read(to_server_socket,buffer,512);
printf("%s\n",buffer);

bzero(buffer,sizeof(buffer));
read(to_server_socket,buffer,512);
printf("%s\n",buffer);
/* fermeture de la connection */
shutdown(to_server_socket,2);
close(to_server_socket);
}
