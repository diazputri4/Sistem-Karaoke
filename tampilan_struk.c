#include "tampilan_struk.h"

void tampilkan_struk_pembayaran(antrian_laundry* node) {
    printf("\n");
    printf("==========================================\n");
    printf("||           STRUK PEMBAYARAN           ||\n");
    printf("==========================================\n");
    printf("||ID Pesanan: %d\n", node->id);
    printf("||Nama: %s\n", node->nama_pelanggan);
    printf("||No. Telepon: %s\n", node->no_telp);
    printf("||Alamat: %s\n", node->alamat);
    printf("||Tipe Layanan: %s\n", nama_paket[node->paket]);
    
    // Format waktu lebih rapi
    struct tm* tm_pesan = localtime(&node->waktu_pesan);
    printf("||Waktu Pesanan: %02d/%02d/%04d %02d:%02d:%02d\n", 
           tm_pesan->tm_mday, tm_pesan->tm_mon + 1, tm_pesan->tm_year + 1900,
           tm_pesan->tm_hour, tm_pesan->tm_min, tm_pesan->tm_sec);
    
    struct tm* tm_selesai = localtime(&node->waktu_selesai);
    printf("||Estimasi Selesai: %02d/%02d/%04d %02d:%02d:%02d\n", 
           tm_selesai->tm_mday, tm_selesai->tm_mon + 1, tm_selesai->tm_year + 1900,
           tm_selesai->tm_hour, tm_selesai->tm_min, tm_selesai->tm_sec);
    
    printf("==========================================\n");
    printf("||           TERIMA KASIH               ||\n");
    printf("||      Simpan struk pembayaran Anda    ||\n");
    printf("==========================================\n");
} 