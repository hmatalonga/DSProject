#include "dataobj.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

BLIST *BLISTMemAlloc() {
    return (BLIST *) malloc(sizeof(BLIST));
}

BLIST *BLISTCreate(BLIST *L) {
    L = NULL;
    return L;
}

BLIST *BLISTAppend(BLIST *head, CALENDAR cal, unsigned int id) {
    BLIST *newp;
    if ((newp = BLISTMemAlloc()) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->cal = cal;
    newp->id = id;
    newp->next = head;
    return newp;    
}

BLIST *BLISTPrint(BLIST *L) {
    while (L != NULL) {
        printf("%lu\n", L->id);
        L = L->next;
    }
}

BLIST *BLISTSwap(BLIST *a, BLIST *b) {
    a->next = b->next;
    b->next = a;
    return b;    
}

BLIST *BLISTMove(BLIST *obj) {
    BLIST *n, *p, *ret;
    p = obj;
    n = obj->next;
    ret = n;
    while (n != NULL && obj->id > n->id) {
        p = n;
        n = n->next;
    }
    /* we now move the top item between p and n */
    p->next = obj;
    obj->next = n;
    return ret;    
}

BLIST *BLISTSort(BLIST *head) {
    if (head == NULL)
        return NULL;
    head->next = BLISTSort(head->next);
    //head->index > head->next->index str1 é maior
    if (head->next != NULL && head->id > head->next->id)
        head = BLISTMove(head);
    return head;    
}


BLIST *BLISTExtend(BLIST *head, BLIST *ext) {
    while (ext != NULL) {
        head = BLISTAppend(head, ext->cal, ext->id);
        ext = ext->next;
    }
    return head;
}

// Hashtable methods
HASH *HashMemAlloc() {
    return (HASH *) malloc(sizeof(HASH)); 
}

HASH *HashCreate(int size) {
    HASH *new_table;
    int i = 0;
    
    if (size < 1)
        return NULL; /* invalid size for table */

    /* Attempt to allocate memory for the table structure */
    if ((new_table = HashMemAlloc()) == NULL)
        return NULL;
    
    /* Attempt to allocate memory for the table itself */
    if ((new_table->table = (BLIST **)malloc(size*sizeof(BLIST *))) == NULL)
        return NULL;

    /* Initialize the elements of the table */
    for(i = 0; i < size; i++)
        new_table->table[i] = NULL;

    /* Set the table's size */
    new_table->size = size;

    return new_table;    
}

// Binary Tree Methods
int CNodeHeight(CNODE *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

CNODE *CNodeMemAlloc() {
    return (CNODE *) malloc(sizeof(CNODE));
}

CNODE *CNodeNewNode(unsigned short int val) {
    CNODE *newNode = CNodeMemAlloc();
    newNode->course = val;
    newNode->hash = HashCreate(HASH_SIZE);
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;    
}

CNODE *CNodeRightRotate(CNODE *y) {
    CNODE *x = y->left;
    CNODE *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(CNodeHeight(y->left), CNodeHeight(y->right))+1;
    x->height = max(CNodeHeight(x->left), CNodeHeight(x->right))+1;

    // Return new root
    return x;    
}
CNODE *CNodeLeftRotate(CNODE *x) {
    CNODE *y = x->right;
    CNODE *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(CNodeHeight(x->left), CNodeHeight(x->right))+1;
    y->height = max(CNodeHeight(y->left), CNodeHeight(y->right))+1;
 
    // Return new root
    return y;    
}

int CNodeGetBalance(CNODE *node) {
    if (node == NULL)
        return 0;
    return CNodeHeight(node->left) - CNodeHeight(node->right);
}

CNODE *CNodeInsert(CNODE *node, unsigned short int val) {
    if (node == NULL)
        return(CNodeNewNode(val));
    
    if (val < node->course)
        node->left = CNodeInsert(node->left, val);
    else
        node->right = CNodeInsert(node->right, val);

    node->height = max(CNodeHeight(node->left), CNodeHeight(node->right)) + 1;
    
    int balance = CNodeGetBalance(node);
    
    // Left Left Case
    if (balance > 1 && val < node->left->course)
        return CNodeRightRotate(node);
 
    // Right Right Case
    if (balance < -1 && val > node->right->course)
        return CNodeLeftRotate(node);
 
    // Left Right Case
    if (balance > 1 && val > node->left->course)
    {
        node->left =  CNodeLeftRotate(node->left);
        return CNodeRightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && val < node->right->course)
    {
        node->right = CNodeRightRotate(node->right);
        return CNodeLeftRotate(node);
    }    
    
    return (node);   
}

CNODE *CNodeLookUp(CNODE *node, unsigned short int val) {
    if (node == NULL)
      return NULL;
    else
      if (val == node->course)
          return node;
      else
          if (val < node->course)
              return(CNodeLookUp(node->left, val));
          else
              return(CNodeLookUp(node->right, val));    
}

RESLIST *ResMemAlloc() {
    return (RESLIST *) malloc(sizeof(RESLIST));
}

/**
 * Adiciona um novo elemento no inicio da Lista
 * @param head Cabeça da Lista
 * @param obj Novo elemento a adicionar
 * @return Retorna novamente a cabeça da lista com o novo elemento
 */
RESLIST *ResAppend(RESLIST *head, BLIST *obj) {
    RESLIST *newp;
    if ((newp = ResMemAlloc()) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->elem = obj;
    newp->next = head;
    return newp;    
}

/**
 * Procura um certo objecto na Lista de dados
 * @param head Cabeça da Lista a procurar
 * @param obj Objecto a ser procurado
 * @return O objecto da lista caso tenha encontrado senão devolve NULL
 */
RESLIST *ResFind(RESLIST *head, BLIST *obj) {
    while (head != NULL) {
        if (head->elem->id == obj->id)
            return head;
        head = head->next;
    }
    return NULL;
}

/**
 * Actualiza a lista de resultados
 * @param output Lista com os resultados existentes 
 * @param nlist Nova lista com dados a intersectar
 * @return Uma nova lista de resultados obtida pela intersecção das listas
 */
RESLIST *ResCopy(RESLIST *output, RESLIST *nlist) {
    RESLIST *newp = NULL;
    while (nlist != NULL) {
        if (output == NULL || ResFind(output, nlist->elem) != NULL)
            newp = ResAppend(newp, nlist->elem);
        nlist = nlist->next;
    }
    return newp;
}

/**
 * Liberta memória anexa a uma lista
 * @param head Cabeça da lista a libertar memória
 * @return A lista vazia (NULL)
 */
RESLIST *ResClearAll(RESLIST *head) {
    RESLIST *current = head, *temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
    return head;
}

/**
 * Função para contar o número total de elementos de uma lista
 * @param head Cabeça da lista a contar
 * @return Número total de elementos
 */
long int ResCount(RESLIST *head) {
    long int c = 0;
    while (head != NULL) {
        c++;
        head = head->next;
    }
    return c;
}

/**
 * Imprime os dados de uma dada lista
 * @param head Cabeça da lista
 */
void ResPrint(RESLIST *head) {
    while (head != NULL) {
        printf("%ld\n", head->elem->id);
        head = head->next;
    }
}

RESLIST *removeDuplicates(RESLIST *head) {
    /* Pointer to traverse the linked list */
    RESLIST *current = head;

    /* Pointer to store the next pointer of a node to be deleted*/
    RESLIST *next_next;

    /* do nothing if the list is empty */
    if(current == NULL)
        return NULL;

    /* Traverse the list till last node */
    while(current->next != NULL) {
        /* Compare current node with next node */
        if(current->elem->id == current->next->elem->id) {
            /*The sequence of steps is important*/              
            next_next = current->next->next;
            free(current->next);
            current->next = next_next; 
        }
        else /* This is tricky: only advance if no deletion */
            current = current->next;
    }
    
    return head;
}

// Returns the last node of the list
RESLIST *getTail(RESLIST *elem) {
    while (elem != NULL && elem->next != NULL)
        elem = elem->next;
    return elem;
}
 
// Partitions the list taking the last element as the pivot
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd) {
    RESLIST *pivot = end;
    RESLIST *prev = NULL, *cur = head, *tail = pivot;
 
    // During partition, both the head and end of the list might change
    // which is updated in the newHead and newEnd variables
    while (cur != pivot) {
        if (cur->elem->id < pivot->elem->id) {
            // First node that has a value less than the pivot - becomes
            // the new head
            if ((*newHead) == NULL)
                (*newHead) = cur;
 
            prev = cur; 
            cur = cur->next;
        }
        else { // If cur node is greater than pivot
            // Move cur node to next of tail, and change tail
            if (prev)
                prev->next = cur->next;
            RESLIST *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }
 
    // If the pivot data is the smallest element in the current list,
    // pivot becomes the head
    if ((*newHead) == NULL)
        (*newHead) = pivot;
 
    // Update newEnd to the current last node
    (*newEnd) = tail;
 
    // Return the pivot node
    return pivot;
}
 
 
//here the sorting happens exclusive of the end node
RESLIST *quickSort(RESLIST *head, RESLIST *end) {
    // base condition
    if (!head || head == end)
        return head;
 
    RESLIST *newHead = NULL, *newEnd = NULL;
 
    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    RESLIST *pivot = partition(head, end, &newHead, &newEnd);
 
    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot) {
        // Set the node before the pivot node as NULL
        RESLIST *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;
 
        // Recur for the list before pivot
        newHead = quickSort(newHead, tmp);
 
        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }
 
    // Recur for the list after the pivot element
    pivot->next = quickSort(pivot->next, newEnd);
 
    return newHead;
}