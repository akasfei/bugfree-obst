typedef struct BinTreeClass
{
    struct BinTreeObject *root, *_this;
    int height;
    int count;
}BinTreeClass;

typedef struct BinTreeObject
{
    int depth;
    DataObject data;
    struct BinTreeObject *parent, *lchild, *rchild;
}BinTreeObject;

int BinTreeSelect (BinTreeClass *T, int pos) //0 to select parent, 1 to select left child, 2 to select right child.
{
    if (T->root == NULL)
        return STS_FAIL;
    if (T->_this == NULL)
        T->_this = T->root;
    if (pos == 0)
    {
        if (T->_this->parent == NULL)
            return STS_FAIL;
        T->_this = T->_this->parent;
    } else if (pos == 1)
    {
        if (T->_this->lchild == NULL)
            return STS_FAIL;
        T->_this = T->_this->lchild;
    } else if (pos == 2)
    {
        if (T->_this->rchild == NULL)
            return STS_FAIL;
        T->_this = T->_this->rchild;
    } else
        return STS_FAIL;
    return STS_OK;
}

int BinTreeView (BinTreeClass *T)
{
    if (T->root == NULL)
        return STS_FAIL;
    if (T->_this == NULL)
        T->_this = T->root;
    printf("Current selection: %s\n", DO_serialize(T->_this->data));
    if (T->_this->parent != NULL)
        printf("Parent: %s\n", DO_serialize(T->_this->parent->data));
    if (T->_this->lchild != NULL)
        printf("left child: %s\n", DO_serialize(T->_this->lchild->data));
    if (T->_this->rchild != NULL)
        printf("right child: %s\n", DO_serialize(T->_this->rchild->data));
    return STS_OK;
}

int BinTreeTraverse_RF (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T)) // Root first
{
    int mark;
    if (T->_this != NULL)
    {
        mark = (*visit) (*(T->_this), T);
        if (mark > 0)
            return STS_FAIL;
    }
    if (T->_this->lchild == NULL)
    {
        T->_this = T->_this->lchild;
        BinTreeTraverse_RF (T, visit);
    }
    if (T->_this->rchild == NULL)
    {
        T->_this = T->_this->rchild;
        BinTreeTraverse_RF (T, visit);
    }
    T->_this = T->_this->parent;
    return STS_OK;
}

int BinTreeTraverse_RM (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T)) // root middle
{
    int mark;
    if (T->_this->lchild == NULL)
    {
        T->_this = T->_this->lchild;
        BinTreeTraverse_RM (T, visit);
    }
    if (T->_this != NULL)
    {
        mark = (*visit) (*(T->_this), T);
        if (mark > 0)
            return STS_FAIL;
    }
    if (T->_this->rchild == NULL)
    {
        T->_this = T->_this->rchild;
        BinTreeTraverse_RM (T, visit);
    }
    T->_this = T->_this->parent;
    return STS_OK;
}

int BinTreeTraverse_RL (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T)) // root last
{
    int mark;
    if (T->_this->lchild == NULL)
    {
        T->_this = T->_this->lchild;
        BinTreeTraverse_RF (T, visit);
    }
    if (T->_this->rchild == NULL)
    {
        T->_this = T->_this->rchild;
        BinTreeTraverse_RF (T, visit);
    }
    if (T->_this != NULL)
    {
        mark = (*visit) (*(T->_this), T);
        if (mark > 0)
            return STS_FAIL;
    }
    T->_this = T->_this->parent;
    return STS_OK;
}

int BinTreeTraverse (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T)) // Root First
{
    int mark;
    if (T->root == NULL)
        return STS_FAIL;
    T->_this = T->root;
    if (T->root != NULL)
    {
        mark = (*visit) (*(T->_this), T);
        if (mark > 0)
            return STS_FAIL;
    }
    if (T->root->lchild == NULL)
    {
        T->root = T->root->lchild;
        BinTreeTraverse_RF (T, visit);
    }
    if (T->root->rchild == NULL)
    {
        T->root = T->root->rchild;
        BinTreeTraverse_RF (T, visit);
    }
    return STS_OK;
}

