#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define print(x) printf(x "\n")
#define err(x) fprintf(stderr, x "\n")

void handle_connection(int port) {
    int conn_server, conn_client;
    struct sockaddr_in server, client;
    conn_server = socket(AF_INET, SOCK_STREAM, 0); // ip generic protocol

    if (conn_server < 0) {
        err("socket() failed");
        exit(conn_server);
    }

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY; // acepto todo.
    int r = bind(conn_server, (struct sockaddr *)&server, sizeof(server));

    if (r < 0) {
        err("bind failed");
        exit(r);
    }

    listen(conn_server, 3);
    print("Listening...");

    int sz = sizeof(struct sockaddr_in);
    print("Press Ctrl+C to exit.");

    while (1) {
        conn_client = accept(
            conn_server, 
            (struct sockaddr *)&client, 
            (socklen_t *)&sz
        );
        printf("Connection received from: %s\n", inet_ntoa(client.sin_addr));

        if (conn_client < 0) {
            err("accept failed. Exiting...");
            exit(conn_client);
        }

        time_t t;
        t = time(NULL);
        struct tm * mydate = localtime(&t);
        
        if (mydate == NULL) {
            err("localtime failed!");
            exit(EXIT_FAILURE);
        }

        int buffsize = 1024;
        char * date_str;
        date_str = (char *) malloc(buffsize * sizeof(char));

        if (date_str == NULL) {
            err("No space here!");
            exit(EXIT_FAILURE);
        }

        const char * f_str = "%A, %d %b %Y %T\n";

        if (strftime(date_str, buffsize, f_str, mydate) == 0) {
            err("Error");
            exit(EXIT_FAILURE);
        }
        

        write(conn_client,  date_str, strlen(date_str));
        shutdown(conn_client, SHUT_RDWR);
        close(conn_client);
    }

}

int main(int argc, char * argv[]) {
    long myport;
    print("Hello, friend");
    printf("Insert the port you wanna listen: ");
    scanf("%ld", &myport);
    printf("You have chose: %ld\n", myport);

    if (myport <= 0 || myport >= 65535) {
        err("Bad Option.");
        exit(2);
    }
    handle_connection(myport);

    return 0;
}
