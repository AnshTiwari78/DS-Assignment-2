#include<iostream>
#include<cmath>
using namespace std;
//create a Node class for Binary Tree---------------
class Node{
public:
    int value;
    Node* left;
    Node* right;
    //constructor-------------
    Node(int val){
        value=val;
        left=nullptr;
        right=nullptr;
    }
};
//binary tree class with operation-------------
class BinaryTree{
public:
    //recursive function to build tree from user input---------
    Node* buildTree(){
        int value;
        cout<<"Enter value (-1 for NULL): ";
        cin>>value;
        //base case:if value is -1,return null----------------
        if(value==-1){
            return nullptr;
        }
        //create new node with the value-------------------
        Node* root=new Node(value);
        //recursively build left subtree-------------------
        cout<<"Enter left child of "<<value<<":\n";
        root->left=buildTree();
        //recursively build right subtree------------------------
        cout<<"Enter right child of "<<value<<":\n";
        root->right=buildTree();
        return root;
    }
    //function to check if two trees are magical-----------------
    bool magical(Node* root1,Node* root2,int& isMagical)
    {
        //base case: both trees are empty---------
        if(!root1&&!root2){
            return true;
        }
        //if one tree is empty and other is not, trees are not magical---------
        if(!root1||!root2){
            isMagical=0;
            return false;
        }
        //calculate sum of children for both trees
        int leftSum1=root1->left?root1->left->value:0;
        int rightSum1=root1->right?root1->right->value:0;
        int leftSum2=root2->left?root2->left->value:0;
        int rightSum2=root2->right?root2->right->value:0;
        // Check if sum of children are equal in both trees-----------
        if(leftSum1+rightSum1!=leftSum2+rightSum2){
            isMagical=0;
        }
        
        //calculate difference between absolute differences
        int diff1=abs(leftSum1-root1->value)-abs(rightSum1-root1->value);
        int diff2=abs(leftSum2-root2->value)-abs(rightSum2-root2->value);
        
        //check if differences are equal
        if(diff1!=diff2){
            isMagical=0;
        }
        //recursively check left and right subtrees
        magical(root1->left,root2->left,isMagical);
        magical(root1->right,root2->right,isMagical);
        
        return isMagical;
    }
    //function to free memory used by tree
    void freeTree(Node* root){
        if(!root)return;
        //recursively free left and right subtrees
        freeTree(root->left);
        freeTree(root->right);
        //delete current node
        delete root;
    }
};
int main(){
    BinaryTree tree;
    //build first tree
    cout<<"Build Tree 1:\n";
    Node* root1=tree.buildTree();
    //build second tree
    cout<<"Build Tree 2:\n";
    Node* root2=tree.buildTree();
    //check if trees are magical
    int isMagical=1;
    tree.magical(root1,root2,isMagical);
     //display result
    if(isMagical){
        cout<<"The trees are magical.\n";
    }
    else{
        cout<<"The trees are not magical.\n";
    }
    //free memory
    tree.freeTree(root1);
    tree.freeTree(root2);
    return 0;
}