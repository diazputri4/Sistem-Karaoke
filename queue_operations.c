#include "laundry_system.h"

/*
Nama: init_queue
Parameter yang dibutuhkan: Queue* q (pointer ke struktur queue)
Proses yang dilakukan: Menginisialisasi queue dengan mengatur front dan rear ke NULL, count ke 0
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Queue yang sudah diinisialisasi
*/
void init_queue(Queue* q) {
    q->front = NULL;
    q->rear = NULL;
    q->count = 0;
}

/*
Nama: enqueue
Parameter yang dibutuhkan: Queue* q (pointer ke queue), Pesanan pesanan (data pesanan)
Proses yang dilakukan: Menambahkan pesanan baru ke belakang queue
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Queue dengan pesanan baru di belakang
*/
void enqueue(Queue* q, Pesanan pesanan) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = pesanan;
    newNode->next = NULL;
    
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->count++;
}

/*
Nama: dequeue
Parameter yang dibutuhkan: Queue* q (pointer ke queue)
Proses yang dilakukan: Mengambil dan menghapus pesanan dari depan queue
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Data pesanan yang diambil dari depan queue
*/
Pesanan dequeue(Queue* q) {
    Pesanan temp = {0};
    if (q->front == NULL) {
        return temp;
    }
    
    Node* nodeToDelete = q->front;
    temp = nodeToDelete->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(nodeToDelete);
    q->count--;
    return temp;
}

/*
Nama: is_empty
Parameter yang dibutuhkan: Queue* q (pointer ke queue)
Proses yang dilakukan: Mengecek apakah queue kosong atau tidak
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: 1 jika queue kosong, 0 jika tidak kosong
*/
int is_empty(Queue* q) {
    return q->front == NULL;
}
