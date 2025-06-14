#ifndef HISTORY_H
#define HISTORY_H

#include "Pemesanan_Laundry.h"
#include <time.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Structure for history entries
typedef struct history_node {
    pesanan data;
    struct history_node* next;
} history_node;

// Global variable declaration
extern history_node* history_head;

// Function declarations
void save_history(history_node** history_head, pesanan* order);
void display_history(history_node* history_head);
void free_history(history_node** history_head);
void save_to_file(history_node* history_head);
void load_from_file(history_node** history_head);
int count_history_entries(history_node* head);

#endif