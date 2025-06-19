// ===============================
// ADT QUEUE (ANTRIAN LAUNDRY)
// ===============================
#ifndef ANTRIAN_LAUNDRY_H
#define ANTRIAN_LAUNDRY_H

#include "Tampilan.h"
#include "Helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include <windows.h>

typedef enum {
    REGULER,
    PREMIUM,
    REPAIRMENT,
    REPAINT
} Jenis_Paket;

typedef struct node {
    char nama_pelanggan[30];
    char no_telp[14];
    char alamat[50];
    char id[9];  // 8 karakter + null terminator
    Jenis_Paket paket;
    time_t waktu_pesan;
    time_t waktu_selesai;
    bool sudah_selesai;
    struct node * nextnode;
} antrian_laundry;

extern const char* nama_paket[];
extern antrian_laundry *antrian_reguler;
extern antrian_laundry *antrian_premium;
extern antrian_laundry *antrian_repairment;
extern antrian_laundry *antrian_repaint;
extern antrian_laundry *global_pesanan_baru;

int validasi_nomor_hp(char* no_hp);
int isEmpty(antrian_laundry * cek);
void clean_stdin(char * buffer);
void input_data(antrian_laundry ** hasil);
int isDigit(char c);
void enqueue();
void dequeue(antrian_laundry ** del);
void display_antrian();
void cari_antrian(antrian_laundry ** awal, antrian_laundry * display);
void tampilkan_waktu(time_t waktu);
void perbarui_status_pesanan(antrian_laundry ** awal);
void periksa_status_pesanan(antrian_laundry ** awal);
void tampilkan_menu();
void dealokasi_antrian();

// Fungsi untuk menyimpan dan memuat antrian
void save_queue_to_file();
void load_queue_from_file();

// Fungsi untuk auto-dequeue pesanan yang sudah selesai
void auto_dequeue_completed();

void tampilkan_status_semua_pesanan();

void edit_status_pengambilan();

#endif

