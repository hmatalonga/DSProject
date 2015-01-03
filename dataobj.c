#include "dataobj.h"

int max(int a, int b) {
    return (a > b) ? a : b;
}

NOTE *appendNote(NOTE *head, PERSON *person, unsigned char grade) {
    NOTE *newp;
    if ((newp = (NOTE *) malloc(sizeof (NOTE))) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->grade = grade;
    newp->person = person;
    newp->prev = NULL;
    newp->next = head;
    if (head != NULL)
        head->prev = newp;
    return newp;
}


// Binary Tree Methods

int PersonElemHeight(PERSON *elem) {
    if (elem == NULL)
        return 0;
    return elem->height;
}

PERSON *PersonNewElem(unsigned long int val) {
    PERSON *newNode = (PERSON *) malloc(sizeof (PERSON));
    if (newNode == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }    
    newNode->id = val;
    newNode->course_array = NULL;
    newNode->course_index = 0;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

PERSON *PersonRightRotate(PERSON *y) {
    PERSON *x = y->left;
    PERSON *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(PersonElemHeight(y->left), PersonElemHeight(y->right)) + 1;
    x->height = max(PersonElemHeight(x->left), PersonElemHeight(x->right)) + 1;

    // Return new root
    return x;
}

PERSON *PersonLeftRotate(PERSON *x) {
    PERSON *y = x->right;
    PERSON *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    //  Update heights
    x->height = max(PersonElemHeight(x->left), PersonElemHeight(x->right)) + 1;
    y->height = max(PersonElemHeight(y->left), PersonElemHeight(y->right)) + 1;

    // Return new root
    return y;
}

int PersonGetBalance(PERSON *node) {
    if (node == NULL)
        return 0;
    return PersonElemHeight(node->left) - PersonElemHeight(node->right);
}

PERSON *insertPerson(PERSON *node, COURSE **courses, TEMP data) {
    int i = 0;

    // If current course has no grades alloc space
    if (courses[data.course - 1] == NULL) {
        courses[data.course - 1] = (COURSE *) malloc(sizeof (COURSE));

        if (courses[data.course - 1] == NULL) {
            fprintf(stderr, "Memory Allocation error.\n");
            exit(1);
        }

        courses[data.course - 1]->grades = (NOTE **) malloc(21 * sizeof (NOTE *));

        if (courses[data.course - 1]->grades == NULL) {
            fprintf(stderr, "Memory Allocation error.\n");
            exit(1);
        }

        for (i = 0; i < 21; i++)
            courses[data.course - 1]->grades[i] = NULL;
    }

    NOTE *grade = courses[data.course - 1]->grades[data.grade];

    if (node == NULL) {
        PERSON *newPerson = PersonNewElem(data.id);

        grade = appendNote(grade, newPerson, data.grade);
        courses[data.course - 1]->counter++;
        courses[data.course - 1]->grades[data.grade] = grade;

        newPerson->course_index = data.course;
        newPerson->course_array = (NOTE **) malloc(data.course * sizeof (NOTE *));

        if (newPerson->course_array == NULL) {
            fprintf(stderr, "Memory Allocation error.\n");
            exit(1);
        }

        for (i = 0; i < data.course; i++)
            newPerson->course_array[i] = NULL;

        newPerson->course_array[data.course - 1] = grade;

        return newPerson; // Nova pessoa 
    }

    if (data.id == node->id) {
        // Update info about current person
        if (data.course > node->course_index) {
            // Need to expand course array
            
            node->course_array = (NOTE **) realloc(node->course_array, data.course * sizeof (NOTE *));

            if (node->course_array == NULL) {
                fprintf(stderr, "Memory Allocation error.\n");
                exit(1);
            }
            
            for (i = node->course_index; i < data.course; i++)
                node->course_array[i] = NULL;
            
            node->course_index = data.course;

            grade = appendNote(grade, node, data.grade);
            courses[data.course - 1]->counter++;
            courses[data.course - 1]->grades[data.grade] = grade;

            node->course_array[data.course - 1] = grade;
        } else {
            // If there is no grade in that course
            if (node->course_array[data.course - 1] == NULL) {
                grade = appendNote(grade, node, data.grade);
                courses[data.course - 1]->grades[data.grade] = grade;
                node->course_array[data.course - 1] = grade;

            }
            else {
                NOTE *currGrade = node->course_array[data.course - 1];
                if (data.grade > currGrade->grade) {
                    // Has better grade then overwrite it
                    if (currGrade->prev == NULL && currGrade->next == NULL) {
                        
                        free(courses[data.course - 1]->grades[currGrade->grade]);
                        courses[data.course - 1]->grades[currGrade->grade] = NULL;
                    
                    }
                    else {
                        if (currGrade->prev == NULL) {
                            courses[data.course - 1]->grades[currGrade->grade]->next->prev = NULL;
                            courses[data.course - 1]->grades[currGrade->grade] = courses[data.course - 1]->grades[currGrade->grade]->next;    
                        }
                        else if (currGrade->next == NULL) {
                            currGrade->prev->next = NULL;
                        }
                        else {
                            currGrade->prev->next = currGrade->next;
                            currGrade->next->prev = currGrade->prev;
                        }
                        free(node->course_array[data.course - 1]);
                    }

                    grade = appendNote(grade, node, data.grade);
                    courses[data.course - 1]->grades[data.grade] = grade;
                    node->course_array[data.course - 1] = grade; //currGrade
                }
            }
        }
    } else if (data.id < node->id)
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
        node->left = PersonLeftRotate(node->left);
        return PersonRightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data.id < node->right->id) {
        node->right = PersonRightRotate(node->right);
        return PersonLeftRotate(node);
    }

    return (node);
}

/**
 * Adiciona um novo elemento no inicio da Lista
 * @param head Cabeça da Lista
 * @param obj Novo elemento a adicionar
 * @return Retorna novamente a cabeça da lista com o novo elemento
 */
RESLIST *ResAppend(RESLIST *head, PERSON *obj) {
    RESLIST *newp;
    if ((newp = (RESLIST *) malloc(sizeof (RESLIST))) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->elem = obj;
    newp->next = head;
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
        tmp->next = pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSort(pivot->next, newEnd);

    return newHead;
}

// Query data structure operations
QUERY *appendCriteria(QUERY *head, unsigned short int course, unsigned char grade, char oper) {
    QUERY *newp = NULL;
    if ((newp = (QUERY *) malloc(sizeof (QUERY))) == NULL) {
        fprintf(stderr, "Memory Allocation error.\n");
        exit(1);
    }
    newp->course = course;
    newp->grade = grade;
    newp->operator = oper;
    newp->next = head;
    return newp;
}

QUERY *findBest(QUERY *head) {
    QUERY *ret = NULL;
    unsigned short int mark = 100;
    while (head != NULL) {
        if (head->operator == '+') {
            if ((20 - head->grade) < mark) {
                ret = head;
                mark = head->grade;
            }
        }
        else {
            if (head->grade < mark) {
                ret = head;
                mark = head->grade;
            }            
        }         
        head = head->next;
    }
    return ret;
}