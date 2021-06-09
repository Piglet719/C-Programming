#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    char *buf, *rbuf;
    int fd, i, ret;
    unsigned int fileSize;
    if(argc != 2){
        fprintf(stderr, "usage: reverse [FileName].\n");
        exit(1);
    }
    fd = open(argv[1], O_RDWR, 0600);
    if(fd < 0){
        fprintf(stderr, "open %s error.\n", argv[1]);
        exit(1);
    }
    fileSize = lseek(fd, 0, SEEK_END);
    buf = (char *) malloc(fileSize + 1);
    rbuf = (char *) malloc(fileSize + 1);
    if(buf == NULL || rbuf == NULL){
        fprintf(stderr, "malloc failed. size: %d\n", fileSize);
        exit(1);
    }
    lseek(fd, 0, SEEK_SET); //回到文章開頭
    ret = read(fd, buf, fileSize);
    if(ret < 0){
        fprintf(stderr, "read %s error.\n", argv[1]);
        exit(1);
    }
    else if(ret == 0){
        fprintf(stderr, "The end of %s.\n", argv[1]);
        exit(1);
    }
    for(i=0;i<fileSize;i++){
        rbuf[i] = buf[fileSize-i-1];
    }
    lseek(fd, 0, SEEK_SET); //回到文章開頭
    ret = write(fd, rbuf, fileSize);
    if(ret < 0){
        fprintf(stderr, "write %s error.\n", argv[2]);
    }
    close(fd);
    free(buf);
    free(rbuf);
    return 0;
}
