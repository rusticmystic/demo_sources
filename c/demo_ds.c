/** This sample program contains linked list and Binary tree implementation. Features: Mirror, Search, Reverese etc **/

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
int    delNode(Node* List, int key);
int    showContent(Node *List);
int    sortList(Node * List);
Node * reverseList(Node  * List);
Node * getLastNode(Node *List);
Node * getFirstNode(Node *List);
int    FreeList(Node * List);

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

Node * reverseList(Node  * List)
{
    Node * Iter = List;
    Node * Prev = NULL;
    Node * temp;
    Node *NewHead;

    if(List) {
        while(Iter->next!=NULL) {
            temp = Iter->next;
            Iter->next = Prev;
            Prev = Iter;
            Iter = temp;
        }
    }
    List->next=NULL;
    Iter->next = Prev;
    return Iter;
}

int sortList(Node * List) {

}

Node * getLastNode(Node *List) {
    Node * Iter = List;
    if(!Iter) return;
    while(Iter->next!=NULL)
    {

        Iter = Iter->next;
    };
    //printf(" %d \n",Iter->key);
    return Iter;
}

Node * getFirstNode(Node *List) {

}

int    FreeList(Node * List) {
    Node * temp = List;
    Node *Iter = List;

    while(Iter!=NULL) {
        temp = Iter;
        Iter = Iter->next;
        printf(" Free %d\n",temp->key);
        free(temp);
    }
    printf("List %p",List);
}

/** Binary Tree****/

//	int addElement(Tree * root, int key);
int removeElement(Tree * root, int key);
int Inorder(Tree *root);
int Preorder(Tree *root);
int Mirror(Tree *root);
int showTreeContent(Tree *root);

Tree * addElement(Tree * root, int key)
{
    Tree *temp;

    if(!root) {
        // This is the root node
        printf("Adding  %d \n", key);
        temp = (Tree *)malloc(sizeof(Tree));
        temp->key = key;
        temp->right=NULL;
        temp->left=NULL;
        //root = temp;
        return temp;

    }
    else {
        //Find the location

        if(root->key < key) {
            if(root->right) {
                addElement (root->right,key);
            }
            else {
                root->right = addElement (root->right,key);
            }

        } else {
            if(root->left) {
                addElement (root->left,key);
            }
            else {
                root->left = addElement (root->left,key);
            }
        }
    }
}

int Inorder(Tree *root) {
    if(root) {
        Inorder(root->left);
        printf(" %d ",root->key);
        Inorder(root->right);
    }
}

int Preorder(Tree *root) {
    if(root) {
        printf(" %d ",root->key);
        Preorder(root->left);
        Preorder(root->right);

    }
}

int Mirror(Tree *root) {
    Tree * temp;
    Tree *Left=NULL;
    Tree *Right=NULL;

    if(root) {
        //swap the left and right nodes

        if(root->left && root->right) {
            temp = (root->left);
            (root->left) = (root->right);
            (root->right) = temp;
        }

        Mirror(root->left);
        Mirror(root->right);
    }
}

int searchElement(Tree * root, int key) {
    int ret = 0;
    if(root) {
        if(root->key < key) {
            ret = searchElement(root->left,key);
        } else if(root->key > key) {
            ret = searchElement(root->right,key);
        }
        else if(root->key==key) {
            ret = 1;
        }
    }
    return ret;
}

#define MAX(_x,_y) (_x-_y)>0 ? _x :_y
 
int Height(Tree * root) {
	
	if(!root) return 0;
	
	if(root){
	return MAX(Height(root->left),Height(root->right))+1;
	}
	
}

// Level order Traversal with DFS.
// without queue.
int LevelNodes(Tree *root, int level)
{
	if(!root) return;
	if(level==1) {
		printf(" %d ", root->key);
		}
	   LevelNodes(root->left, level-1);
	   LevelNodes(root->right,level-1);
	  
	}

int LevelOrder(Tree *root)
{
	int i;
	if(!root) return;
	int maxLevels = Height(root);
	
	for(i=1;i<=maxLevels;i++)
	{
	LevelNodes(root,i);	
	printf("\n");	
	}
}

/*** MAX Heap using a tree ******/

typedef Node List;

int main(int arg, char * argv[]) {

    // Create a List

    List *MyList=NULL;
    int SearchFor = 0;
    MyList=addNode(MyList,10);
    //    printf("List Demo %p\n",MyList->next);

    // Add Data to the Nodes
    addNode(MyList,8);
    addNode(MyList,4);
    addNode(MyList,7);
    addNode(MyList,9);
    addNode(MyList,12);

    //    printf("List Demo %p\n",MyList);

    // Display
    showContent(MyList);
    MyList=reverseList(MyList);

    // printf("List Demo %p\n",MyList);

    // Delete Nodes
    //delNode(MyList, 9);
    //delNode(MyList, 4);

    // Display
    showContent(MyList);

    FreeList(MyList);
    printf("\n List Freed \n");
    showContent(MyList);

    // Tree
    Tree *MyTree = NULL;

    // addElement(&MyTree,10);
    MyTree = addElement(MyTree,10);
    addElement(MyTree,5);
    addElement(MyTree,30);
    addElement(MyTree,4);
    addElement(MyTree,8);
    addElement(MyTree,28);
    addElement(MyTree,42);


    printf("InOrder \n");
    Inorder(MyTree);

    printf("\n PreOrder \n");
    Preorder(MyTree);
     
    printf("\n LevlOrder \n");

    LevelOrder(MyTree);

    printf("\n Inrder Mirror \n");
    Mirror(MyTree);
    Inorder(MyTree);
    printf("\n LevlOrder \n");

    LevelOrder(MyTree);

    //search for
    SearchFor = 8;
    printf("\n %d in Tree: %s\n",SearchFor,searchElement(MyTree,SearchFor) ? "TRUE" :"FALSE");

    printf("\n\nHeight of a Tree %d\n",Height(MyTree));
     
    return 0;
}
