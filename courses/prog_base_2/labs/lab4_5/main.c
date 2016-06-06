#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>  // ptrdiff_t
#include <signal.h>

#include "socket.h"
#include "file.h"
#include "http.h"
#include "io.h"  // io_kbhit();
#include "tower.h"

#define FALSE 0
#define TRUE 1

void server_notFound(socket_t * client);

int isPostValid(http_request_t * postReq)
{
    if(postReq->formLength < 0 || postReq->formLength > 5)
        return FALSE;
    if(atof(postReq->form[0].value)<=0)
        return FALSE;
    if(atoi(postReq->form[3].value)<=0)
        return FALSE;
//use before year10k
    char * date = strtok(postReq->form[4].value,"-");
    if(atoi(date) <=0 || atoi(date)>31)
        return FALSE;
    date = strtok(NULL,"-");
    if(atoi(date) <=0 || atoi(date)>12)
        return FALSE;
    date = strtok(NULL,"-");
    if(atoi(date) <=0 || atoi(date)>9999)
        return FALSE;

    return TRUE;
}

char * server_tower_form_table_html(char * dbName,int isFiltrated,int levels, double height)
{
    towers_t * towlist = towers_new();
    if(isFiltrated)
        towers_fillFromSql_Filtrated("tower.db",towlist,levels,height);
    else
        towers_fillFromSql("tower.db",towlist);
    char table[2000];
    strcpy(table," ");
    for(int i = 0; i < towlist->amount; i++)
    {
        strcat(table,"<tr>\n");
        char buf[100];
        sprintf(buf,"<td>%i</td>\n",towlist->towarr[i].id);
        strcat(table,buf);
        sprintf(buf,"<td>%f</td>\n",towlist->towarr[i].height);
        strcat(table,buf);
        sprintf(buf,"<td>%s</td>\n",towlist->towarr[i].name);
        strcat(table,buf);
        sprintf(buf,"<td>%s</td>\n",towlist->towarr[i].material);
        strcat(table,buf);
        sprintf(buf,"<td>%i</td>\n",towlist->towarr[i].levels);
        strcat(table,buf);
        sprintf(buf,"<td>%s</td>\n",towlist->towarr[i].buildingDate);
        strcat(table,buf);
        sprintf(buf,"<td><a href=\"http://127.0.0.1:27015/towers/%i\">Elem %i</a></td>\n",i,i);
        strcat(table,buf);
        strcat(table,"</tr>\n");
    }
    return table;
}


void server_table_update(socket_t * client,char * dbName,int isFiltrated,int levels,int height)
{
    char homeBuf[10240];
    char htmlText[7000];
    char table[5000];
    strcpy(table,server_tower_form_table_html("tower.db",isFiltrated,levels,height));
    sprintf(htmlText,
            "<body>"
            "<div>"
            "<table border = \"3\">"
            "<tr>"
            "<td> ID </td>"
            "<td> Height(m) </td>"
            "<td> Name </td>"
            "<td> Material </td>"
            "<td> Levels </td>"
            "<td> BuildingDate </tg>"
            "<td> Element info </td>"
            "</tr>"
            "%s"
            "</table>"
            "<br><br><br>"
            "<a href=\"http://127.0.0.1:27015/\"> Main page </a>"
            "<br>"
            "<a href=\"http://127.0.0.1:27015/new-towers/\"> Create row </a>"
            "</form>"
            "</div>"
            "</body>",
            table);
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, homeBuf);
    socket_close(client);
}

void server_file(socket_t * client, const char * fileName)
{
    char * fileBuf;
    int fileLen = file_readAllBytes(fileName, &fileBuf);
    char header[10240];
    sprintf(header,
            "HTTP/1.1 200 OK\n"
            "Content-Length: %i\n"
            // "Content-Type: image/png\n"
            "Accept-Ranges: bytes\n"
            "Connection: close\n"
            "\n", fileLen);
    socket_write_string(client, header);
    printf(">> Sending file '%s' of size %i bytes...\n\n", fileName, fileLen);
    socket_write(client, fileBuf, fileLen);
    socket_close(client);
    free(fileBuf);
}

