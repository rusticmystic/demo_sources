#include <iostream>

struct TreeNode {
    TreeNode *Left;
    TreeNode *Right;
    int Key;
};

enum OrderType { InOrder, PreOrder, PostOrder, LevelOrder };

class BTree {
    TreeNode *root;
public:
    // default
    BTree();
    ~BTree();
    //BTree(const BTree&);

    // methods
    bool IsEmpty() const;
    void Add(int key);
    void Delete(int key);
    bool Find(int key) const;
    int  Height();
    // int getLevel(key)
    // int LevelOrderByQueue()
    int  NodesAtLevel(int Level);
    void Print(OrderType Order) const;
    void Destroy(TreeNode *&root);

    // InsertNode(TreeNode *root, int key);
    // operators
    // void operator=(BTree& originalTree);
};

BTree::BTree()
{
    root = NULL;
}

BTree::~BTree()
{
	Print(LevelOrder);
    Destroy(root);
    //root = NULL;
    Print(LevelOrder);
}

void BTree::Destroy(TreeNode *&root)
{
if(root) {
        Destroy(root->Left);
        Destroy(root->Right);
        TreeNode *temp = root;
        delete temp;
        temp=NULL;
    }
}

bool BTree::IsEmpty() const
{
    bool ret = false;
    if(root) ret = true;
    return ret;
}

/* Node this recursive calling a function which passes pointer in cpp.
 * We have to pass the POINTER BY REFERENCE to be able to change the pointer,
 * rather than changing its local copy
 * */
void InsertNode(TreeNode *&root, int key)
{
    if(!root) {
        root = new TreeNode;
        root->Key = key;
        root->Left = NULL;
        root->Right = NULL;
    } else
    {
        if(key < root->Key) {
            InsertNode(root->Left, key);
        }
        else {
            InsertNode(root->Right, key);
        }
    }
}

void BTree::Add(int key) {
    InsertNode(root,key);
}

void BTree::Delete(int key) {


}

#define MAX(_x,_y) (_x-_y)>0 ? _x :_y

int TreeHeight(TreeNode *&root)
{
    if(!root) return 0;
    return MAX(TreeHeight(root->Left),TreeHeight(root->Right))+1;
}

int  BTree::Height() {
    int x=TreeHeight(root);
    return x;
}

void LevelNodes(TreeNode *root, int level) {
    if(!root) return;
    if(level==1) {
        std::cout << " " << root->Key << " ";
    }
    LevelNodes(root->Left, level-1);
    LevelNodes(root->Right,level-1);
    std::cout << "  ";
}

int  BTree::NodesAtLevel(int Level) {
    std::cout << "\nNodes at Level \n" << std::endl;
    LevelNodes (root,Level);
    return 0;
}

bool SearchTree(TreeNode *root,int key, int &ret)
{
    if (root) {
        if (root->Key > key)
        {
            std::cout << root->Key << std::endl;
            SearchTree (root->Left,key, ret);
        } else if (root->Key < key)
        {
            std::cout << root->Key << std::endl;
            SearchTree(root->Right,key, ret);
        } else if (root->Key == key)
        {
            std::cout << root->Key << std::endl;
            ret = true;
            return true;
        }
    }
    std::cout << root << std::endl;
    return false;
}

bool BTree::Find(int key) const
{
    int ret=false;
    SearchTree(root, key,ret);
    return ret;
}

void InOrderTraversal(TreeNode * root)
{
    if(root) {
        InOrderTraversal(root->Left);
        std::cout << " " << root->Key<< " " ;
        InOrderTraversal(root->Right);
    }
}

void PreOrderTraversal(TreeNode * root)
{
    if(root) {
        std::cout << " " << root->Key<< " " ;
        PreOrderTraversal(root->Left);
        PreOrderTraversal(root->Right);
    }
}

void PostOrderTraversal(TreeNode * root)
{
    if(root) {
        PostOrderTraversal(root->Left);
        PostOrderTraversal(root->Right);
        std::cout << " " << root->Key<< " " ;
    }
}

void LevelOrderTraversal(TreeNode * root)
{
    if(root) {
        int Height = TreeHeight(root);
        for (int Level=1; Level <=Height; Level++)
        {
            LevelNodes (root,Level);
            std::cout << " \n" << std::endl;
        }
    }
}

void BTree::Print(OrderType Order) const
{
    if(Order ==InOrder)
    {
        std::cout << " InOrder" << std::endl;
        InOrderTraversal(root);
        std::cout << std::endl;
    }
    else if(Order == PostOrder) {
        std::cout << " PostOrder" << std::endl;
        PostOrderTraversal(root);
        std::cout << std::endl;

    }
    else if(Order == PreOrder) {
        std::cout << " PreOrder" << std::endl;
        PreOrderTraversal(root);
        std::cout << std::endl;

    }
    else if(Order == LevelOrder) {
        std::cout << " LevelOrder" << std::endl;
        LevelOrderTraversal(root);
        std::cout << std::endl;
    }
}

int main() {

    std::cout << " Tree Demo" << std::endl;
    {
    BTree BT;

    BT.Add(10);
    BT.Add(20);
    BT.Add(5);
    BT.Add(15);
    BT.Add(30);



    BT.Print(InOrder);
    BT.Print(LevelOrder);
    std::cout << " Tree height " << BT.Height();
    BT.NodesAtLevel(1);

    int searchfor = 14;
    std::string found = BT.Find(searchfor) ? "true" : "false";
    std::cout << "\n Is " << searchfor << " in Tree :"<< found << std::endl;

   } 
     
    return 0;
}
