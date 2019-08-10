#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "../Graph/graph.h"
#include "../Dijkstra/dijkstra.h"

typedef struct{
    int id;
    char name[20];
    int count;
}sanpham;

typedef struct{
    char name[20];
    int id;
    sanpham s[10];
}khohang;

void readFileSanpham(FILE *fin1, sanpham S[], int *n);
void readFileKhohang(FILE *fin2, khohang K[], int *m, int n, Graph g);
void kiemKe(sanpham S[], khohang K[], int n, int m);
void kiemKeSp(Graph g, sanpham Sp[], khohang K[], int id, int kho);
void checkTime(Graph g, int id, int sl, int k1, int k2, khohang K[]);

int main(int argc, char *argv[]){

    if(argc == 1){
        printf("Thieu tham so dau vao\n");
        return 0;
    }

    int m, n;

    Graph g = creatGraph();
    FILE *fin1, *fin2;
    khohang K[10];
    sanpham Sp[10];

    // if((fin1 = fopen("sanpham.txt", "r")) == NULL){
    //     printf("Can not open file %s\n", argv[2]);
    //     return 0;
    // }
    // if((fin2 = fopen("khohang.txt", "r")) == NULL){
    //     printf("Can not open file %s\n", argv[2]);
    //     return 0;
    // }

    if(strcmp("-t", argv[1]) == 0){
        printf("C-Advance, HK20182\n");
        return 1;
    }

    if(strcmp("-s", argv[1]) == 0){
        if(argc != 3){
            printf("Thieu tham so dau vao\n");
            printf("%s -s <sanpham.txt>\n", argv[0]);
            return 0;
        }
        if((fin1 = fopen(argv[2], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        readFileSanpham(fin1, Sp, &n);
        for(int i = 0 ; i < n; i++){
            printf("%s %d\n", Sp[i].name, Sp[i].id);
        }
        return 1;
    }

    if(strcmp("-w", argv[1]) == 0){
        if(argc != 5){
            printf("Thieu tham so dau vao\n");
            return 0;
        }
        fin1 = fopen("sanpham.txt", "r");
        if((fin2 = fopen(argv[2], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        readFileSanpham(fin1, Sp, &n);
        readFileKhohang(fin2, K, &m, n, g);

        if(hasEdge(g, atoi(argv[3]), atoi(argv[4])) == 0){
            printf("-1\n");
        }else{
            int tmp = getEdgeValue(g, atoi(argv[3]), atoi(argv[4]));
            printf("%d km\n", tmp);
        }
        return 1;
    }

    if(strcmp("-a", argv[1]) == 0){
        if((fin1 = fopen(argv[3], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        if((fin2 = fopen(argv[2], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        readFileSanpham(fin1, Sp, &n);
        readFileKhohang(fin2, K, &m, n, g);
        kiemKe(Sp, K, n, m);
    }

    if(strcmp("-h", argv[1]) == 0){
        if(argc != 6){
            printf("Thieu tham so dau vao\n");
            return 0;
        }

        if((fin1 = fopen(argv[3], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        if((fin2 = fopen(argv[2], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        readFileSanpham(fin1, Sp, &n);
        readFileKhohang(fin2, K, &m, n, g);
        kiemKeSp(g, Sp, K, atoi(argv[4]), atoi(argv[5]));
    }

    if(strcmp("-g", argv[1]) == 0){
        if(argc != 8){
            printf("Thieu tham so dau vao\n");
            return 0;
        }
        if((fin1 = fopen(argv[3], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        if((fin2 = fopen(argv[2], "r")) == NULL){
            printf("Can not open file %s\n", argv[2]);
            return 0;
        }
        readFileSanpham(fin1, Sp, &n);
        readFileKhohang(fin2, K, &m, n, g);
        checkTime(g, atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), K);
    }


}

void readFileSanpham(FILE *fin1, sanpham S[], int *n){
    fscanf(fin1, "%d", n);
    for(int i = 0 ; i < *n; i++){
        fscanf(fin1, "%s%d", S[i].name, &S[i].id);
    }
}

void readFileKhohang(FILE *fin2, khohang K[], int *m, int n, Graph g){
    fscanf(fin2, "%d", m);
    // printf("m = %d\n", *m);
    for(int i = 0; i < *m; i++){
        fscanf(fin2, "%s%d", K[i].name, &K[i].id);
        // printf("%s-%d\n", K[i].name, K[i].id);
        addVertex(g, K[i].id, K[i].name);
        for(int j = 0; j < n; j++){
            fscanf(fin2, "%d%d", &K[i].s[j].id, &K[i].s[j].count);
        }
    }

    int id1, id2, k;
    double w;

    fscanf(fin2, "%d", &k);
    // printf("k = %d\n", k);
    for(int i = 0; i < k; i++){
        fscanf(fin2,"%d%d%lf", &id1, &id2, &w);
        addEdgeValue(g, id1, id2, w);
        addEdgeValue(g, id2, id1, w);
    }

}

void kiemKe(sanpham Sp[], khohang K[], int n, int m){
    for(int i = 0; i < m; i++){
        printf("%s\n", K[i].name);
        for(int j = 0; j < n; j++){
            printf("%s %d\n", Sp[j].name, K[i].s[j].count);
        }
        printf("-------\n");
    }
}

void kiemKeSp(Graph g, sanpham Sp[], khohang K[], int id, int kho){
    printf("%s\n", getVertex(g, kho));
    printf("%s %d\n", Sp[id-1].name, K[kho-1].s[id-1].count);
    int output[100];
    int tmp;
    tmp = outDegree(g, kho, output);
    printf("---Cac kho ke la: \n");
    for(int i = 0; i < tmp; i++){
        printf("%s\n", getVertex(g, output[i]));
        printf("%s %d\n", Sp[id-1].name, K[output[i]-1].s[id-1].count);
    }
}

void checkTime(Graph g, int id, int sl, int k1, int k2, khohang K[]){
    int tmp;
    if(sl <= K[k1-1].s[id-1].count){
        printf("Dat hang thanh cong, giao hang trong 30 phut\n");
        return;
    }
    if(sl > K[k1-1].s[id-1].count && sl <= (K[k1-1].s[id-1].count + K[k2-1].s[id-1].count)){
        printf("Dat hang thanh cong,");
        int p[10];
        double w = shortestPath_s_to_t(g, k1, k2, p, &tmp);
        double time = w/30 + 0.5;
        double x, y;
        x = modf(time, &y);
        printf("giao hang trong thoi gian %g gio %g phut\n", y, x*60);
        return;
    }
    if(sl > (K[k1-1].s[id-1].count + K[k2-1].s[id-1].count)){
        printf("Dat hang khong thanh cong\n");
        return;
    }
}

// void readFile(Graph g, char *filename)
// {
//     IS is = new_inputstruct(filename);
//     if (is == NULL)
//     {
//         printf("File fail!\n");
//         exit(1);
//     }

//     while (get_line(is) > 0)
//     {
//         int time;
//         const char s[2] = "-";
//         char *Vertex = (char *)malloc(sizeof(char) * strlen(is->fields[0]));
//         strcpy(Vertex, is->fields[0]);
//         int ID = vertexToNum(Vertex);
//         addVertex(g, ID, Vertex);

//         for (int i = 2; i < is->NF; i++)
//         {
//             char *first = strtok(is->fields[i], s);
//             int ID2 = vertexToNum(first);
//             time = atoi(strtok(NULL, s));
//             addEdge(g, ID2, ID, time);
//         }
//     }
// }