#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdbool.h>

#define SHARED 1

void *producer1();
void *producer2();
void *consumer1();
void *consumer2();

sem_t empty, full, sm;

struct node 
{
    int data;
    int key;

    struct node *next;
    struct node *prev;
};

struct node *head = NULL;

struct node *last = NULL;

struct node *current = NULL;

bool isEmpty()
{
    return head == NULL;
}

int length()
{
    int length = 0;
    struct node *current;

    for(current = head; current != NULL; current = current->next)
    {
        length++;
    }

    return length;
}

void display()
{
    struct node *ptr = head;

    while(ptr != NULL)
    {
        printf("Current = %d",ptr->data);
        printf("\n");
        ptr = ptr->next;
    }
}

void insertEnd(int k, int d)
{
    struct node *insert = (struct node*) malloc(sizeof(struct node));
    insert->key = k;
    insert->data = d;

    if(isEmpty())
    {
        last = insert;
    }
    else
    {
        last->next = insert;

        insert->prev = last;
    }

    last = insert;
    
    printf("Current = %d\n",insert->data);
}

void deleteHead()
{
    struct node *tmp = (struct node*) malloc(sizeof(struct node));
    
    if(head == NULL)
    {
    	return;
    	printf("check");
    }
    
    tmp = head;
    
    head = head->next;
    
    free(tmp);
}

void *producer1()
{
    printf("Producer 1 has been created");
    printf("\nProducer id is %ld\n",pthread_self());

    display();

    for(int produce = 0; produce < 30; produce++)
    {
        sem_wait(&empty);
        sem_wait(&sm);
        insertEnd((length()+1),(2*(rand()%25)+1));
        sem_post(&sm);
        sem_post(&full);
        if(length()>= 30)
        {
        	break;
        }
    }

    display();
}

void *producer2()
{
    printf("Producer 2 has been created");
    printf("\nProducer id is %ld\n",pthread_self());

    display();

    for(int produce = 0; produce < 30; produce++)
    {
        sem_wait(&empty);
        sem_wait(&sm);
        insertEnd((length()+1),(2*(rand()%25)));
        sem_post(&sm);
        sem_post(&full);
        if(length()>= 30)
        {
        	break;
        }
    }

    display();
}

void *consumer1(void *num)
{
    int *thread = (int*)num;

    printf("Consumer 1 has been created");
    printf("\nConsumer id is %ld\n",pthread_self());

    display();

    for(int consume = 0; consume < 15; consume++)
    {
        sem_wait(&full);
        sem_wait(&sm);
        deleteHead();
        sem_post(&sm);
        sem_post(&empty);
    }

    display();
}

void *consumer2(void *num)
{
    int *thread = (int*)num;

    printf("Consumer 2 has been created");
    printf("\nConsumer id is %ld\n",pthread_self());

    display();

    for(int consume = 0; consume < 15; consume++)
    {
        sem_wait(&full);
        sem_wait(&sm);
        deleteHead();
        sem_post(&sm);
        sem_post(&empty);
    }

    display();
}

void main()
{
    srand(time(NULL));

    insertEnd(1,(2*(rand()%25)));
    insertEnd(2,(2*(rand()%25)+1));
    insertEnd(3,(2*(rand()%25)));
    
    display();

    pthread_t ptid1, ptid2, ctid1, ctid2;

    int x=1, y=2;
    int *a = &x;
    int *b = &y;

    sem_init(&empty, SHARED, 30);
    sem_init(&full, SHARED, 0);
    sem_init(&sm, SHARED, 1);

    pthread_create(&ptid1, NULL, producer1, NULL);
    pthread_create(&ptid2, NULL, producer2, NULL);
    pthread_create(&ctid1, NULL, consumer1, (void*)a);
    pthread_create(&ctid2, NULL, consumer2, (void*)b);

    pthread_join(ctid1,NULL);
    pthread_join(ctid2,NULL);
    pthread_join(ptid1,NULL);
    pthread_join(ptid2,NULL);   
}
