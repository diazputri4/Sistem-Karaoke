#ifndef HISTORY_H
#define HISTORY_H

#include <time.h>
#include <stdbool.h>
#include "Antrian_Laundry.h"

// Structure for history entries
typedef struct history_node {
    int id;
    char nama_pelanggan[50];
    char no_telp[15];
    char alamat[100];
    int paket;
    time_t waktu_pesan;
    time_t waktu_selesai;
    struct history_node* next;
} history_node;

// Global variable declaration
extern history_node* history_head;

// Function declarations
void save_history(history_node** history_head, antrian_laundry* order);
void load_history(history_node** history_head);
void display_history(history_node* history_head);
void free_history(history_node** history_head);
void save_to_file(history_node* history_head);
void load_from_file(history_node** history_head);
int get_last_id();

#endif