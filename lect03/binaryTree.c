#include <stdio.h>
#include <stdlib.h>

typedef int elementtype;

typedef struct node{
    elementtype element;
    struct node *left;
    struct node *right;
}node;

typedef node *tree;

void initalize(tree *T){
    *T = NULL;
}

tree makeNewNode(elementtype e){
    tree new = (node *)malloc(sizeof(node));
    new->element = e;
    new->left = NULL;
    new->right = NULL;
    return new;
}

int isLeaf(tree T){
    if(T != NULL){
        return (T->left == NULL && T->right == NULL);
    }
    return -1;
}

int countTree(tree T){
    if(T == NULL) return 0;
    return 1 + countTree(T->left) + countTree(T->right);
}

tree creatFrom2(tree L, tree R, elementtype e){
    tree new = makeNewNode(e);
    new->left = L;
    new->right = R;
    return new;
}

void insertMostLeft(tree *T, elementtype e){
    tree new = makeNewNode(e);
    if(*T == NULL) *T = new;
    else{
        tree tmp = *T;
        while(tmp->left != NULL){
            tmp = tmp->left;
        }
        tmp->left = new;
    }
}

void insertMostRight(tree *T, elementtype e){
    tree new = makeNewNode(e);
    if(*T == NULL) *T = new;
    else{
        tree tmp = *T;
        while(tmp->right != NULL){
            tmp = tmp->right;
        }
        tmp->right = new;
    }
}

int height(tree T){
    if(T == NULL) return 0;
    int h1 = height(T->left);
    int h2 = height(T->right);
    int maxH = h1 > h2 ? h1 : h2;
    return maxH + 1;
}

int countLeaf(tree T){
    static int leaf = 0;
    if(T != NULL){
        if(isLeaf(T)) leaf++;
        else{
            leaf = countLeaf(T->left) + countLeaf(T->right);
        }
    }
    return leaf;
}

void preOder(tree T){
    if(T != NULL){
        printf("%d ", T->element);
        preOder(T->left);
        preOder(T->right);
    }
}


int main(){

    tree T;
    initalize(&T);
    for(int i = 1; i <= 10; i++){
        if(i%2 == 1){
            insertMostRight(&T, i);
        }else{
            insertMostLeft(&T, i);
        }
    }

    preOder(T);
    printf("\n");

    printf("height = %d\n", height(T));
    printf("count node = %d\n", countTree(T));

}

