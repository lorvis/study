#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#define PB_PORT 80
#define MAX_BUFFER_SIZE 20480
#define NO_FLAGS 0
#define NOT_SPECIFIED_PROTOCOL 0

void setServerSockInfo(SOCKADDR_IN * server_s,char * ip, int port, int family){
memset(server_s, 0, sizeof(*server_s));
server_s->sin_addr.s_addr = inet_addr(ip);
server_s->sin_family = family;
server_s->sin_port = htons(port);
}

void hostnameToIp(const char * hostname, HOSTENT * any_host_info, char ** ip_str_pt){
any_host_info = gethostbyname(hostname);
*ip_str_pt = inet_ntoa(*(struct in_addr *)*any_host_info->h_addr_list);
}

void httpToContent(char ** content, char * http){

*content = strtok(http,"\n");

for(int i = 0; i < 6; i++){
        *content = strtok(NULL,"\n");
}

}

void recvCheckForError(int recv_size, SOCKET s){
int status;
if(recv_size == SOCKET_ERROR)
{
    puts("Recieving error!");
    status = closesocket(s);
    if(status == SOCKET_ERROR)
        puts("Socket closing error");
        status == WSACleanup();
        if (status == SOCKET_ERROR)
            puts("WSACleanup error!");
        return 1;
}
}

int main()
{
WSADATA wsa;
SOCKET s;
SOCKADDR_IN server_s;
const char * hostname = "pb-homework.appspot.com";
const char * link = "/var/11?secret=totalrecall";
int status;
int recv_size = 0;
char * ip;
char * content;
char * arrayelem;
char * result;
char buffer[20480];
int sum=0;
HOSTENT * host_info;
status = WSAStartup(MAKEWORD(2,2),&wsa);

if(status!=0){
    puts("WSA Startup error");
    return 1;
}

hostnameToIp(hostname,host_info,(char**)&ip);

printf("IP address is: %s.\n",ip);

setServerSockInfo((SOCKADDR_IN *)&server_s,ip,PB_PORT,AF_INET);

s = socket(AF_INET,SOCK_STREAM,NOT_SPECIFIED_PROTOCOL);

if(s == INVALID_SOCKET){
    puts("socket creation problem");
    WSACleanup();
    return 1;
}


if(connect(s,(SOCKADDR*)&server_s,sizeof(SOCKADDR_IN)) == SOCKET_ERROR){
    printf("CONNECTION ERROR");
    closesocket(s);
    WSACleanup();
    return 1;

}

char request[200];
sprintf(request, "GET %s HTTP/1.1\nHost:%s\r\n\r\n",link, hostname);

printf("request is : %s\n\r\n",request);

send(s, request, strlen(request), NO_FLAGS);

recv_size = recv(s, buffer, MAX_BUFFER_SIZE, NO_FLAGS);

recvCheckForError(recv_size,s);

//content = strtok(buffer,"\n");
//
//for(int i = 0; i < 6; i++){
//        content = strtok(NULL,"\n");
//}

httpToContent((char **)&content,buffer);

printf("ARRAY : %s\n",content);

arrayelem = strtok(content," ");

while(arrayelem!=NULL){
    sum+=atoi(arrayelem);
    arrayelem = strtok(NULL," ");
}

printf("SUM = %i",sum);

sprintf(result,"result=%i",sum);

sprintf(request,"POST %s HTTP/1.1\nHost:%s\r\nContent-Length:%d\r\n\r\n%s",link,hostname,strlen(result),result);

send(s, request, strlen(request), NO_FLAGS);

recv_size = recv(s, buffer, MAX_BUFFER_SIZE, NO_FLAGS);

recvCheckForError(recv_size,s);

puts(buffer);

closesocket(s);
WSACleanup();
    return 0;
}
