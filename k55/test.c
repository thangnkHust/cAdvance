#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxSize 100

int cutName(char name[]){
    char tmp[10];
    int j = 0;
    for(int i = 0; i < strlen(name); i++){
        if(name[i] != 'A'){
            tmp[j++] = name[i];
        }
    }
    return atoi(tmp);
}

void cutName1(char name[], int *id1, int *w){
    char *token; 
    int count = 0;
    token = strtok(name, "-");
    while(token != NULL){
        if(count == 0){
            *id1 = cutName(name);
            // strcpy(name1, token);
            count++;
        }else{
            *w = atoi(token);
        }
        token = strtok(NULL, "-");
    }
}

void readFile(FILE *fin){
    char str[maxSize];
    while(fgets(str, maxSize, fin) != NULL){
        int i = 0;
        int id, id1, w;
        int dem = 0;
        printf("%s\n", str);
        while(str[i] != '\n'){
            int j = 0;
            char tmp[10];
            if(str[i] == 'A'){
                // printf("%c\n", str[i]);
                // printf("%d\n", dem);
                if(dem == 0){
                    while(str[i] != ' '){
                        tmp[j] = str[i];
                        i++;
                        j++;
                    }
                    tmp[j] = '\0';
                    id = cutName(tmp);
                    printf("name %s-id %d: ", tmp, id);
                    // addVertex(g, id, tmp);
                }else{
                    while(str[i] != ' '){
                        tmp[j++] = str[i++];
                    }
                    cutName1(tmp, &id1, &w);
                    printf("id %d-weight %d", id1, w);
                    // addEdge(g, id1, id, w);
                }
                dem++;
            }
            i++;
        }
        printf("\n");
    }
}

int main(){

    // char name[] = "A10-10";
    // // int n = cutName(name);
    // // printf("%d\n", n);
    // char name1[10];
    // int n, w;
    // // cutName1(name, &n, &w, name1);
    // printf("id = %d, name = %s\n", n, name1);

    FILE *fin;
    if((fin = fopen("file.txt", "r")) == NULL){
        printf("Can not open file\n");
        return 0;
    }

    readFile(fin);

}