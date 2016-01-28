#include <stdio.h>
#include <stdlib.h>

/** Structures **/

typedef struct node {
    struct node *next;
    int key;
} Node;

struct Tree {
    struct Tree *left;
    struct Tree *right;
    int key;
};

typedef struct node Node;
typedef struct Tree Tree;

/**** List *****/
Node * getLastNode(Node *List);
int delNode(Node* List, int key);
int showContent(Node *List);
int sortList(Node * List);
int reverseList(Node  * List);
Node * getLastNode(Node *List);
Node * getFirstNode(Node *List);

int showContent(Node *List) {
    Node *Iter = List;
    if(List) {
        while(Iter->next!=NULL) {
            printf(" %d ",Iter->key);
            Iter = Iter->next;
        }
        printf(" %d ",Iter->key);
        printf(" \n");
    }
}

Node * addNode(Node* List, int key)
{
    Node *temp;
    temp = (Node *)malloc(sizeof(Node));
    temp->key = key;
    temp->next = NULL;

    if(List) {
        Node *N = getLastNode(List);
        N->next = temp;
    }
    else {
        List = temp;
        //printf("First Node = %p\n",temp);
    }
    return temp;
}

Node * searchNode(Node* List, int key) {
    Node * Iter = List;
    while(List->next!=NULL) {
        if(List->key==key) {
            return List;
        }
    }
    return NULL;
}

int delNode(Node* List, int key) {
    Node * Iter = List;
    Node * Prev = List;
    Node * temp;

    if(List) {
        //single element case
        {
            if(List->key==key)
                List=NULL;
        }

        while(Iter->next!=NULL) {
            if(Iter->next->key==key)
            {
                Prev = Iter;
                break;

            }
            Iter = Iter->next;
        }

        temp = Iter->next;
        Prev->next = temp->next;
        free(temp);

    }

}

int sortList(Node * List) {}
int reverseList(Node  * List) {}

Node * getLastNode(Node *List) {
    Node * Iter = List;
    while(Iter->next!=NULL)
    {

        Iter = Iter->next;
    };
    //printf(" %d \n",Iter->key);
    return Iter;
}

Node * getFirstNode(Node *List) {

}

/** Binary Tree****/

int addElement(Tree * root, int key);
int removeElement(Tree * root, int key);
int Inorder(Tree *root);
int Preorder(Tree *root);
int Mirror(Tree *root);
int showTreeContent(Tree *root);


/***Heap******/

typedef Node List;

int main(int arg, char * argv[]) {

    // Create a List
    List *MyList;
    MyList=addNode(MyList,10);
    printf("List Demo %p\n",MyList->next);
    addNode(MyList,8);
    addNode(MyList,4);
    addNode(MyList,7);
    addNode(MyList,9);
    addNode(MyList,12);

    printf("List Demo %p\n",MyList);
    showContent(MyList);
    delNode(MyList, 9);
    delNode(MyList, 4);
    showContent(MyList);


}
