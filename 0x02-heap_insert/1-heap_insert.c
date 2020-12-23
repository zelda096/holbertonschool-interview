#include "binary_trees.h"
/**
 * binary_tree_size - measures the size of a binary tree
 * @tree: input binary tree
 * Return: number of descendant child nodes
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
    if (!tree)
        return (0);
    return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}
/**
 * convert - converts number and base into string
 * @num: input number
 * @base: input base
 * @lowercase: flag if hexa values need to be lowercase
 * Return: result string
 */
char *convert(unsigned long int num, int base, int lowercase)
{
    static char *rep;
    static char buffer[50];
    char *ptr;

    rep = (lowercase)
              ? "0123456789abcdef"
              : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = 0;
    do
    {
        *--ptr = rep[num % base];
        num /= base;
    } while (num);
    return (ptr);
}
/**
 * insert - helper func to insert node to correct location
 * @root: double pointer to root of max heap
 * @node: node to insert
 */
void insert(heap_t **root, heap_t *node)
{
    char c, *binary;
    unsigned int i, size;
    heap_t *tmp = NULL;

    tmp = *root;
    size = binary_tree_size(tmp) + 1;
    binary = convert(size, 2, 1);
    for (i = 1; i < strlen(binary); i++)
    {
        c = binary[i];
        if (i == strlen(binary) - 1)
        {
            if (c == '1')
                tmp->right = node;
            else if (c == '0')
                tmp->left = node;
            node->parent = tmp;
        }
        else if (c == '1')
            tmp = tmp->right;
        else if (c == '0')
            tmp = tmp->left;
    }
}
/**
 * heap_insert - inserts a value into a max binary heap
 * @root: double pointer to root of tree
 * @value: input value
 * Return: pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
    heap_t *new_node = NULL;
    int tmp;

    if (!root)
        return (NULL);
    new_node = binary_tree_node(NULL, value);
    if (!*root)
    {
        *root = new_node;
        return (new_node);
    }
    insert(root, new_node);
    while (new_node->parent && new_node->n > new_node->parent->n)
    {
        tmp = new_node->parent->n;
        new_node->parent->n = new_node->n;
        new_node->n = tmp;
        new_node = new_node->parent;
    }
    return (new_node);
}