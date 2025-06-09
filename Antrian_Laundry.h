#ifndef ANTRIAN_LAUNDRY_H
#define ANTRIAN_LAUNDRY_H

#include "Tampilan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

typedef enum {
    REGULER,
    PREMIUM,
    REPAIRMENT,
    REPAINT
} Jenis_Paket;

typedef struct node {
    char nama_pelanggan[30];
    int no_telp;
    char alamat[50];
    int id;
    Jenis_Paket paket;
    time_t waktu_pesan;
    time_t waktu_selesai;
    bool sudah_selesai;
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
void tampilkan_waktu(time_t waktu);
void perbarui_status_pesanan(antrian_laundry ** awal);
void periksa_status_pesanan(antrian_laundry ** awal);
void tampilkan_menu();

#endif