/*
int BinTreeTraverse_NoRecursion (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T)) // Root First
{
    int mark;
    if (T->root == NULL)
        return STS_FAIL;
    T->_this = T->root;
    if (T->root != NULL)
    {
        mark = (*visit) (*(T->_this), T);
        if (mark > 0)
            return STS_FAIL;
    }
    return STS_OK;
}
*/

int BinTreeTraverse_L (BinTreeClass *T, int (*visit) (BinTreeObject, BinTreeClass *T))
{
    if (T->root == NULL)
        return STS_FAIL;
    if (T->_this == NULL)
        T->_this = T->root;
    BinTreeObject *queue[255];
    int qs=0, qe=0, i, mark;
    queue[qe] = T->_this;
    qe++;
    mark = (*visit) (*(T->_this), T);
    if (mark > 0)
        return STS_FAIL;
    for (i=qs; i<=qe ; i++)
    {
        if (queue[i]->lchild != NULL)
        {
            queue[qe] = queue[i]->lchild;
            qe++;
        }
        if (queue[i]->rchild != NULL)
        {
            queue[qe] = queue[i]->rchild;
            qe++;
        }
    }
    for (i=qs; i<=qe ; i++)
    {
        mark = (*visit) (*(queue[i]), T);
        if (mark > 0)
            return STS_FAIL;
    }
    return STS_OK;
}

int BinTreeInsert (BinTreeClass *T, int pos, DataObject obj) // 1 to insert as left child, 2 to insert as right child.
{
    if (T->root == NULL)
    {
        T->root = (BinTreeObject *)malloc(sizeof(BinTreeObject));
        T->count++;
        T->height++;
        T->root->depth = 1;
        T->root->parent = T->root->lchild = T->root->rchild = NULL;
        T->root->data = obj;
        return STS_OK;
    }
    if (T->_this == NULL)
        T->_this = T->root;
    BinTreeObject *ithis = (BinTreeObject *)malloc(sizeof(BinTreeObject));
    if (T->_this->lchild != NULL && T->_this->rchild != NULL)
        return STS_MAX;
    T->count++;
    if (T->_this->depth >= T->height)
        T->height++;
    ithis->parent = T->_this;
    ithis->lchild = ithis->rchild = NULL;
    ithis->depth = T->_this->depth + 1;
    ithis->data = obj;
    if (pos == 1)
        T->_this->lchild = ithis;
    else
    if (pos == 2)
        T->_this->rchild = ithis;
    else
        return STS_CRASH;
    return STS_OK;
}

int countLeaf (BinTreeObject obj, BinTreeClass *T)
{
    T->count++;
    return STS_OK;
}

int BinTreeUpdateCount (BinTreeClass *T)
{
    if (T->root == NULL)
        return STS_FAIL;
    T->count = 0;
    BinTreeTraverse(T, &countLeaf);
    printf("Leave count: %d", T->count);
    return STS_OK;
}

int updateHeight (BinTreeObject obj, BinTreeClass *T)
{
    if (obj.depth > T->height)
        T->height = obj.depth;
    return STS_OK;
}

int BinTreeUpdateHeight (BinTreeClass *T)
{
    if (T->root == NULL)
        return STS_FAIL;
    T->height = 0;
    BinTreeTraverse(T, &updateHeight);
    printf("Height updated: %d", T->height);
    return STS_OK;
}

int BinTreeRemove (BinTreeClass *T)
{
    BinTreeObject *_this;
    if (T->_this == NULL || T->_this->lchild != NULL || T->_this->rchild != NULL)
        return STS_FAIL;
    _this = T->_this;
    T->_this = T->_this->parent;
    free(_this);
    return STS_OK;
}

int BinTreeInit (BinTreeClass *T)
{
    //T->root = T->_this = (BinTreeObject *)malloc(sizeof(BinTreeObject));
    //if (T->root == NULL)
    //    return STS_FAIL;
    //T->root->data = firstObj;
    T->root = T->_this = NULL;
    T->count = 0;
    T->height = 0;
    return STS_OK;
}
