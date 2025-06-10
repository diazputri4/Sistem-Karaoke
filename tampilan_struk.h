#ifndef TAMPILAN_STRUK_H
#define TAMPILAN_STRUK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Antrian_Laundry.h"

// Konstanta untuk tipe layanan
typedef enum {
    REGULAR_WASH = 1,
    PREMIUM_WASH,
    REPAIRMENT,
    REPAINT
} TipeLayanan;

// Konstanta untuk metode pembayaran
typedef enum {
    TUNAI = 1,
    TRANSFER_BANK,
    E_WALLET
} MetodePembayaran;

typedef struct {
    char nama[30];
    char no_hp[15];
    char alamat[50];
} Pelanggan;

typedef struct {
    char id_pesanan[10];
    Pelanggan pelanggan;
    TipeLayanan tipe_layanan;
    int jumlah_pasang;
    float berat;
    float total_harga;
    MetodePembayaran metode_pembayaran;
    time_t waktu_pesanan;
} Pesanan;

void tampilkan_struk_pembayaran(antrian_laundry* node, Pesanan p);
void clear_screen();

#endif 