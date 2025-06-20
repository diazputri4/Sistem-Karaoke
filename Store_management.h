#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include <time.h>
#include <stdio.h>
#include <conio.h>

// Struktur untuk menyimpan waktu operasional toko
typedef struct {
    int buka_jam;
    int buka_menit;
    int tutup_jam;
    int tutup_menit;
} waktu_operasional;

// Fungsi untuk mengecek apakah toko sedang buka
int is_toko_buka();

// Fungsi untuk mendapatkan waktu operasional toko
waktu_operasional get_waktu_operasional();

// Fungsi untuk menampilkan status toko
void tampilkan_status_toko();

#endif

