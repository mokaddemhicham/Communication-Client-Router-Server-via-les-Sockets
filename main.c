#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *crc(char str[16]){

    char *px = (char*)malloc(sizeof(char)*19);
    for(int i = 0; i < 16; i++){
        px[i] = str[i];
    }
    for(int i = 16; i < 19; i++){
        px[i] = '0';
    }
    
    char gx[4] = "1101";
    
    char t1[4];
    char *tr = (char*)malloc(sizeof(char)*3);

    for(int i = 0; i < 4; i++){
        t1[i] = px[i];
    }
    for(int i = 4; i < 19; i++){
        for(int j = 0; j < 3; j++){
            if(t1[j] == gx[j]){
                tr[j] = '0';
            }else{
                tr[j] = '1';
            }
        }
        if(tr[0] == '1'){
            for(int i = 0; i < 4; i++){
                t1[i] = tr[i];
            }
        }
        t1[0] = tr[1];
        t1[1] = tr[2];
        t1[2] = tr[3];
        t1[3] = tr[i];
    }
    return tr;
}


void main(){
    
    for(int i = 0; i < 4; i++){
        printf("%c", crc("1010101010101101")[i]);
    }
    printf("\n");

}