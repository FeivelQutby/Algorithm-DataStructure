#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

TreeNode *create_node(int data)
{
    TreeNode *new_node = calloc(1, sizeof(TreeNode));
    new_node->data = data;
    return new_node;
}

TreeNode *find_min_node(TreeNode *node)
{
    while (node->left != NULL)
    {
        node = node->left;
    }
    return node;
}

TreeNode *deleteNode(TreeNode *root, int data)
{
    if (root == NULL)
    {
        return root;
    }
    else if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else
    {

        if (root->left == NULL)
        {
            TreeNode *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            TreeNode *temp = root->left;
            free(root);
            return temp;
        }

        // Case 2: Two children
        TreeNode *min_right = find_min_node(root->right);
        root->data = min_right->data;
        root->right = deleteNode(root->right, min_right->data);
    }
    return root;
}

void insert_node(TreeNode **root_ptr, int data)
{
    TreeNode *new_node = create_node(data);
    if (*root_ptr == NULL)
    {
        *root_ptr = new_node;
        return;
    }
    TreeNode *current_node = *root_ptr;
    while (1)
    {
        if (data < current_node->data)
        {
            if (current_node->left == NULL)
            {
                current_node->left = new_node;
                break;
            }
            else
            {
                current_node = current_node->left;
            }
        }
        else if (data > current_node->data)
        {
            if (current_node->right == NULL)
            {
                current_node->right = new_node;
                break;
            }
            else
            {
                current_node = current_node->right;
            }
        }
        else
        {
            free(new_node);
            break;
        }
    }
}

void inorder_traversal(const TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    inorder_traversal(root->left);
    printf("%d ", root->data);
    inorder_traversal(root->right);
}

void preorder_traversal(const TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    printf("%d ", root->data);
    preorder_traversal(root->left);
    preorder_traversal(root->right);
}

void postorder_traversal(const TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    postorder_traversal(root->left);
    postorder_traversal(root->right);
    printf("%d ", root->data);
}

void free_tree(TreeNode *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main()
{
    TreeNode *root = NULL;

    insert_node(&root, 50);
    insert_node(&root, 30);
    insert_node(&root, 70);
    insert_node(&root, 20);
    insert_node(&root, 40);
    insert_node(&root, 60);
    insert_node(&root, 80);

    printf("Base Tree\n");
    printf("Preorder  : ");
    preorder_traversal(root);
    printf("\n");
    printf("Inorder   : ");
    inorder_traversal(root);
    printf("\n");
    printf("Postorder : ");
    postorder_traversal(root);
    printf("\n");

    printf("Deleting Node 20\n");
    deleteNode(root, 20);
    printf("Preorder  : ");
    preorder_traversal(root);
    printf("\n");
    printf("Inorder   : ");
    inorder_traversal(root);
    printf("\n");
    printf("Postorder : ");
    postorder_traversal(root);
    printf("\n");

    printf("Deleting Node 30\n");
    deleteNode(root, 30);
    printf("Preorder  : ");
    preorder_traversal(root);
    printf("\n");
    printf("Inorder   : ");
    inorder_traversal(root);
    printf("\n");
    printf("Postorder : ");
    postorder_traversal(root);
    printf("\n");

    printf("Deleting Node 70\n");
    deleteNode(root, 70);
    printf("Preorder  : ");
    preorder_traversal(root);
    printf("\n");
    printf("Inorder   : ");
    inorder_traversal(root);
    printf("\n");
    printf("Postorder : ");
    postorder_traversal(root);
    printf("\n");

    free_tree(root);

    return 0;
}
