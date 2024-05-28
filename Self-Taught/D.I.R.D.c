#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define flush fflush(stdin)

typedef struct node{
    int elem;
    struct node* Lchild;
    struct node* Rchild;
}nodetype,*TREE;

void Display(TREE);
int Input();
TREE Create(int);
void Insert(TREE*,int);
void Remove(TREE*,int);
void Delete(TREE*);

int main(){
    TREE ptr = NULL;
    int option = 0;
    int elem;
    
    while(1){
        system("cls");
        printf("===LINKED LIST TREE in C===\n");
        printf("[1] DISPLAY\n");
        printf("[2] INSERT\n");
        printf("[3] REMOVE\n");
        printf("[0] DELETE & EXIT\n");
        printf("Enter option number: ");
        flush;
        scanf("%d",&option);

        switch(option){
            case 1: 
            system("cls");
            printf("=====DISPLAY=====\n");
            printf("Tree in Inceasing order: ");
            (ptr!=NULL)? Display(ptr),printf("\n"):printf("TREE EMPTY\n");
            printf("Press enter to return--");
            flush;
            getch();
            printf("\n\n");
            break;

            case 2: 
            system("cls");
            printf("=====INSERT=====\n");
            elem = Input();
            Insert(&ptr,elem);
            printf("\n\n");
            break;

            case 3: 
            system("cls");
            printf("=====REMOVE=====\n");
            (ptr!=NULL)? elem = Input(),Remove(&ptr,elem):printf("TREE EMPTY");
            printf("\n\n");
            break;

            case 0: 
            Delete(&ptr);
            printf("=====PROGRAM EXITED=====\n");
            exit(0);
            break;
        }
        option = 0;
    }
    return 0;
}

void Display(TREE root){
    if(root != NULL){
        Display(root->Lchild);
        printf("[%d] ",root->elem);
        Display(root->Rchild);
    }
}

int Input(){
    int elem;
    printf("Input Element(int): ");
    flush;
    scanf("%d",&elem);

    return elem;
}

TREE Create(int elem){
    TREE root = (TREE)malloc(sizeof(struct node));
    if(!root){
        printf("Memory Error\n");
        return NULL;
    }
    root->elem = elem;
    root->Lchild = root->Rchild = NULL;
    return root;
}

void Insert(TREE* root,int elem){
    if(*root == NULL){
        *root = Create(elem);
    }else if(elem < (*root)->elem){
        Insert(&(*root)->Lchild,elem);
    }else{
        Insert(&(*root)->Rchild,elem);
    }
}

void Remove(TREE* root,int elem){
    if(*root == NULL){
         printf("Element not found.\n");
        return;
    }else if(elem < (*root)->elem){
        Remove(&(*root)->Lchild,elem);
    }else if(elem > (*root)->elem){
        Remove(&(*root)->Rchild,elem);
    }else{
        if ((*root)->Lchild == NULL && (*root)->Rchild == NULL) {//-------->Case 1: No child (leaf node)
            free(*root);
            *root = NULL;
        } else if ((*root)->Lchild == NULL) {//---------------------------->Case 2.1: One child (right child)
            TREE temp = *root;
            *root = (*root)->Rchild;
            free(temp);
        } else if ((*root)->Rchild == NULL) {//---------------------------->Case 2.2: One child (left child)
            TREE temp = *root;
            *root = (*root)->Lchild;
            free(temp);
        } else {//--------------------------------------------------------->Case 3: Two children
            // Find the minimum value node in the right subtree
            TREE temp = (*root)->Rchild;
            while (temp->Lchild != NULL) {
                temp = temp->Lchild;
            }
            // Replace root's value with temp's value
            (*root)->elem = temp->elem;
            // Delete the duplicate node in the right subtree
            Remove(&(*root)->Rchild, temp->elem);
        }
    }
}

void Delete(TREE* root){
    if(*root!= NULL){
        Delete(&(*root)->Lchild);
        Delete(&(*root)->Rchild);
        free(*root);
    }
}