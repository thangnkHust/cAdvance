#include <stdio.h>
#include <stdlib.h>

typedef int keyType;

typedef struct node{
    keyType key;
    struct node *left;
    struct node *right;
}node;

typedef node *tree;

void initalize(tree *T){
    *T = NULL;
}

tree makeNewNode(keyType k){
    tree new = (node *)malloc(sizeof(node));
    new->key = k;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int isLeaf(tree T){
    if(T != NULL){
        return (T->left == NULL & T->right == NULL);
    }
    return -1;
}

int countTree(tree T){
    if(T == NULL) return 0;
    return 1 + countTree(T->left) + countTree(T->right);
}

void insertNode(tree *T, keyType k){
    if(*T == NULL){
        *T = makeNewNode(k);
        // *T = (node *)malloc(sizeof(node));
        // (*T)->key = k;
        // (*T)->left = NULL;
        // (*T)->right = NULL;
    }else{
        if(k < (*T)->key) insertNode(&((*T)->left), k);
        else if(k > (*T)->key) 
            insertNode(&((*T)->right), k);
    }
}

tree search(tree T, keyType k){
    if(T == NULL) return NULL;
    if(k == T->key) return T;
    if(k < T->key) return search(T->left, k);
    return search(T->right, k);
}

keyType deleteMin(tree *T){
    keyType k;
    if((*T)->left == NULL){
        k = (*T)->key;
        *T = (*T)->right;
        return k;
    }
    return deleteMin(&(*T)->left);
}

void deleteNode(tree *T, keyType x){
    if(*T != NULL){
        if( x < (*T)->key) deleteNode(&(*T)->left, x);
        else{
            if(x > (*T)->key) deleteNode(&(*T)->right, x);
            else if((*T)->left == NULL && (*T)->right == NULL) *T = NULL;
            else if((*T)->right == NULL) *T = (*T)->left;
            else if((*T)->left == NULL) *T = (*T)->right;
            else (*T)->key = deleteMin(&(*T)->right);
        }
    }
}

void inOder(tree T){
    if(T != NULL){
        inOder(T->left);
        printf("%d ", T->key);
        inOder(T->right);
    }
}

void freeTree(tree *T){
    (*T) = NULL;
}


int main(){

    int a[11] = {43, 31, 64, 20, 28, 33, 40, 56, 89, 47, 59};
    tree T;
    node *tmp = NULL;
    int n;

    initalize(&T);

    for(int i = 0; i < 11; i++){
        // printf("a[i] = %d\n", a[i]);
        insertNode(&T, a[i]);
    }
    // printf("T = %d\n", T->right->right->key);

    printf("Nhap so can tim: ");
    scanf("%d", &n);
    tmp = search(T, n);

    if( tmp != NULL ) printf("Co phan tu %d trong cay\n", n);
    else printf("Khong co trong cay\n");

    deleteNode(&T, 30);

    inOder(T);
    printf("\n");

    freeTree(&T);

    inOder(T);
    printf("\n");        

}



