#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../Graph/graph.h"
#include "../Dijkstra/dijkstra.h"
#define maxSize 100

int menu(void);
void readFile(FILE *fin, Graph g);
int cutName(char name[]);
void cutName1(char name[], int *id1, double *w);

int main(){

    Graph g = creatGraph();
    FILE *fin;
    if((fin = fopen("file.txt", "r")) == NULL){
        printf("Can not open file\n");
        return 0;
    }

    int selec;
    char test[10];
    int id, count;
    int output[maxSize];
    int tmp = 0;
    double time;
    JRB node;

    do{

        if(tmp == 0) selec = menu();
        if(tmp == 1) selec = 2;
        if(tmp == -1) selec = 4;
        switch(selec){
            case 1:
                readFile(fin, g);
                // jrb_traverse(tmp, g.vertices){
                //     count++;
                // }    
                // printf("So cong viec la: %d", count);

                break;
            case 2:
                printf("Nhap cong viec: ");
                getchar();
                gets(test);
                id = cutName(test);
                node = jrb_find_int(g.vertices, id);
                if(node == NULL){
                    printf("Cong viec khong co trong chuong trinh\n");
                }else{
                    count = inDegree(g, id, output);
                    printf("Co %d cong viec ngay truoc\n", count);
                    printf("Cac cong viec la: ");
                    for(int i = 0; i < count; i++){
                        printf("%-5s", getVertex(g, output[i]));
                    }
                    printf("\n");
                }
                tmp = 0;
                break;
            case 3:
                printf("Ban co muon thuc hien lai cong viec 2 la nua khong(yes/no): ");
                getchar();
                gets(test);
                if(strcmp(test, "yes") == 0){
                    tmp = 1;
                }else{
                    if(strcmp(test, "no") == 0){
                        tmp = -1;
                    }else{
                        printf("Ban nhap sai cu phap\n");
                    }
                }
                break;
            case 4:
                topoSort(g, output, &count);
                for(int i = 0; i < count-1; i++){
                    printf("%s ==> ", getVertex(g, output[i]));
                }
                printf("%s\n", getVertex(g, output[count-1]));
                tmp = 0;
                break;
            case 5:
                printf("Nhap cong viec: ");
                getchar();
                gets(test);
                id = cutName(test);
                
                break;
            case 6:
                break;
            case 7:
                printf("Exit!!!\n");
                break;
        }

    }while(selec != 7);

}

int menu(){
    int selec;
    puts("1. So cong viec va so cung topo");
    puts("2. In thong bao tuong ung");
    puts("3. Co thuc hien lai cong viec 3 khong?");
    puts("4. In thu tu topo");
    puts("5. In thoi gian lam 1 cong viec");
    puts("6. Kiem tra do thi topo");
    puts("7. Exit!!!");
    printf("Your choice: ");
    scanf("%d", &selec);
    return selec;
}

void readFile(FILE *fin, Graph g){
    char str[maxSize];
    int count = 0, sum = 0;
    while(fgets(str, maxSize, fin) != NULL){
        int i = 0;
        int id, id1;
        double w;
        int dem = 0;
        while(str[i] != '\n'){
            int j = 0;
            char tmp[10];
            if(str[i] == 'A'){
                if(dem == 0){
                    while(str[i] != ' '){
                        tmp[j] = str[i];
                        i++;
                        j++;
                    }
                    tmp[j] = '\0';
                    id = cutName(tmp);
                    addVertex(g, id, tmp);
                    count++;
                }else{
                    while(str[i] != ' '){
                        tmp[j++] = str[i++];
                    }
                    cutName1(tmp, &id1, &w);
                    addEdgeValue(g, id1, id, w);
                    sum++;
                }
                dem++;
            }
            i++;
        }
    }
    printf("So cong viec la: %d\n", count);
    printf("so cung cua do thi topo la: %d\n", sum);
}

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

void cutName1(char name[], int *id1, double *w){
    char *token; 
    int count = 0;
    token = strtok(name, "-");
    while(token != NULL){
        if(count == 0){
            *id1 = cutName(name);
            // strcpy(name1, token);
            count++;
        }else{
            *w = atof(token);
        }
        token = strtok(NULL, "-");
    }
}

double countTime(Graph g, int id){
    int output[maxSize];
    double w;
}