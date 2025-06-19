// File ini tidak perlu fungsi antrian, semua sudah di Antrian_Laundry.h/.c
// Jika ingin menambah fitur lain, tambahkan di sini, tapi untuk antrian cukup panggil dari Antrian_Laundry.h

#include "laundry_system.h"
#include "Antrian_Laundry.h"
#include "tampilan_struk.h"
#include "tampilan_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h> // untuk sleep()
#include "clear_screen.h"

// Konstanta untuk tipe layanan
#define REGULAR_WASH 1
#define PREMIUM_WASH 2
#define REPAIRMENT 3
#define REPAINT 4

void buat_pesanan(antrian_laundry** q) {
    antrian_laundry* new_node = (antrian_laundry*)malloc(sizeof(antrian_laundry));
    if (new_node == NULL) {
        printf("Gagal mengalokasikan memori\n");
        return;
    }

    // Input data pelanggan terlebih dahulu
    printf("\nMasukkan nama pelanggan: ");
    scanf(" %[^\n]s", new_node->nama_pelanggan);
    printf("Masukkan nomor telepon: ");
    scanf("%d", &new_node->no_telp);
    getchar();
    printf("Masukkan alamat: ");
    scanf(" %[^\n]s", new_node->alamat);

    // Buat struct Pesanan untuk data pesanan
    Pesanan p;

    // Setelah data pelanggan, tampilkan pilihan layanan
    printf("\n||================== MENU LAYANAN =====================||\n");
    printf("||1. Regular Wash                                    ||\n");
    printf("||2. Premium Wash                                    ||\n");
    printf("||3. Repairment                                      ||\n");
    printf("||4. Repaint                                         ||\n");
    printf("||=======================================================||\n");
    printf("Pilihan: ");
    scanf("%d", &p.tipe_layanan);

    // Set prioritas berdasarkan tipe layanan
    int prioritas;
    if (p.tipe_layanan == PREMIUM_WASH) {
        prioritas = 1;
    } else {
        prioritas = 2;
    }

    // Generate ID pesanan berdasarkan waktu
    time_t t = time(NULL);
    struct tm* tm = localtime(&t);
    char id_pesanan[20];
    sprintf(id_pesanan, "%03d/%02d/%02d/%02d/%02d", 1, prioritas, tm->tm_mday, tm->tm_mon + 1, tm->tm_year % 100);
    strcpy(p.id_pesanan, id_pesanan);

    // Input jumlah pasang
    printf("Masukkan jumlah pasang: ");
    scanf("%d", &p.jumlah_pasang);

    // Hitung total harga
    float harga_per_pasang;
    switch(p.tipe_layanan) {
        case REGULAR_WASH:
            harga_per_pasang = 15000.0;
            break;
        case PREMIUM_WASH:
            harga_per_pasang = 25000.0;
            break;
        case REPAIRMENT:
            harga_per_pasang = 50000.0;
            break;
        case REPAINT:
            harga_per_pasang = 75000.0;
            break;
        default:
            harga_per_pasang = 0.0;
    }
    p.total_harga = harga_per_pasang * p.jumlah_pasang;

    // Input metode pembayaran
    printf("\nPilih metode pembayaran:\n");
    printf("1. Tunai\n");
    printf("2. Transfer Bank\n");
    printf("3. E-Wallet\n");
    printf("Pilihan: ");
    scanf("%d", &p.metode_pembayaran);

    // Set waktu pesanan
    p.waktu_pesanan = t;

    // Tambahkan ke antrian
    new_node->nextnode = *q;
    *q = new_node;

    // Tampilkan struk pembayaran
    tampilkan_struk_pembayaran(new_node, p);
}

void list_antrian(antrian_laundry* q) {
    if (q == NULL) {
        printf("\nAntrian kosong!\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getch();
        return;
    }
    
    printf("\nDaftar Antrian:\n");
    antrian_laundry* current = q;
    int i = 1;
    while (current != NULL) {
        printf("%d. %s - %d\n", i, current->nama_pelanggan, current->no_telp);
        current = current->nextnode;
        i++;
    }
    printf("\nTekan Enter untuk kembali ke menu...");
    getch();
}

void detail_status_pesanan(antrian_laundry* q) {
    if (q == NULL) {
        printf("\nAntrian kosong!\n");
        printf("Tekan Enter untuk kembali ke menu...");
        getch();
        return;
    }
    
    char nama[30];
    printf("\nMasukkan nama pelanggan: ");
    scanf(" %[^\n]s", nama);
    
    antrian_laundry* current = q;
    int found = 0;
    while (current != NULL) {
        if (strcmp(current->nama_pelanggan, nama) == 0) {
            printf("\nDetail Pesanan:\n");
            printf("Nama: %s\n", current->nama_pelanggan);
            printf("No. Telp: %d\n", current->no_telp);
            printf("Alamat: %s\n", current->alamat);
            found = 1;
            break;
        }
        current = current->nextnode;
    }
    
    if (!found) {
        printf("\nPesanan tidak ditemukan!\n");
    }
    printf("\nTekan Enter untuk kembali ke menu...");
    getch();
}

void riwayat_pesanan_hari_ini() {
    printf("\nMohon Maaf Fitur dalam pengembangan!\n");
    printf("Tekan Enter untuk kembali ke menu...");
    getch();
}
