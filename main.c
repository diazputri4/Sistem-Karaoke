#include <stdio.h>
#include <stdlib.h>
#include "laundry_system.h"

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
    Queue q_wash, q_repair, q_repaint;
    init_queue(&q_wash);
    init_queue(&q_repair);
    init_queue(&q_repaint);
    
    int pilihan;
    do {
        system("cls");
        printf("\n=== SISTEM LAUNDRY SEPATU ===\n");
        printf("1. Buat Pesanan\n");
        printf("2. List Antrian\n");
        printf("3. Detail Status Pesanan\n");
        printf("4. Riwayat Pesanan Hari Ini\n");
        printf("5. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1:
                buat_pesanan(&q_wash, &q_repair, &q_repaint);
                break;
            case 2:
                list_antrian(&q_wash, &q_repair, &q_repaint);
                break;
            case 3:
                detail_status_pesanan(&q_wash, &q_repair, &q_repaint);
                break;
            case 4:
                riwayat_pesanan_hari_ini();
                break;
            case 5:
                system("cls");
                printf("\nTerima kasih telah menggunakan sistem laundry kami!\n");
                break;
            default:
                printf("\nPilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
        }
    } while (pilihan != 5);
    
    return 0;
}
