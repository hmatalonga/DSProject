#include "dataobj.h"

int max(int a, int b)
{
    return (a > b) ? a : b;
}

BLIST *BLISTMemAlloc()
{
    return (BLIST *) malloc(sizeof(BLIST));
}

BLIST *BLISTCreate(BLIST *L)
{
    L = NULL;
    return L;
}

BLIST *BLISTAppend(BLIST *head, CALENDAR cal, unsigned int id)
{
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

BLIST *BLISTPrint(BLIST *L)
{
    while (L != NULL) {
        printf("%lu\n", L->id);
        L = L->next;
    }
}

BLIST *BLISTSwap(BLIST *a, BLIST *b)
{
    a->next = b->next;
    b->next = a;
    return b;
}

BLIST *BLISTMove(BLIST *obj)
{
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

BLIST *BLISTSort(BLIST *head)
{
    if (head == NULL)
        return NULL;
    head->next = BLISTSort(head->next);
    //head->index > head->next->index str1 é maior
    if (head->next != NULL && head->id > head->next->id)
        head = BLISTMove(head);
    return head;
}


BLIST *BLISTExtend(BLIST *head, BLIST *ext)
{
    while (ext != NULL) {
        head = BLISTAppend(head, ext->cal, ext->id);
        ext = ext->next;
    }
    return head;
}

// Hashtable methods
HASH *HashMemAlloc()
{
    return (HASH *) malloc(sizeof(HASH));
}

HASH *HashCreate(int size)
{
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

NOTE *appendNote(NOTE *head, PERSON *person, unsigned char grade) {
    NOTE *newp;
    if ((newp = (NOTE *)malloc(sizeof(NOTE))) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->grade = grade;
    newp->person = person;
    newp->prev = NULL;
    newp->next = head;
    head->prev = newp;
    return newp;    
}


// Binary Tree Methods
int PersonElemHeight(PERSON *elem)
{
    if (elem == NULL)
        return 0;
    return elem->height;
}

PERSON *PersonNewElem(unsigned long int val)
{
    PERSON *newNode = (PERSON *) malloc(sizeof(PERSON));
    newNode->id = val;
    newNode->course_array = NULL;
    newNode->course_index = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

PERSON *PersonRightRotate(PERSON *y)
{
    PERSON *x = y->left;
    PERSON *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(PersonElemHeight(y->left), PersonElemHeight(y->right))+1;
    x->height = max(PersonElemHeight(x->left), PersonElemHeight(x->right))+1;

    // Return new root
    return x;
}

PERSON *PersonLeftRotate(PERSON *x)
{
    PERSON *y = x->right;
    PERSON *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(PersonElemHeight(x->left), PersonElemHeight(x->right))+1;
    y->height = max(PersonElemHeight(y->left), PersonElemHeight(y->right))+1;

    // Return new root
    return y;
}

int PersonGetBalance(PERSON *node)
{
    if (node == NULL)
        return 0;
    return PersonElemHeight(node->left) - PersonElemHeight(node->right);
}

PERSON *insertPerson(PERSON *node, COURSE **courses, TEMP data)
{
    int i = 0;
    COURSE *course = courses[data.course-1];
    
    // If current course has no grades alloc space
    if (course == NULL) {
        course = (COURSE *) malloc(sizeof(COURSE));
        course->grades = (NOTE **) malloc(20*sizeof(NOTE *));
        for (i = 0; i < 20; i++)
            course->grades[i] = NULL;
    }
    
    NOTE *grade = course->grades[data.grade-1];
    
    if (node == NULL) {
        PERSON *newPerson = PersonNewElem(data.id);
        
        grade = appendNote(grade, newPerson, data.grade);
        
        newPerson->course_index = data.course;
        newPerson->course_array = (NOTE **) malloc(data.course*sizeof(NOTE *));
        for (i = 0; i < data.course; i++)
            newPerson->course_array[i] = NULL;
        
        newPerson->course_array[data.course-1] = grade;
        
        return newPerson; // Nova pessoa 
    }

    if (data.id == node->id) {
        // Update info about current person
        if (data.course > node->course_index) {
            // Need to expand course array
            node->course_index = data.course;
            node->course_array = (NOTE **)realloc(node->course_array, data.course*sizeof(NOTE *));
            
            grade = appendNote(grade, node, data.grade);
            
            node->course_array[data.course-1] = grade;
        }
        else {
            NOTE *currGrade = node->course_array[data.course-1];
            if (data.grade > currGrade->grade) {
                // Has better grade then overwrite it
                if (currGrade->prev == NULL && currGrade->next == NULL)
                    currGrade = NULL;
                else if (currGrade->prev == NULL)
                    currGrade->next->prev = NULL;
                else if (currGrade->next == NULL)
                    currGrade->prev->next = NULL;
                else {
                    currGrade->prev->next = currGrade->next;
                    currGrade->next->prev = currGrade->prev;
                }
                free(currGrade);
                
                grade = appendNote(grade, node, data.grade);
                currGrade = grade;
            }
        }
    }


    if (data.id < node->id)
        node->left = insertPerson(node->left, courses, data);
    else
        node->right = insertPerson(node->right, courses, data);

    node->height = max(PersonElemHeight(node->left), PersonElemHeight(node->right)) + 1;

    int balance = PersonGetBalance(node);

    // Left Left Case
    if (balance > 1 && data.id < node->left->id)
        return PersonRightRotate(node);

    // Right Right Case
    if (balance < -1 && data.id > node->right->id)
        return PersonLeftRotate(node);

    // Left Right Case
    if (balance > 1 && data.id > node->left->id) {
        node->left =  PersonLeftRotate(node->left);
        return PersonRightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data.id < node->right->id) {
        node->right = PersonRightRotate(node->right);
        return PersonLeftRotate(node);
    }

    return (node);
}

PERSON *CNodeLookUp(PERSON *node, unsigned short int val)
{
    if (node == NULL)
        return NULL;
    else if (val == node->id)
        return node;
    else if (val < node->id)
        return(CNodeLookUp(node->left, val));
    else
        return(CNodeLookUp(node->right, val));
}

RESLIST *ResMemAlloc()
{
    return (RESLIST *) malloc(sizeof(RESLIST));
}

/**
 * Adiciona um novo elemento no inicio da Lista
 * @param head Cabeça da Lista
 * @param obj Novo elemento a adicionar
 * @return Retorna novamente a cabeça da lista com o novo elemento
 */
RESLIST *ResAppend(RESLIST *head, BLIST *obj)
{
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
RESLIST *ResFind(RESLIST *head, BLIST *obj)
{
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
RESLIST *ResCopy(RESLIST *output, RESLIST *nlist)
{
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
RESLIST *ResClearAll(RESLIST *head)
{
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
long int ResCount(RESLIST *head)
{
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
void ResPrint(RESLIST *head)
{
    while (head != NULL) {
        printf("%ld\n", head->elem->id);
        head = head->next;
    }
}

RESLIST *removeDuplicates(RESLIST *head)
{
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
        } else /* This is tricky: only advance if no deletion */
            current = current->next;
    }

    return head;
}

// Returns the last node of the list
RESLIST *getTail(RESLIST *elem)
{
    while (elem != NULL && elem->next != NULL)
        elem = elem->next;
    return elem;
}

// Partitions the list taking the last element as the pivot
RESLIST *partition(RESLIST *head, RESLIST *end, RESLIST **newHead, RESLIST **newEnd)
{
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
        } else { // If cur node is greater than pivot
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
RESLIST *quickSort(RESLIST *head, RESLIST *end)
{
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
