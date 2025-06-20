// ===============================
// ADT STACK/LINKED LIST (HISTORY)
// ===============================
#ifndef HISTORY_H
#define HISTORY_H

#include "Pemesanan_Laundry.h"
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Array untuk nama paket
extern const char* nama_paket_history[];

// Structure for history entries
typedef struct history_node {
    pesanan data;
    struct history_node* next;
} history_node;

// Global variable declaration
extern history_node* history_head;

// Function declarations
void save_history(history_node** history_head, pesanan* order);
void display_history(history_node** history_head);
void free_history(history_node** history_head);
void save_to_file(history_node* history_head);
void load_from_file(history_node** history_head);
int count_history_entries(history_node* head);

// Auto-delete functions
void check_and_run_auto_delete(history_node** history_head);
void auto_delete_old_history(history_node** history_head);
void debug_auto_delete();
void force_delete_old_history();
void reset_cleanup_timer();

#endif
