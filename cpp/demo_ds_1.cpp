#include <iostream>

struct TreeNode {
    TreeNode *Left;
    TreeNode *Right;
    int Key;
};

enum OrderType { InOrder, PreOrder, PostOrder, LevelOrder};

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
    void Print(OrderType Order) const;
    void Destroy();

    //InsertNode(TreeNode *root, int key);
    // operators
    //void operator=(BTree& originalTree);


};

BTree::BTree()
{
    root = NULL;
}

BTree::~BTree()
{
    Destroy();
    root = NULL;
}

void BTree::Destroy()
{

}

bool BTree::IsEmpty() const
{
    bool ret = false;
    if(root) ret = true;
    return ret;
}

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
            InsertNode(root->Left, key);
        }
    }
}

void BTree::Add(int key) {
    InsertNode(root,key);
}

void BTree::Delete(int key) {


}

bool BTree::Find(int key) const
{
    bool ret = false;

    return ret;

}

void InOrderTraversal(TreeNode * root)
{
    if(root) {
        std::cout << " " << root->Key<< " " ;
        InOrderTraversal(root->Left);
        InOrderTraversal(root->Right);
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
}

int main() {

    std::cout << " Tree Demo" << std::endl;

    BTree BT;

    BT.Add(10);
    BT.Add(20);
    BT.Add(5);
    BT.Add(15);
    BT.Add(30);



    BT.Print(InOrder);

}
