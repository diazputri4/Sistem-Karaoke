#include <stdio.h>
#include <stdlib.h>
#include "Antrian_Laundry.h"
#include "tampilan_struk.h"
#include "Tampilan.h"
#include "History.h"

int main() {
    int pilihan;
    
    do {\
        load_from_file(&history_head);
        system("cls");
        tampilan_logo_menu();
        tampilkan_menu();
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1:
                enqueue();
                if (global_pesanan_baru != NULL) {
                    save_history(&history_head, global_pesanan_baru);
                    tampilkan_struk_pembayaran(global_pesanan_baru);
                }
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 2:
                display_antrian();
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 3:
                break;
                
            case 4:
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