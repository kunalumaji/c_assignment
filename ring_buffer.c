#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
#include <pthread.h>

//act like multiple producers can
//add transmission packets to TX queue
//and single consumer NIC will read from
//the queue

struct net_buffer {
    int data;
};
typedef struct net_buffer packet;


struct ring_desc {
    void* head;
    int length;
    void* tail;
    packet* data;
};


struct TX_RING {
    int size;
    sem_t free_slots;
    sem_t occupied_slots;
    sem_t buffer_lock;
    int consumer_index;
    int producer_index;
    struct ring_desc* descriptor_array;
};


const int producers_count = 8;


struct TX_RING* init_tx_ring(int total_slots) {

    struct TX_RING* ring = malloc(sizeof(struct TX_RING));

    ring->size = total_slots;
    sem_init(&(ring->free_slots), 0, total_slots);
    sem_init(&(ring->occupied_slots), 0, 0);
    sem_init(&(ring->buffer_lock), 0, 1);
    ring->consumer_index = 0;
    ring->producer_index = 0;
    ring->descriptor_array = malloc(sizeof(struct ring_desc)*total_slots);

    return ring;

}

struct producer_thread_arg {
    struct TX_RING* tx_ring;
    struct ring_desc* desc;
};

void* produce(void* arg) {

    struct producer_thread_arg* prod_arg = (struct producer_thread_arg*) arg;
    struct TX_RING* tx_ring = prod_arg->tx_ring;
    struct ring_desc* desc = prod_arg->desc;

    //semaphore for checking if free slot is available
    // printf("waiting for free slots...");
    sem_wait(&(tx_ring->free_slots));
    // printf("unlocked\n");

    //semaphore for checking if buffer lock is available
    // printf("waiting for buffer lock...");
    sem_wait(&(tx_ring->buffer_lock));
    // printf("unlocked\n");

    if (tx_ring->descriptor_array != NULL) {
        tx_ring->descriptor_array[tx_ring->producer_index].length = desc->length;
        tx_ring->descriptor_array[tx_ring->producer_index].data = desc->data;
        tx_ring->descriptor_array[tx_ring->producer_index].head = desc->data;
        tx_ring->descriptor_array[tx_ring->producer_index].tail = desc->tail;
    }
    else
        printf("descriptor array is null\n");

    printf("produced %d index: %d\n", desc->length, tx_ring->producer_index);


    tx_ring->producer_index = (tx_ring->producer_index + 1) % tx_ring->size;

    sem_post(&(tx_ring->buffer_lock));
    sem_post(&(tx_ring->occupied_slots));

    return NULL;

}

struct ring_desc* consume(struct TX_RING* tx_ring) {

    struct ring_desc* descriptor = NULL;

    if (tx_ring->descriptor_array != NULL) {
        sem_wait(&(tx_ring->occupied_slots));

        struct ring_desc d = tx_ring->descriptor_array[tx_ring->consumer_index];

        descriptor = malloc(sizeof(struct ring_desc));
        descriptor->length = d.length;
        descriptor->data = d.data;
        descriptor->head = d.head;
        descriptor->tail = d.tail;

        printf("-->consumed %d index %d\n", descriptor->length, tx_ring->consumer_index); //consider that length as unique id for desc, just for e.g.

        tx_ring->consumer_index = (tx_ring->consumer_index + 1) % tx_ring->size;

        // if (tx_ring->consumer_index == tx_ring->producer_index) {
        //     tx_ring->consumer_index = -1;
        //     tx_ring->producer_index = 0;
        // }


        //increase free slot and decrease occupied slot by 1
        sem_post(&(tx_ring->free_slots));

    }

    return descriptor;
}


void* consume_packets(void* arg) {

    struct TX_RING* tx_ring = (struct TX_RING*) arg;

    for (int i = 0; i < producers_count; i++) {
        // pthread_join(thread_array[i], NULL);
        struct ring_desc* desc = consume(tx_ring);
        if (desc != NULL) {
            free(desc);
        }
    }

    return NULL;
}


int main() {

    struct TX_RING* tx_ring = init_tx_ring(5);

    pthread_t thread_array[producers_count];

    // for (int i = 0; i < 1000; i++) {
    //     // pthread_join(thread_array[i], NULL);
    //     struct ring_desc* desc = consume(tx_ring);
    //     if (desc != NULL) {
    //         printf("consumed %d\n", desc->length); //consider that length as unique id for desc, just for e.g.
    //         free(desc);
    //     }
    // }

    pthread_t consume_packet_id;

    pthread_create(&consume_packet_id, NULL, consume_packets, tx_ring);

    for (int i = 0; i < producers_count; i++) {

        struct ring_desc* producer_desc = malloc(sizeof(struct ring_desc));

        producer_desc->length = i;
        producer_desc->data = NULL;
        producer_desc->head = NULL;
        producer_desc->tail = NULL;

        struct producer_thread_arg* producer_arg = malloc(sizeof(struct producer_thread_arg));
        producer_arg->desc = producer_desc;
        producer_arg->tx_ring = tx_ring;

        pthread_create(&thread_array[i],NULL, produce, producer_arg);

    }

    pthread_join(consume_packet_id, NULL);

    free(tx_ring->descriptor_array);
    free(tx_ring);

    return 0;
}