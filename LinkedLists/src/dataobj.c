#include "dataobj.h"

/**
 * Calcula o valor máximo de 2 variáveis
 * @param a Primeira variável
 * @param b Segunda variável
 * @return Valor máximo
 */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * Aloca memória para novo ponteiro do tipo PLIST
 * @return Endereço do novo ponteiro alocado
 */
PLIST *PLISTMemAlloc() {
    return (PLIST *) malloc(sizeof(PLIST));
}

/**
 * Adiciona um novo elemento no inicio da Lista
 * @param head Cabeça da Lista
 * @param obj Novo elemento a adicionar
 * @return Retorna novamente a cabeça da lista com o novo elemento
 */
PLIST *PLISTAppend(PLIST *head, PLIST *obj) {
    PLIST *newp;
    if ((newp = PLISTMemAlloc()) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->cal = obj->cal;
    newp->course = obj->course;
    newp->grade = obj->grade;
    newp->id = obj->id;
    newp->next = head;
    return newp;    
}

/**
 * Aloca memória para novo ponteiro do tipo RESLIST
 * @return Endereço do novo ponteiro alocado
 */
RESLIST *ResMemAlloc() {
    return (RESLIST *) malloc(sizeof(RESLIST));
}

/**
 * Adiciona um novo elemento no inicio da Lista
 * @param head Cabeça da Lista
 * @param obj Novo elemento a adicionar
 * @return Retorna novamente a cabeça da lista com o novo elemento
 */
RESLIST *ResAppend(RESLIST *head, PLIST *obj) {
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
RESLIST *ResFind(RESLIST *head, PLIST *obj) {
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

/**
 * Troca 2 elementos de uma lista de resultados
 * @param a Elemento A
 * @param b Elemento B
 * @return O elemento B na nova posição da lista
 */
RESLIST *ResSwap(RESLIST *a, RESLIST *b) {
    a->next = b->next;
    b->next = a;
    return b;    
}

/**
 * Ordena a lista implementando o algoritmo bubble sort
 * A implementação deste algoritmo foi retirada de:
 * http://faculty.salina.k-state.edu/tim/CMST302/study_guide/topic7/bubble.html
 * @param head Cabeça da lista
 * @return A Lista ordenada por ordem crescente
 */
RESLIST *ResSort(RESLIST *head) {
    RESLIST *p, *q, *top;
    int changed = 1;
    long int c = 0;

    /*
    * We need an extra item at the top of the list just to help
    * with assigning switched data to the 'next' of a previous item.
    * It (top) gets deleted after the data is sorted.
    */

    if( (top = ResMemAlloc()) == NULL) {
        fprintf( stderr, "Memory Allocation error.\n" );
        // In Windows, replace following with a return statement.
        exit(1);
    }

    top->next = head;
    if( head != NULL && head->next != NULL ) {
        /*
        * This is a survival technique with the variable changed.
        *
        * Variable q is always one item behind p. We need q, so
        * that we can make the assignment q->next = list_switch( ... ).
        */

        while( changed ) {
            printf("%ld\n", c++);
            changed = 0;
            q = top;
            p = top->next;
            while( p->next != NULL ) {
                /* push bigger items down */
                if( p->elem->id > p->next->elem->id ) {
                    q->next = ResSwap( p, p->next );
                    changed = 1;
                }
                q = p;
                if( p->next != NULL )
                    p = p->next;
            }
        }
    }
    p = top->next;
    free( top );
    return p;   
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