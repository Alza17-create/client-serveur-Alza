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
#include <signal.h>

void fin (int i);
void appli(int no_client_socket);
char buffer[512];
int ma_socket;

struct dir;

int main ( void )
{
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



int client_socket;
struct sockaddr_in mon_address, client_address;
int mon_address_longueur, lg;

bzero(&mon_address,sizeof(mon_address));
mon_address.sin_port = htons(port);
mon_address.sin_family = AF_INET;
long hostAddr = inet_addr(addr);
bcopy(&hostAddr,&mon_address.sin_addr,sizeof(hostAddr));
/* creation de socket */
if ((ma_socket = socket(AF_INET,SOCK_STREAM,0))== -1)
{
  printf("Creation echoue\n");
  exit(0);
}
signal(SIGINT,fin);
/* bind serveur - socket */
bind(ma_socket,(struct sockaddr *)&mon_address,sizeof(mon_address));

/* ecoute sur la socket */
listen(ma_socket,5);

/* accept la connexion */
mon_address_longueur = sizeof(client_address);
while(1)
{
  client_socket = accept(ma_socket,
                         (struct sockaddr *)&client_address,
                         &mon_address_longueur);
bzero(buffer,sizeof(buffer));
read(client_socket,buffer,512);
printf("%s\n",buffer);
bzero(buffer,sizeof(buffer));
strcpy(buffer,"Bonjour client");
write(client_socket,buffer,512);
bzero(buffer,sizeof(buffer));
  if (fork() == 0)
  {
    close(ma_socket);


    }

    DIR *d;
  struct dirent *dir;
  d = opendir("/home/ferio06/Desktop/ALZA");
  if (d) {
    while ((dir = readdir(d)) != NULL) {


    //read(client_socket,dir->d_name);
    //dir=dir->d_name;

    printf("%s\n", dir->d_name);
    sprintf(dir->d_name,"%s\n",dir->d_name);
    write(client_socket, dir->d_name,512);
    /* fermeture de la connection */


    shutdown(client_socket,2);
    close(client_socket);

    }
    closedir(d);
  }
return(0);
    /*
    lg = read(client_socket,buffer, 512);
    printf("le serveur a recu: %s\n",buffer);
    sprintf(buffer,"%s du serveur",buffer);
    write(client_socket,buffer, 512);
    shutdown(client_socket,2);
    close(client_socket);
    exit(0);
    */

}
//shutdown(ma_socket,);
//close(ma_socket);
}


void appli(int no_client_socket)
{
  printf("ici le serveur\n");
}

void fin(int i)
{
shutdown(ma_socket,2);
close(ma_socket);
}
