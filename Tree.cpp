#include <iostream>

using namespace std;
struct Node
{
    int data;
    Node *left;
    Node *right;
};
Node* CreateNode(int data)
{
    Node *temp = new Node();
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
void InsertNode(Node *&root, int data)
{
    if(root == NULL)
    {
        root = CreateNode(data);
        return;
    }
    else if(data <= root->data)
    {
        InsertNode(root->left,data);
    }
    else
    {
        InsertNode(root->right,data);
    }

}
void Search(Node *root, int x)
{
    if(root == NULL)
    {
        cout<<"Not Found";
    }
    else if(x == root->data)
    {
        cout<<"Found";
    }
    else if(x < root->data)
    {
        Search(root->left,x);
    }
    else{
        Search(root->right,x);
    }
}
int Count(Node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        return 1+Count(root->left) + Count(root->right);
    }
}
int Min(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else if(root ->left == NULL)
    {
        return root->data;
    }
    else
    {
        return Min(root->left);
    }
}
int Max(Node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else if(root ->right == NULL)
    {
        return root->data;
    }
    else
    {
        return Max(root->right);
    }
}
void DFSPreOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    cout<<root->data<<"\n";
    DFSPreOrder(root->left);
    DFSPreOrder(root->right);
}
void DFSInOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    DFSInOrder(root->left);
    cout<<root->data<<"\n";
    DFSInOrder(root->right);
}
void DFSPostOrder(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    DFSPostOrder(root->left);
    DFSPostOrder(root->right);
    cout<<root->data<<"\n";
}
int Sum(Node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    return root->data + Sum(root->left) + Sum(root->right);
}
int main()
{
    Node *tree = CreateNode(20);
    InsertNode(tree,5);
    InsertNode(tree,10);
    InsertNode(tree,15);
    InsertNode(tree,2);
    InsertNode(tree,6);
    DFSPreOrder(tree);
    cout<<Sum(tree);

    return 0;
}
