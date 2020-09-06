#include <stdio.h>
#include <pth.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>

static void *handler(void *_arg)
{
    int fd = *((int*)_arg);
    time_t now;
    char *ct;

    now = time(NULL);
    ct = ctime(&now);
    pth_write(fd, ct, strlen(ct));
    close(fd);
    return NULL;
}

static void *ticker(void *_arg)
{
    time_t now;
    char *ct;
    float load;

    for (;;) {
        pth_sleep(5);
        now = time(NULL);
        ct = ctime(&now);
        ct[strlen(ct)-1] = '\0';
        pth_ctrl(PTH_CTRL_GETAVLOAD, &load);
        printf("ticker: time: %s, average load: %.2f\n", ct, load);
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    pth_attr_t attr;
    struct sockaddr_in sar;
    struct protoent *pe;
    struct sockaddr_in peer_addr;
    socklen_t peer_len;
    int sa, sw;
    int port;

    pth_init();
    port = atoi(argv[1]);
    signal(SIGPIPE, SIG_IGN);

    attr = pth_attr_new();
    pth_attr_set(attr, PTH_ATTR_NAME, "ticker");
    pth_attr_set(attr, PTH_ATTR_STACK_SIZE, 32*1024);
    pth_attr_set(attr, PTH_ATTR_JOINABLE, FALSE);
    pth_spawn(attr, ticker, NULL);

    pe = getprotobyname("tcp");
    sa = socket(AF_INET, SOCK_STREAM, pe->p_proto);
    sar.sin_family = AF_INET;
    sar.sin_addr.s_addr = INADDR_ANY;
    sar.sin_port = htons(port);
    bind(sa, (struct sockaddr *)&sar, sizeof(struct sockaddr_in));
    listen(sa, 10);

    pth_attr_set(attr, PTH_ATTR_NAME, "handler");
    for (;;) {
        sw = pth_accept(sa, (struct sockaddr *)&peer_addr, &peer_len);
        pth_spawn(attr, handler, (void *)&sw);
    }

    return 0;
}
