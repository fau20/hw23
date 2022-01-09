#include "pipe_networking.h"

int main() {

  int client_socket;
  int sd;

  sd = server_setup();

  while(1){
    client_socket = server_connect(sd);

    char line[1000];
    int f = fork();
    if(f) {
      close(client_socket);
    }
    else {
      while(read(client_socket, line, sizeof(line)) != 0){
        int i = 0;
        while(line[i]) {
          if(line[i] >= 'a' && line[i] <= 'z') {
            line[i] = line[i] - 'a' + 'A';
          }
          i++;
        }
        write(client_socket, line, sizeof(line));
      }
      exit(0);
    }
  }
}
