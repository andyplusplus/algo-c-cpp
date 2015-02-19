#include "treenode.h"

/*search for data in tree, and return the node*/
TreeNode* search(TreeNode* root, int data){
    if(root == 0 || root->data == data)
        return root;
    for(int i = 0; i < root->adjs; ++i){
        TreeNode* found = search(root->adj[i], data);
        if(found != 0)
            return found;
    }
    return 0;
}


int main(){
    return 0;
}
