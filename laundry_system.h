#ifndef LAUNDRY_SYSTEM_H
#define LAUNDRY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_LAYANAN 20
#define MAX_NAMA 100
#define MAX_HP 15

// Struktur untuk menyimpan informasi layanan yang dipilih
typedef struct {
    char nama_layanan[100];
    int jumlah;
    int harga_satuan;
    int estimasi_hari;
} LayananDipilih;

// Struktur untuk menyimpan data pesanan
typedef struct {
    char id_pesanan[20];
    char nama_pelanggan[MAX_NAMA];
    char no_hp[MAX_HP];
    LayananDipilih layanan[MAX_LAYANAN];
    int total_layanan;
    int subtotal;
    int diskon;
    int total_bayar;
    int estimasi_selesai;
    char tanggal_terima[20];
    char tanggal_selesai[20];
} Pesanan;

// Struktur Node untuk Queue
typedef struct Node {
    Pesanan data;
    struct Node* next;
} Node;

// Struktur Queue
typedef struct {
    Node* front;
    Node* rear;
    int count;
} Queue;

// Deklarasi fungsi-fungsi
void init_queue(Queue* q);
void enqueue(Queue* q, Pesanan pesanan);
Pesanan dequeue(Queue* q);
int is_empty(Queue* q);

// Fungsi utama sistem
void buat_pesanan(Queue* q_wash, Queue* q_repair, Queue* q_repaint);
void list_antrian(Queue* q_wash, Queue* q_repair, Queue* q_repaint);
void detail_status_pesanan(Queue* q_wash, Queue* q_repair, Queue* q_repaint);
void riwayat_pesanan_hari_ini();

// Fungsi helper
int validasi_nomor_hp(char* no_hp);
void generate_id_pesanan(char* id_pesanan);
void simpan_riwayat(Pesanan pesanan);
void cetak_struk(Pesanan pesanan);
void get_tanggal_hari_ini(char* tanggal);
void hitung_tanggal_selesai(char* tanggal_selesai, int estimasi_hari);

#endif
