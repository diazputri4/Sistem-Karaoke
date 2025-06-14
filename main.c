#include <stdio.h>
#include <stdlib.h>
#include "Antrian_Laundry.h"
#include "Pemesanan_Laundry.h"
#include "Tampilan.h"
#include "History.h"

int main() {
    int pilihan;
    
    do {
        load_from_file(&history_head);
        system("cls");
        tampilan_logo_menu();
        tampilkan_menu();
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1:
                system("cls");
                tampilan_logo_menu();
                enqueue();
                if (global_pesanan_baru != NULL) {
                    order(global_pesanan_baru);
                    tampilkan_struk_pembayaran(latest_order);
                    save_history(&history_head, &latest_order);
                }
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 2:
            system("cls");
                display_antrian();
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 3:
                break;
                
            case 4:
            system("cls");
                load_from_file(&history_head);
                display_history(history_head);
                break;
                
            case 5:
                system("cls");
                printf("\nTerima kasih telah menggunakan sistem laundry kami!\n");
                save_to_file(history_head);
                free_history(&history_head);
                dealokasi_antrian();
                break;
                
            default:
                printf("\nPilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
        }
    } while (pilihan != 5);
    
    return 0;
}