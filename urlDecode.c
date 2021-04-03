#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MaxLineLen 4096

int checkFormat(char *text);

int main(){
    char line[MaxLineLen];
    char *ptr, *qtr, *last, *lineEnd;
    int hex1, hex2;
    unsigned char c;

    while(fgets(line,MaxLineLen,stdin)){
        if(!checkFormat(line)){ // 確認輸入是否合理
            printf("error format\n");
            continue;
        }

        ptr = line;
        last = line;
        lineEnd = line + strlen(line);

        while(*ptr){
            qtr = last;
            ptr = strchr(ptr,'%');
            if(ptr == NULL){
                while(qtr < lineEnd){
                    printf("%c",*qtr);
                    qtr++;
                }
                break;
            }
            else{
                while(qtr < ptr){   // 印出'%'前之文字
                    printf("%c",*qtr);
                    qtr++;
                }
                ptr++;
                if(isdigit(*ptr)){
                    hex1 = *ptr - '0';
                }
                else{
                    hex1 = *ptr - 'A' + 10; // A -> 10, B -> 11, ...
                }
                ptr++;
                if(isdigit(*ptr)){
                    hex2 = *ptr - '0';
                }
                else{
                    hex2 = *ptr - 'A' + 10;
                }
                c = hex1 * 16 + hex2;
                printf("%c",c);

                ptr++;
                last = ptr;
            }
        }
    }
    return 0;
}

int checkFormat(char *text){
    char *ptr = text;
    while(ptr){
        ptr = strchr(ptr,'%');
        if(ptr){
            ptr++;
            if(!isdigit(*ptr) && !(*ptr >= 'A' && *ptr <= 'F')){
                return 0;
            }
            ptr++;
            if(!isdigit(*ptr) && !(*ptr >= 'A' && *ptr <= 'F')){
                return 0;
            }
            ptr++;
        }
    }
    return 1;
}
