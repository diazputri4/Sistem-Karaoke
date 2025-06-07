#ifndef ANTRIAN_LAUNDRY_H
#define ANTRIAN_LAUNDRY_H

#include "Tampilan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char nama_pelanggan[30];
    int no_telp;
    char alamat[50];
    struct node * nextnode;
} antrian_laundry;

int isEmpty(antrian_laundry * cek);
void clean_stdin(char * buffer);
int validasi_no_telp(const char * nomor);
void input_data(antrian_laundry ** hasil);
int isDigit(char c);
void enqueue(antrian_laundry ** in);
void dequeue(antrian_laundry ** del);
void display_antrian(antrian_laundry ** awal, antrian_laundry * display);
void cari_antrian(antrian_laundry ** awal, antrian_laundry * display);

#endif