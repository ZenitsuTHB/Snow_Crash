#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>


int main() {


  int fd, bytes;
  fd = open("token", O_RDONLY);
  if (fd < 0) {
    perror("Trouble reading file !");
    exit(1);
  }
  printf("fd = %d\n", fd);
  char *buf = (char*)calloc(30, sizeof(char));
  bytes = read(fd, buf, 30);
  buf[bytes] = '\0';
  printf("Those byte are as follow :\n%s\nThe password is : \n", buf);
  for (int i = 0; i < strlen(buf) - 1; i++){

    printf("%c", buf[i] - i);
  }
  printf("\n");
  close(fd);
  free(buf);
  return 0;
}
