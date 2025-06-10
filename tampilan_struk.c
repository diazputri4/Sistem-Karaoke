#include <stdio.h>
#include "tampilan_struk.h"
#include <stdlib.h>
#include <time.h>

void tampilkan_struk_pembayaran(antrian_laundry* node, Pesanan p) {
    printf("\n");
    printf("==========================================\n");
    printf("||           STRUK PEMBAYARAN           ||\n");
    printf("==========================================\n");
    printf("||ID Pesanan: %s\n", p.id_pesanan);
    printf("||Nama: %s\n", node->nama_pelanggan);
    printf("||No. Telepon: %d\n", node->no_telp);
    printf("||Alamat: %s\n", node->alamat);
    printf("||Tipe Layanan: ");
    switch(p.tipe_layanan) {
        case 1:
            printf("REGULAR WASH\n");
            break;
        case 2:
            printf("PREMIUM WASH\n");
            break;
        case 3:
            printf("REPAIRMENT\n");
            break;
        case 4:
            printf("REPAINT\n");
            break;
        default:
            printf("Tidak diketahui\n");
    }
    printf("||Jumlah Pasang: %d\n", p.jumlah_pasang);
    printf("||Total Harga: Rp %.2f\n", p.total_harga);
    printf("||Metode Pembayaran: ");
    switch(p.metode_pembayaran) {
        case 1:
            printf("TUNAI\n");
            break;
        case 2:
            printf("TRANSFER BANK\n");
            break;
        case 3:
            printf("E-WALLET\n");
            break;
        default:
            printf("Tidak diketahui\n");
    }
    
    // Format waktu lebih rapi
    struct tm* tm = localtime(&p.waktu_pesanan);
    printf("||Waktu Pesanan: %02d/%02d/%04d %02d:%02d:%02d\n", 
           tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900,
           tm->tm_hour, tm->tm_min, tm->tm_sec);
    
    printf("==========================================\n");
    printf("||           TERIMA KASIH               ||\n");
    printf("||      Simpan struk pembayaran Anda    ||\n");
    printf("==========================================\n");
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
    getchar();
} 