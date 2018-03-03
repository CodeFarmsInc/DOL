// test of BINARY TREE and using free lists at the same time
/* Example:
                                  10
                               9      11
                       5                        16
                   1       6             12
                0    3        8             14
                    2 4      7             13 15
*/

#include <stdio.h>
#define ZZmain
#include "zzincl.h"

class Node { 
    int i;
    ZZ_EXT_Node
public:
    Node *newObj(int ii){Node *p; ZZ_OBJECT_NEW(Node,p); 
        p->i=ii; return p;} // from the list, replaces new() and the constructor
    static void delObj(void *p){ ZZ_OBJECT_FREE(Node,(Node*)p); } // delete list
    static void trueDelete(void *p){delete (Node*)p;}              // hides delete
    int val(){return i;}
}aNode;

ZZ_HYPER_BINARY_TREE(binTree,Node);

int main(){
    Node *np, *root;

    Node* n10=aNode.newObj(10);
    root=n10;
    Node* n9=aNode.newObj(9); binTree.addL(n10,n9);
    Node* n5=aNode.newObj(5); binTree.addL(n9,n5);
    Node* n1=aNode.newObj(1); binTree.addL(n5,n1);
    Node* n0=aNode.newObj(0); binTree.addL(n1,n0);
    Node* n3=aNode.newObj(3); binTree.addR(n1,n3);
    Node* n2=aNode.newObj(2); binTree.addL(n3,n2);
    Node* n4=aNode.newObj(4); binTree.addR(n3,n4);
    Node* n6=aNode.newObj(6); binTree.addR(n5,n6);
    Node* n8=aNode.newObj(8); binTree.addR(n6,n8);
    Node* n7=aNode.newObj(7); binTree.addL(n8,n7);
    Node* n11=aNode.newObj(11); binTree.addR(n10,n11);
    Node* n16=aNode.newObj(16); binTree.addR(n11,n16);
    Node* n12=aNode.newObj(12); binTree.addL(n16,n12);
    Node* n14=aNode.newObj(14); binTree.addR(n12,n14);
    Node* n15=aNode.newObj(15); binTree.addR(n14,n15);
    Node* n13=aNode.newObj(13); binTree.addL(n14,n13);

    binTree_iterator it;

    it.start(n10);
    ITERATE(it,np){  // traversing all nodes left-to-right
        printf("%d ",np->val());
    }
    printf("\n");

    it.start(n9);
    RETRACE(it,np){  // traversing only leaves right-to-left
        if(binTree.isLeaf(np))printf("%d ",np->val());
    }
    printf("\n");

    np=binTree.replaceByRightSubtree(n5,1,Node::delObj);
    if(np)root=np;

    // print the resulting tree
    it.start(root);
    ITERATE(it,np){  // traversing subnodes of n10 left-to-right
        printf("%d ",np->val());
    }
    printf("\n");

    np=binTree.replaceByLeftSubtree(n10,0,Node::delObj);
    if(np)root=np;

    // print the resulting tree
    it.start(root);
    ITERATE(it,np){  // traversing subnodes of n10 left-to-right
        printf("%d ",np->val());
    }
    printf("\n");

    binTree.delSub(root,Node::delObj); // dismantle and destroy remaining tree
    return 0;
}
#include "zzfunc.c"
