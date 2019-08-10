// 1. Doc file luu vao mang dong
// 2. Dung qsort sap xep theo diem -> ten -> ho -> dem
    // sort(arr, size arr, sizeof, compare)
    // Viet ham compare dong thoi
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max 100

typedef struct{
    char ma[15], ho[15], dem[15], ten[15];
    struct{
        double toan, ly, hoa, tong;
    }diem;
}elementtype;

int menu(void);
void readFile(FILE *fin, elementtype *element, int *n, int (*compare)(void *x, void *y));
int intCompare(void *x, void *y);
void printList(elementtype *element, int n, double diemChuan);
void case3(elementtype *element, int n, double diemChuan);

int main(){

    int selec;
    FILE *fin;
    int n = 0;
    double diemChuan = 0;
    int case1 = 0;

    if((fin = fopen("../../file/diem.txt", "r")) == NULL){
        printf("Can't open file\n");
        return 0;
    }

    elementtype *element = (elementtype *)malloc(max * sizeof(elementtype));

    readFile(fin, element, &n, intCompare);

    do{

        selec = menu();
        switch(selec){
            case 1:
                printf("Ban hay nhap diem chuan: ");
                scanf("%lf", &diemChuan);
                case1 = 1;
                break;
            case 2:
                if(case1 == 0){
                    puts("Chua co diem chuan\nHay nhap lai");
                    break;
                }
                printList(element, n, diemChuan);
                break;
            case 3:
                case3(element, n, diemChuan);
                break;
            case 4:
                free(element);
                fclose(fin);
                puts("Thoat!!!");
                break;
            default:
                puts("Nhap sai cu phap");
                break;
        }

    }while(selec != 4);

}

int menu(){
    int selec;
    puts("==========MENU=========");
    puts("1.Nhap diem chuan");
    puts("2.In danh sach thi sinh trung tuyen");
    puts("3.Tim diem chuan");
    puts("4.Thoat");
    printf("Nhap lua chon: ");
    scanf("%d", &selec);
    return selec;
}

int intCompare(void *x, void *y){
    double m, n;
	m = ((elementtype *)x)->diem.tong;
	n = ((elementtype *)y)->diem.tong;
    if(m == n){
        if(strcmp(((elementtype *)x)->ten, ((elementtype *)y)->ten) == 0){
            if(strcmp(((elementtype *)x)->ho, ((elementtype *)y)->ho) == 0){
                return strcmp(((elementtype *)x)->dem, ((elementtype *)y)->dem);
            }
            return strcmp(((elementtype *)x)->ho, ((elementtype *)y)->ho);
        }
        return strcmp(((elementtype *)x)->ten, ((elementtype *)y)->ten);
    }
	if(n > m) return 1;
    return -1;
}

void readFile(FILE *fin, elementtype *element, int *n, int (*compare)(void *x, void *y)){
    fscanf(fin, "%d", n);
    for(int i = 0; i < *n; i++){
        fscanf(fin, "%s%s%s%s%lf%lf%lf", element[i].ma, element[i].ho, element[i].dem, element[i].ten, &element[i].diem.toan, &element[i].diem.ly, &element[i].diem.hoa);
        element[i].diem.tong = element[i].diem.toan + element[i].diem.ly +  element[i].diem.hoa;
    }
    qsort(element, *n, sizeof(elementtype), intCompare);
}

void printList(elementtype *element, int n, double diemChuan){
    printf("%-5s%-15s%-15s%-15s%-15s%-10s%-5s%-5s%-5s\n", "stt" ,"ma", "ho","dem", "ten", "tong", "toan", "ly", "hoa");
    int dem = 1;
    for(int i =0; i < n; i++){
        if(element[i].diem.tong >= diemChuan && element[i].diem.toan > 0 && element[i].diem.ly > 0 && element[i].diem.hoa > 0){
            printf("%-5d%-15s%-15s%-15s%-15s%-10g%-5g%-5g%-5g\n", dem, element[i].ma, element[i].ho, element[i].dem, element[i].ten, element[i].diem.tong, element[i].diem.toan, element[i].diem.ly, element[i].diem.hoa);
            dem++;
        }
    }
}

void case3(elementtype *element, int n, double diemChuan){
    int count = 0;
    printf("Nhap so luong thi sinh: ");
    scanf("%d", &count);
    // printf("Diem chuan la: %g\n", diemChuan);
    
    int tmp = 0;
    int tmp1 = 0;
    for(int i =0; i < n; i++){
        if( element[i].diem.toan > 0 && element[i].diem.ly > 0 && element[i].diem.hoa > 0 && tmp < count){
            tmp1 = i;
            tmp++;
        }
    }
    // printf("Diem chuan la: %g\n", element[tmp1].diem.tong);
    int temp = 0;
    if(element[tmp1].diem.tong == element[tmp1 + 1].diem.tong){
        temp = 1;
    }

    tmp = 0;
    int dem = 0;
    int tmp2 = 0;
    for(int i =0; i < n; i++){
        if(element[i].diem.toan > 0 && element[i].diem.ly > 0 && element[i].diem.hoa > 0 && tmp < count){
            if(temp == 1){
                if(element[i].diem.tong != element[tmp1].diem.tong){
                    dem++;
                    tmp2 = i;
                }
            }else{
                dem++;
                tmp2 = i;
            }
            tmp++;
        }
    }
    
    printf("Diem chuan la: %g\n", element[dem].diem.tong);
    printf("So thi sinh duoc tuyen la: %d\n", dem);
    printf("%-5s%-15s%-15s%-15s%-15s%-10s%-5s%-5s%-5s\n", "stt" ,"ma", "ho","dem", "ten", "tong", "toan", "ly", "hoa");

    tmp = 0;
    for(int i =0; i < n; i++){
        if(element[i].diem.toan > 0 && element[i].diem.ly > 0 && element[i].diem.hoa > 0 && tmp < count){
            if(temp == 1){
                if(element[i].diem.tong != element[tmp1].diem.tong){
                    printf("%-5d%-15s%-15s%-15s%-15s%-10g%-5g%-5g%-5g\n", tmp+1,  element[i].ma, element[i].ho, element[i].dem, element[i].ten, element[i].diem.tong, element[i].diem.toan, element[i].diem.ly, element[i].diem.hoa);
                }
            }else{
                printf("%-5d%-15s%-15s%-15s%-15s%-10g%-5g%-5g%-5g\n", tmp+1,  element[i].ma, element[i].ho, element[i].dem, element[i].ten, element[i].diem.tong, element[i].diem.toan, element[i].diem.ly, element[i].diem.hoa);
            }
            tmp++;
        }
    }

}