void server_notFound(socket_t * client)
{
    char replyBuf[1024];
    const char * htmlText = "<h1>404 Page Not Found!</h1>";
    sprintf(replyBuf,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, replyBuf);
    socket_close(client);
}

void server_OK(socket_t * client)
{
    socket_write_string(client, "HTTP/1.1 200 OK");
    socket_close(client);
}

void server_badRequest(socket_t * client)
{
    char replyBuf[1024];
    const char * htmlText = "<h1>400 Bad Request!</h1>";
    sprintf(replyBuf,
            "HTTP/1.1 400 \n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, replyBuf);
    socket_close(client);
}

void server_internalError(socket_t * client)
{
    char replyBuf[1024];
    const char * htmlText = "<h1>500 Internal server error!</h1>";
    sprintf(replyBuf,
            "HTTP/1.1 500 \n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, replyBuf);
    socket_close(client);
}

void server_send_towers(socket_t * client,char * dbName, int isFiltrated, int levels, double height)
{
    char towerJForm[9000];
    strcpy(towerJForm,towers_get_JSON_string("tower.db",isFiltrated,levels,height));
    char message[10000];
    sprintf(message,
            "HTTP/1.1 200 OK\n"
            "Content-Type: application/json\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(towerJForm), towerJForm);
    socket_write_string(client, message);
    socket_close(client);
}


void server_homepage(socket_t * client)
{
    char * greetings = "<html>"
                       "<head>"
                       "<title> Welcome to towers table </title>"
                       "</head>"
                       "<body>"
                       "<h> TOWERS TABLE IS HERE!!!!!</h>"
                       "<p><b> The links are down there</b></p>"
                       "<a href=\"http://127.0.0.1:27015/towers/\">HTML interface here!</a>"
                       "</body>"
                       "</html>";
    char message[1000];
    sprintf(message,
            "HTTP/1.1 404 \n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "\n%s", strlen(greetings), greetings);
    socket_write_string(client, message);
    socket_close(client);
}

void server_send_elem(socket_t * client, int index, char format)
{
    if(index < 0 || index >= sqlite3_get_row_count("tower.db","Towers"))
    {
        server_badRequest(client);
        return;
    }
    char message[4300];
    if(format=='j')
    {
        char * stringJSON = malloc(1000);
        strcpy(stringJSON,towers_get_JSON_elem("tower.db",index));
        sprintf(message,
                "HTTP/1.1 200 OK\n"
                "Content-Type: application/json\n"
                "Content-Length: %zu\n"
                "Connection: keep-alive\n"
                "\n%s", strlen(stringJSON), stringJSON);
        free(stringJSON);
    }
    else if (format=='s')
    {
        char elemString[4000];
        char delButton[300];
        sprintf(delButton,
                "<body>"
                "<a href=\"http://127.0.0.1:27015/towers/\" onclick=\"doDelete()\">Delete element</a>"
                "<script>"
                "function doDelete() {"
                "var xhttp = new XMLHttpRequest();"
                "xhttp.open(\"DELETE\", \"http://127.0.0.1:27015/towers/%i\", true);"
                "xhttp.send();"
                "}"
                "</script>"
                "<body>",
                index
               );
        strcpy(elemString,towers_get_string_elem("tower.db",index));
        strcat(elemString,delButton);
        sprintf(message,
                "HTTP/1.1 200 OK\n"
                "Content-Type: text/html\n"
                "Content-Length: %zu\n"
                "Connection: keep-alive\n"
                "\n%s", strlen(elemString), elemString);
        free(elemString);
    }
    else
    {
        server_internalError(client);
        return;
    }
    socket_write_string(client, message);
    socket_close(client);
}

void server_delete_elem(socket_t * client, int index)
{
    index-=1;
    if(index<0 || index >= sqlite3_get_row_count("tower.db","Towers"))
    {
        server_badRequest(client);
        return;
    }

}

void server_new_tower(client)
{
    char homeBuf[10240];
    char * htmlText =
        "<body>"
        "<div>"
        "<form action=\"http://127.0.0.1:27015/towers/\" method=\"POST\">"
        "Height(m):<br>"
        "<input type=\"text\" name=\"height(m)\" value='1337.420'><br>"
        "Name:<br>"
        "<input type=\"text\" name=\"name\" value='eiffel'><br>"
        "Material:<br>"
        "<input type=\"text\" name=\"material\" value='steel'><br>"
        "Levels:<br>"
        "<input type=\"text\" name=\"levels\" value=\"36\"><br>"
        "Building date:<br>"
        "<input type=\"text\" name=\"buildingdate\" value=\"01-01-2000\"><br>"
        "<input type=\"submit\" value='Send POST request' />"
        "</form>"
        "<br><br><br>"
        "<a href=\"http://127.0.0.1:27015/\"> Main page </a>"
        "<br>"
        "<a href=\"http://127.0.0.1:27015/towers/\"> List </a>"
        "<br>"
        "<form>"
        "</div>"
        "</body>";
    sprintf(homeBuf,
            "HTTP/1.1 200 OK\n"
            "Content-Type: text/html\n"
            "Content-Length: %zu\n"
            "Connection: keep-alive\n"
            "\n%s", strlen(htmlText), htmlText);
    socket_write_string(client, homeBuf);
}

static socket_t * g_serverSock;

void cleanup_server(void);
void inthandler(int);

int main(void)
{
    const int sPort = 27015;

    atexit(cleanup_server);
    signal(SIGINT, inthandler);

    lib_init();
    g_serverSock = socket_new();
    if (socket_bind(g_serverSock, sPort) == SOCKET_ERR)
    {
        printf("Port %i can't be binded\n", sPort);
        exit(1);
    }
    else
    {
        printf("Binded on port %i\n", sPort);
    }
    socket_listen(g_serverSock);

    char buf[10000];
    char levelsBuf[7];
    char heightBuf[20];
    socket_t * client = NULL;
    while (1)
    {
        printf("Accepting clients...\n");
        client = socket_accept(g_serverSock);
        if (NULL == client)
        {
            printf("NULL client\n");
            exit(1);
        }
        int readStatus = socket_read(client, buf, sizeof(buf));
        if (0 >= readStatus)
        {
            printf("Skipping empty request.\n");
            socket_close(client);
            socket_free(client);
            continue;
        }
        printf(">> Got request (read %i):\n`%s`\n", readStatus, buf);

        http_request_t request = http_request_parse(buf);






        // /towers/
        if (strcmp(request.uri, "/towers/") == 0 || strcmp(request.uri, "/towers") == 0)
        {
            if (strcmp(request.method,"GET")==0)
                server_table_update(client,"tower.db",FALSE,NULL,NULL);

            if (strcmp(request.method,"POST")==0)
            {
                if(isPostValid(&request))
                {
                    tower_insert("tower.db",&request);
                    server_table_update(client,"tower.db",FALSE,NULL,NULL);
                }
                else
                    server_badRequest(client);
            }

        }
        // /towers/{id}
        else if (strstr(request.uri,"/towers/")==request.uri&&strlen(request.uri)>strlen("/towers/")&&atoi(request.uri+strlen("/towers/"))!=0)
        {
            if (strcmp(request.method,"GET")==0)
            {
                if(strlen(request.uri+strlen("/towers/"))<4);
                server_send_elem(client,atoi(request.uri+strlen("/towers/")),'s');
            }

            if (strcmp(request.method,"DELETE")==0)
            {
                if(strlen(request.uri+strlen("/towers/"))<4);
                tower_delete("tower.db",atoi(request.uri+strlen("/towers/")));
                server_OK(client);
            }


        }
        // /new-towers/
        else if (strcmp(request.uri, "/new-towers/") == 0 || strcmp(request.uri, "/new-towers") == 0)
        {
            if (strcmp(request.method,"GET")==0)
                server_new_tower(client);
            server_table_update(client,"tower.db",FALSE,0,0);
        }
        // /api/towers/
        else if (strcmp(request.uri, "/api/towers/") == 0 || strcmp(request.uri, "/api/towers") == 0)
        {
            if (strcmp(request.method,"POST")==0)
            {
                if(isPostValid(&request))
                    tower_insert("tower.db",&request);
                else
                    server_badRequest(client);
            }

            if (strcmp(request.method,"GET")==0)
            {
                server_send_towers(client,"tower.db",FALSE,NULL,0);
            }
        }

        // /api/towers/{id}
        else if (strstr(request.uri,"/api/towers/")==request.uri&&strlen(request.uri)>strlen("/api/towers/")&&atoi(request.uri+strlen("/api/towers/"))!=0)
        {
            if (strcmp(request.method,"GET")==0)
            {
                if(strlen(request.uri+strlen("/api/towers/"))<4);
                server_send_elem(client,atoi(request.uri+strlen("/api/towers/")),'j');
            }

            else if (strcmp(request.method,"DELETE")==0)
            {
                if(strlen(request.uri+strlen("/api/towers/"))<4);
                tower_delete("tower.db",atoi(request.uri+strlen("/api/towers/")));
                server_OK(client);
            }

        }

        // /api/towers/?levels=X&height=Y
        else if (strstr(request.uri,"/api/towers/")==request.uri&&strlen(request.uri)>strlen("/api/towers/"))
        {
            if(strlen(request.uri+strlen("/api/towers/"))>1||atoi(request.uri+strlen("/api/towers/"))==0)
            {
                if(*(request.uri+strlen(request.uri)-1)=='/')
                    *(request.uri+strlen(request.uri)-1) = '\0';
                if(strchr(request.uri+strlen("/api/towers/"),'?')!=NULL \
                        &&strstr(request.uri+strlen("/api/towers/"),"levels=")!=NULL \
                        &&strstr(request.uri+strlen("/api/towers/"),"height=")!=NULL \
                        &&strchr(request.uri+strlen("/api/towers/"),'&')!=NULL \
                  )
                {

                    if(*(request.uri+strlen(request.uri)-1) == '/')
                        *(request.uri+strlen(request.uri)-1) = '\0';

                    if(strstr(request.uri+strlen("/api/towers/"),"?levels=")!=NULL)
                    {
                        size_t levelsDiff = strchr(request.uri,'&') - strstr(request.uri,"?levels=") - strlen("?levels=");
                        memcpy(levelsBuf,strstr(request.uri,"?levels=") + strlen("?levels="),levelsDiff);
                        levelsBuf[levelsDiff+1]='\0';
                        if(!(levelsDiff>1&&atoi(levelsBuf)==0))
                        {
                            strcpy(heightBuf,strstr(request.uri,"&height=")+strlen("&height="));
//                    server_table_update(client,"tower.db",TRUE,atoi(levelsBuf),atof(heightBuf));
                            server_send_towers(client,"tower.db",TRUE,atoi(levelsBuf),atof(heightBuf));
                        }
                    }
                    else
                    {
                        size_t heightDiff = strchr(request.uri,'&') - strstr(request.uri,"?height=") - strlen("?height=");
                        memcpy(heightBuf,strstr(request.uri,"?height=") + strlen("?height="),heightDiff);
                        heightBuf[heightDiff+1]='\0';
                        if(!(heightDiff>1&&atof(heightBuf)==0))
                        {
                            strcpy(levelsBuf,strstr(request.uri,"&levels=")+strlen("&levels="));
//                    server_table_update(client,"tower.db",TRUE,atoi(levelsBuf),atof(heightBuf));
                            server_send_towers(client,"tower.db",TRUE,atoi(levelsBuf),atof(heightBuf));
                        }
                    }
                }
            }

        }





// GET /

    else if (strcmp(request.uri,"/")==0)
    {
        server_homepage(client);
    }
    {
        const char * filePath = strstr(request.uri, "/") + 1;
        if (file_exists(filePath))
        {
            server_file(client, filePath);
        }
        else
        {
            server_notFound(client);
        }
    }

    socket_free(client);
}
socket_free(g_serverSock);
lib_free();
return 0;
}

void inthandler(int sig)
{
    exit(0);  // call to cleanup_server at exit
}

void cleanup_server(void)
{
    printf("Cleanup server.\n");
    socket_close(g_serverSock);
    socket_free(g_serverSock);
}
