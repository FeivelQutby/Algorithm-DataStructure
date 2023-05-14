#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

typedef struct Node
{
    // Tambahan height untuk menyimpan tinggi dari node
    int key, height;
    struct Node *left, *right;
} Node;

// Function untuk menghitung tinggi Tree
int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

// Function untuk mencari nilai terbesar
int max(int a, int b)
{
    return (a > b) ? a : b;
}

Node *newNode(int item)
{
    Node *temp = (Node *)malloc(sizeof(Node));
    temp->key = item;
    temp->left = temp->right = NULL;
    temp->height = 1; // Tambahin ini
    return temp;
}

// Function untuk memutar ke kiri nilai subtree dengan nilai x
Node *leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Function untuk memutar ke kanan nilai subtree dengan nilai x
Node *rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Mengambil nilai balance suatu Node
int getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int key)
{
    /* 1. Insertion kyk BST */
    if (node == NULL)
        return (newNode(key));

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys gaboleh di BST
        return node;
    /* 2. Update height node sblmnya */
    node->height = 1 + max(height(node->left),
                           height(node->right));

    /* 3. Hitung balance factor utk nentuin treenya balance apa gak */
    int balance = getBalance(node);

    // 4 case pas tree ga balance

    // LL
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // RR
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // LR
    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //  RL
    if (balance < -1 && key < node->left->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printInorder(Node *node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    printf("%d", node->key);
    printInorder(node->right);
}

void printPreorder(Node *node)
{
    if (node == NULL)
        return;
    printf("%d", node->key);
    printPreorder(node->left);
    printPreorder(node->right);
}

void printPostorder(Node *node)
{
    if (node == NULL)
        return;
    printPostorder(node->left);
    printPostorder(node->right);
    printf("%d", node->key);
}

Node *minValueNode(Node *node)
{
    Node *current = node;

    /* looping ke node terbawah di kiri */
    while (current && current->left != NULL)
        current = current->left;

    return current;
}

// Function delete node
Node *deleteNode(Node *root, int key)
{
    // base case
    if (root == NULL)
        return root;

    // Kl key < root, pindah ke kiri
    if (key < root->key)
        root->left = deleteNode(root->left, key);

    // Kl key > root, pindah kanan
    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    // Kl key = root
    else
    {
        // node 1 anak / tanpa anak
        if (root->left == NULL)
        {
            Node *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            Node *temp = root->left;
            free(root);
            return temp;
        }

        // node 2 anak
        // ambil key paling kecil di bwhnya
        Node *temp = minValueNode(root->right);

        // Copy nilai paling kecilnya ke root
        root->key = temp->key;

        // Delete nilai paling kecil
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}

int main()
{
    Node *root = NULL;

    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Base Tree\n");
    printf("Preorder  : ");
    printPreorder(root);
    printf("\n");
    printf("Inorder   : ");
    printInorder(root);
    printf("\n");
    printf("Postorder : ");
    printPostorder(root);
    printf("\n\n");

    printf("Deleting node 20\n");
    deleteNode(root, 20);
    printf("Preorder  : ");
    printPreorder(root);
    printf("\n");
    printf("Inorder   : ");
    printInorder(root);
    printf("\n");
    printf("Postorder : ");
    printPostorder(root);
    printf("\n\n");

    printf("Deleting node 30\n");
    deleteNode(root, 30);
    printf("Preorder  : ");
    printPreorder(root);
    printf("\n");
    printf("Inorder   : ");
    printInorder(root);
    printf("\n");
    printf("Postorder : ");
    printPostorder(root);
    printf("\n\n");

    printf("Deleting node 70\n");
    deleteNode(root, 70);
    printf("Preorder  : ");
    printPreorder(root);
    printf("\n");
    printf("Inorder   : ");
    printInorder(root);
    printf("\n");
    printf("Postorder : ");
    printPostorder(root);
    printf("\n\n");

    return 0;
}
