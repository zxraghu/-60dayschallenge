#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node * left;
    struct Node * right;
};

typedef struct Node Node;

Node* Root = NULL;

Node * new_node(int element)
{
    Node*mem = (Node*)malloc(sizeof(Node));
    mem->data = element;
    mem->left = NULL;
    mem->right = NULL;
    return mem;
}

void checkit(Node* Root)
{
    if(Root != NULL) {
        checkit(Root->left);
        printf("%d\n", Root->data);
        checkit(Root->right);
    }
}
        
Node* insert(Node*Root_temp,int element)
{
    if(Root_temp == NULL)
    {
        return (Root_temp = new_node(element));
    }
    else if(Root_temp->data > element)
    {
        Root_temp->left = insert(Root_temp->left, element);
    }
    else
    {
        Root_temp->right = insert(Root_temp->right, element);
    }
    return Root_temp;
}
        
int main()
{
    int i = 0;
    int array[10] = {55,3,65,67,22,85,43,33,45,98};
    
    Root = new_node(200);
    
    for(i = 0; i < 10; i++)
    {
        insert(Root, array[i]);
    }
    
    checkit(Root);
    
    return 0;
}

