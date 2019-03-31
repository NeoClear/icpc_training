#include <stdio.h>
#include <stdlib.h>

#define nil NULL

struct avl
{
    int val;
    struct avl *left;
    struct avl *right;
    int height;
};

static struct avl *root = nil;

struct avl *new_node(int k, struct avl *l, struct avl *r)
{
    struct avl *ret = (struct avl *)malloc(sizeof(struct avl));
    ret->val = k;
    ret->left = l;
    ret->right = r;
    ret->height = 1;
    return ret;
}

void printt(struct avl *tree);

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int height(struct avl *t)
{
    if (t == nil)
        return 0;
    return t->height;
}

void print(struct avl *tree)
{
    if (tree == nil)
        return;
    print(tree->left);
    printf("%d ", tree->val);
    print(tree->right);
}

struct avl *search(struct avl *tree, int k)
{
    while (tree->val != k && tree != nil) {
        if (k < tree->val)
            tree = tree->left;
        else
            tree = tree->right;
    }
    return tree;
}

struct avl *min_node(struct avl *tree)
{
    if (tree == nil)
        return nil;
    while (tree->left != nil)
        tree = tree->left;
    return tree;
}

struct avl *max_node(struct avl *tree)
{
    if (tree == nil)
        return nil;
    while (tree->right != nil)
        tree = tree->right;
    return tree;
}

struct avl *ll_rotate(struct avl *tree)
{
    struct avl *lef;
    lef = tree->left;
    tree->left = lef->right;
    lef->right = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    lef->height = max(height(lef->left), height(lef->right)) + 1;
    return lef;
}

struct avl *rr_rotate(struct avl *tree)
{
    struct avl *rig;
    rig = tree->right;
    tree->right = rig->left;
    rig->left = tree;
    tree->height = max(height(tree->left), height(tree->right)) + 1;
    rig->height = max(height(rig->left), height(rig->right)) + 1;
    return rig;
}

struct avl *lr_rotate(struct avl *tree)
{
    tree->left = rr_rotate(tree->left);
    return ll_rotate(tree);
}

struct avl *rl_rotate(struct avl *tree)
{
    tree->right = ll_rotate(tree->right);
    return rr_rotate(tree);
}

struct avl *insert(struct avl *tree, int k)
{
    // If root is nil then initialize root
    if (tree == nil) {
        tree = new_node(k, nil, nil);
    } else if (k < tree->val) {
        tree->left = insert(tree->left, k);
//        tree->height = max(height(tree->left), height(tree->right)) + 1;
//        printt(tree);
//        printf("%d, %d\n", height(tree->left), height(tree->right));
        if (height(tree->left) - height(tree->right) == 2) {
//            printf("SHIT");
            if (k < tree->left->val)
                tree = ll_rotate(tree);
            else {
                tree = lr_rotate(tree);
            }
        }
    } else if (k > tree->val) {
        tree->right = insert(tree->right, k);
//        tree->height = max(height(tree->left), height(tree->right)) + 1;
        if (height(tree->right) - height(tree->left) == 2) {
            if (k > tree->right->val)
                tree = rr_rotate(tree);
            else
                tree = rl_rotate(tree);
        }
    } else {
        printf("SHIT\n");
    }

    tree->height = max(height(tree->left), height(tree->right)) + 1;
    return tree;
}

struct avl *delete_node(struct avl *tree, struct avl *node)
{
    if (tree == nil || node == nil)
        return nil;
    if (node->val < tree->val) {
        tree->left = delete_node(tree->left, node);
        if (height(tree->right) - height(tree->left) == 2) {
            if (height(tree->right->left) > height(tree->right->right))
                tree = rl_rotate(tree);
            else
                tree = rr_rotate(tree);
        }
    } else if (node->val > tree->val) {
        tree->right = delete_node(tree->right, node);
        if (height(tree->left) - height(tree->right) == 2) {
            if (height(tree->left->right) > height(tree->left->left))
                tree = lr_rotate(tree);
            else
                tree = ll_rotate(tree);
        }
    } else {
        // Delete Current Node
        if (tree->left != nil && tree->right != nil) {
            if (height(tree->left) > height(tree->right)) {
                struct avl *m = max_node(tree->left);
                tree->val = m->val;
                tree->left = delete_node(tree->left, m);
            } else {
                struct avl *n = min_node(tree->right);
                tree->val = n->val;
                tree->right = delete_node(tree->right, n);
            }
        } else {
            struct avl *t = tree;
            if (tree->left == nil)
                tree = tree->right;
            else
                tree = tree->left;
            free(t);
        }
    }
    return tree;
}

struct avl *delete_k(struct avl *tree, int k)
{
    struct avl *t = search(tree, k);
//    printf("%d\n", t->val);
    if (t == nil)
        printf("Couldn't find node\n");
    else
        return delete_node(tree, t);
}

char *pt(struct avl *tree)
{
    char *s = (char *)malloc(sizeof(char) * 99);
    if (tree == nil)
        sprintf(s, "nil");
    else
        sprintf(s, "%d", tree->val);
    return s;
}

int s = 0;

void printt(struct avl *tree)
{
    if (tree == nil)
        return;
    printt(tree->left);
    printf("%d: (%s, %s) : %d\n", tree->val, pt(tree->left), pt(tree->right), tree->height);
    if (tree->height > s)
        s = tree->height;
    printt(tree->right);
}

int main()
{
    freopen("in.txt", "r", stdin);
    int N, M;
    int t;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d", &t);
        root = insert(root, t);
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
        scanf("%d", &t);
        root = delete_k(root, t);
    }
//    root = ll_rotate(root);
//    root = delete_k(root, 1);
//    print(root);
    printt(root);
//    printf("%d\n", search(root, 10)->height);
    printf("%d\n", s);
    return 0;
}
