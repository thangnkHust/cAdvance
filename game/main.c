#include <stdio.h>
#include <string.h>

typedef struct{
    char question[1000];
    char answer[10];
}data;

int main(){



}

void readFile(FILE *fin, data d[100]){
    char str[1000];
    int i = 0;
    while(fgets(str, 1000, fin) != NULL){
        if(strcmp(str, " ") == 0){
            i++;
        }else{
            
        }
        
    }
}