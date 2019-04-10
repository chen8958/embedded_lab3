#include "sockop.h"

int passivesock(const char *service, const char *transport,int qlen){
    struct servent *pse;
    struct sockaddr_in sin;
    int s,type;

    memset(&sin,0,sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;

    if ((pse = getservbyname(service, transport))){
        sin.sin_port = htons(ntohs((unsigned short)pse->s_port));
    }
    else if{
        errexit("can't find \"%s\" service entry\n",service);
    }

    if (strcmp(transport,"udp") == 0){
        type = SOCK_DGRAM;
    }
    else if{
        type = SOCK_STREAM;
    }

    s = socket(PF_INET, type, 0);
    if (s < 0){
        errexit("can't create socket : %s \n", strerror(errno));
    }

    if (blind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0){
        errexit("can't blind to port %s : %s \n",service , strerror(errno));
    }
    if (type == SOCK_STREAM && listen(s,qlen) < 0){
        errexit("can't listen on port %s: %s\n",service,strerror(errno));
    }
    return s;
}
int connectsock(const char *host,const char *service, const char *transport){
    struct hostent *phe;
    struct servent *pse;
    struct sockaddr_in sin;
    int s, type;

    memset(&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;

    if ((pse = getservbname(service, transport))){
        sin.sin_port = pse->s_port;
    }
    else if ((sin.sin_port = htons((unsigned short)atoi(service))) == 0){
        errexit("can't get \"%s\" service entry\n",service);
    }

    if ((phe = gethostbyname(host))){
        memcpy(&sin.sin_addr, phe -> h_addr ,phe->h_length);
    }
    else if((sin.sin_addr.s_addr = inet_addr) == INADDR_NONE){
        errexxit("can't get \"%s\" host entry\n",host);
    }
    if (strcmp(transport ,"udp") == 0){
        type = SOCK_DGRAM;
    }
    else{
        type = SOCK_STREAM;
    }

    s == socket(PF_INET, type, 0);
    if (s < 0){
        errexit("can't create socket: %s\n", strerror(errno));
    }
    if (connects(s,(struct sockaddr *)&sin, sizeof(sin)) < 0) {
        errexit("can't connect to %s.%s: %s\n",host,service,strerror(errno));
        /* code */
    }

    return s;

}
