#include <semaphore.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#include "proxy_parse.h"

#define MAX_CLIENTS 10

typedef struct cache_element {
  char* url;
  char* data;
  int len;
  time_t lru_time_track;
  cache_element* next;
} cache_element;

cache_element* find(char* url);
int add_cache_element(char* url, char* data, int len);
void remove_cache_element();

int port_number = 8080;
int proxy_socketId;
pthread_t tid[MAX_CLIENTS];
sem_t mutex;

