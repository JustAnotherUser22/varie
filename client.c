#include <sys/types.h>
//#include <sys/socket.h>
//"in" per "sockaddr_in"
//#include <netinet/in.h>
//"netdb" per "gethostbyname"
//#include <netdb.h>

/*
int CreaSocket(char* Destinazione, int Porta)
{
  struct sockaddr_in temp; 
  struct hostent *h;
  int sock;
  int errore;
  
  //Tipo di indirizzo
  temp.sin_family=AF_INET;
  temp.sin_port=htons(Porta);
  h=gethostbyname(Destinazione);
  if (h==0) 
  {
    printf("Gethostbyname fallito\n");
    exit(1);
  }
  bcopy(h->h_addr,&temp.sin_addr,h->h_length);
  //Creazione socket. 
  sock=socket(AF_INET,SOCK_STREAM,0);
  //Connessione del socket. Esaminare errore per compiere azioni
  //opportune in caso di errore.
  errore=connect(sock, (struct sockaddr*) &temp, sizeof(temp));
  return sock;
}


int main(int argc,char* argv[])
{
  int DescrittoreSocket;
  
  //Creo e connetto il socket
  DescrittoreSocket=CreaSocket("127.0.0.1",1745);
  
  //Spedisco il messaggio voluto
  if ((argc==2)&&(strcmp(argv[1],"exit")==0))
    SpedisciMessaggio(DescrittoreSocket,"exit");
  else
    SpedisciMessaggio(DescrittoreSocket,"Un messaggio");

  //Chiudo il socket.
  close(DescrittoreSocket);

  return 0;
}

*/
