#include <stdio.h>
#include <string.h>
#include "pesanan.h"

void tampilkanMenu() {
    printf("\n||================== MENU SISTEM LAUNDRY =====================||\n");
    printf("||		{1}. Buat Pesanan Baru                        ||\n");
    printf("||		{2}. Detail Status Pesanan                    ||\n");
    printf("||		{3}. Histori                                  ||\n");
    printf("||		{4}. Keluar                                   ||\n");
    printf("\n||============================================================||\n");
    printf("||Pilih menu (1-4):");

}

int main() {
    int pilihan;
    Pesanan* pesanan = NULL;
    int id_pesanan, id_pelanggan, tipe_harga, tipe_durasi, tipe_pelayanan;
    float berat;
    char status_baru[20];

    do {
        tampilkanMenu();
        scanf("%d", &pilihan);
        getchar(); // Membersihkan buffer

        switch (pilihan) {
            case 1: // Buat Pesanan Baru
                printf("\n=== BUAT PESANAN BARU ===\n");
                printf("ID Pesanan: ");
                scanf("%d", &id_pesanan);
                printf("ID Pelanggan: ");
                scanf("%d", &id_pelanggan);
                
                printf("\nTipe Harga:\n");
                printf("1. Kiloan\n");
                printf("2. Satuan\n");
                printf("3. Setrika\n");
                printf("Pilih tipe harga (1-3): ");
                scanf("%d", &tipe_harga);
                
                printf("\nTipe Durasi:\n");
                printf("1. Instant\n");
                printf("2. Express\n");
                printf("3. Reguler\n");
                printf("Pilih tipe durasi (1-3): ");
                scanf("%d", &tipe_durasi);
                
                printf("\nTipe Pelayanan:\n");
                printf("1. Ambil di tempat\n");
                printf("2. Antar jemput\n");
                printf("Pilih tipe pelayanan (1-2): ");
                scanf("%d", &tipe_pelayanan);
                
                if (tipe_harga == 1 || tipe_harga == 3) {
                    printf("Masukkan berat (kg): ");
                    scanf("%f", &berat);
                } else {
                    berat = 0;
                }

                // Hapus pesanan lama jika ada
                if (pesanan != NULL) {
                    deletePesanan(pesanan);
                }

                // Buat pesanan baru
                pesanan = createPesanan(id_pesanan, id_pelanggan, tipe_harga, 
                                      tipe_durasi, tipe_pelayanan, berat);
                
                if (pesanan != NULL) {
                    printf("\nPesanan berhasil dibuat!\n");
                    displayPesanan(pesanan);
                }
                break;

            case 2: // Lihat Detail Pesanan
                if (pesanan == NULL) {
                    printf("\nBelum ada pesanan yang dibuat!\n");
                } else {
                    displayPesanan(pesanan);
                }
                break;

            case 3: // Update Status Pesanan
                if (pesanan == NULL) {
                    printf("\nBelum ada pesanan yang dibuat!\n");
                } else {
                    printf("\n=== UPDATE STATUS PESANAN ===\n");
                    printf("Status saat ini: %s\n", pesanan->status);
                    printf("\nPilih status baru:\n");
                    printf("1. Menunggu\n");
                    printf("2. Diproses\n");
                    printf("3. Selesai\n");
                    printf("Pilih status (1-3): ");
                    
                    int pilihan_status;
                    scanf("%d", &pilihan_status);
                    
                    switch (pilihan_status) {
                        case 1:
                            strncpy(status_baru, "Menunggu", sizeof(status_baru) - 1);
                            status_baru[sizeof(status_baru) - 1] = '\0';
                            break;
                        case 2:
                            strncpy(status_baru, "Diproses", sizeof(status_baru) - 1);
                            status_baru[sizeof(status_baru) - 1] = '\0';
                            break;
                        case 3:
                            strncpy(status_baru, "Selesai", sizeof(status_baru) - 1);
                            status_baru[sizeof(status_baru) - 1] = '\0';
                            break;
                        default:
                            printf("Pilihan status tidak valid!\n");
                            continue;
                    }
                    
                    updateStatus(pesanan, status_baru);
                    printf("\nStatus berhasil diupdate!\n");
                    displayPesanan(pesanan);
                }
                break;

            case 4: // Keluar
                if (pesanan != NULL) {
                    deletePesanan(pesanan);
                }
                printf("\nTerima kasih telah menggunakan sistem laundry!\n");
                break;

            default:
                printf("\nPilihan tidak valid! Silakan pilih 1-4.\n");
        }
    } while (pilihan != 4);

    return 0;
} 
