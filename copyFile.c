#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv){
    char *buf;
    int fd_in, fd_out, fileSize, ret;
    if(argc != 3){
        fprintf(stderr, "usage: ./a.out [sourceFile] [targetFile].\n");
        exit(1);
    }

    fd_in = open(argv[1], O_RDONLY, S_IRUSR);
    if(fd_in < 0){
        fprintf(stderr, "open %s error.\n", argv[1]);
        exit(1);
    }
    fd_out = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0600);
    if(fd_out < 0){
        fprintf(stderr, "open %s error.\n", argv[2]);
        exit(1);
    }
    fileSize = lseek(fd_in, 0, SEEK_END);
    buf = (char *) malloc(fileSize + 1);
    if(buf == NULL){
        fprintf(stderr, "malloc failed. size: %d\n", fileSize);
        exit(1);
    }
    lseek(fd_in, 0, SEEK_SET); //回到文章開頭
    ret = read(fd_in, buf, fileSize);
    if(ret < 0){
        fprintf(stderr, "read %s error.\n", argv[1]);
        exit(1);
    }
    else if(ret == 0){
        fprintf(stderr, "The end of %s.\n", argv[1]);
        exit(1);
    }
    ret = write(fd_out, buf, fileSize);
    if(ret < 0){
        fprintf(stderr, "write %s error.\n", argv[2]);
    }
    close(fd_in);
    close(fd_out);
    free(buf);
    return 0;
}
