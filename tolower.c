#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    char *buf;
    int fd, readCnt, offset;
    unsigned int fileSize;
    if(argc != 2){
        fprintf(stderr, "usage: tolower [FileName].\n");
        exit(1);
    }
    fd = open(argv[1], O_RDWR, 0600);
    if(fd < 0){
        fprintf(stderr, "open %s error.\n", argv[1]);
        exit(1);
    }
    fileSize = lseek(fd, 0, SEEK_END);
    buf = (char *) malloc(fileSize + 1);
    if(buf == NULL){
        fprintf(stderr, "malloc failed. size: %d\n", fileSize);
        exit(1);
    }
    lseek(fd, 0, SEEK_SET); //回到文章開頭
    offset = 0;
    while((readCnt = read(fd, buf, 1))>0){
        if((*buf >= 'A') && (*buf <= 'Z')){
            *buf = *buf - 'A' + 'a';
        }
        lseek(fd, offset, SEEK_SET);
        write(fd, buf, 1);
        offset++;
    }
    close(fd);
    free(buf);
    return 0;
}
