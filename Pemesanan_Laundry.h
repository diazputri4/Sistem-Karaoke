#ifndef PEMESANAN_LAUNDRY_H
#define PEMESANAN_LAUNDRY_H
#include "Antrian_Laundry.h"
#include "Helper.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

typedef enum {
    TUNAI,
    TRANSFER,
    EWALLET
} metode_pembayaran;

typedef struct {
    antrian_laundry* datastruk;
    metode_pembayaran metode;
    int harga;
    
    // Field tambahan untuk sistem layanan detail
    char nama_layanan[100];
    int jumlah;
    int harga_satuan;
    int subtotal;
    int diskon;
    int estimasi_hari;
} pesanan;

typedef struct {
    char nama_layanan[50];
    int harga;
    int estimasi_hari;
} DetailLayanan;

// Fungsi yang sudah ada
void tampilkan_katalog(int paket);
DetailLayanan get_detail_layanan(int paket, int sub_pilihan);
extern pesanan latest_order;
void tampilkan_struk_pembayaran(pesanan print);
void order(antrian_laundry * neworder);

// Fungsi baru untuk sistem layanan detail
void tampilkan_katalog_wash_regular();
void tampilkan_katalog_wash_premium();
void tampilkan_katalog_repair();
void tampilkan_katalog_repaint();
void get_layanan_info(int tipe_layanan, int sub_tipe, int pilihan, char* nama_layanan, int* harga, int* estimasi);

#endif
