#include <stdio.h>
#include <ctype.h>
#define MaxLineLen 4096

void urlEncode(char *text);

int main(){
    char line[MaxLineLen];
    char *ptr;

    while(fgets(line,MaxLineLen,stdin)){
        ptr = line;
        while(*ptr){
            if(!isdigit(*ptr) && !isalpha(*ptr) && (*ptr != '.') && (*ptr != '\n')){
                urlEncode(ptr);
            }
            else{
                printf("%c",*ptr);
            }
            ptr++;
        }
    }
    return 0;
}

void urlEncode(char *text){
    int hex1, hex2;
    int text1 = *text;
    char c1, c2;

    if(text1 < 0){  // 中文編碼為負數
        text1 += 256;
    }
    hex1 = text1 / 16;
    hex2 = text1 % 16;
    if(hex1 > 9){
        c1 = 'A' + hex1 - 10;
    }
    else{
        c1 = '0' + hex1;
    }
    if(hex2 > 9){
        c2 = 'A' + hex2 - 10;
    }
    else{
        c2 = '0' + hex2;
    }
    printf("%%%c%c",c1,c2);
}
