#include <stdio.h>
#include <stdlib.h>
#include "Antrian_Laundry.h"
#include "Pemesanan_Laundry.h"
#include "Tampilan.h"
#include "History.h"
#include "Store_management.h"

int main() {
    int pilihan;
    
    // Load queue data at startup
    load_queue_from_file();
    
    do {
        load_from_file(&history_head);
        perbarui_status_pesanan(&antrian_reguler);
        perbarui_status_pesanan(&antrian_premium);
        perbarui_status_pesanan(&antrian_repairment);
        perbarui_status_pesanan(&antrian_repaint);
        // Auto-dequeue completed orders
        auto_dequeue_completed();
        system("cls");
        tampilan_logo_menu();
        tampilkan_status_toko();
        tampilkan_menu();
        scanf("%d", &pilihan);
        getchar();
        
        switch (pilihan) {
            case 1:
                if (is_toko_buka()) {
                    system("cls");
                    tampilkan_buat_pesanan();
                    enqueue();
                    if (global_pesanan_baru != NULL) {
                        order(global_pesanan_baru);
                        tampilkan_struk_pembayaran(latest_order);
                        save_history(&history_head, &latest_order);
                        // Save queue after new order
                        save_queue_to_file();
                    }
                } else {
                    printf("\nMaaf, toko sedang tutup. Silakan kembali pada jam operasional (10:00 - 20:00).\n");
                }
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 2:
                if (is_toko_buka()) {
                    system("cls");
                    display_antrian();
                } else {
                    printf("\nMaaf, toko sedang tutup. Silakan kembali pada jam operasional (09:00 - 18:00).\n");
                }
                printf("\nTekan Enter untuk kembali ke menu utama...");
                getchar();
                break;
                
            case 3:
                system("cls");
                tampilkan_status_semua_pesanan();
                printf("\nApakah ingin mengubah status pesanan dari 'Menunggu Pengambilan' ke 'Selesai' dan mengeluarkan dari antrian? (y/n): ");
                char pilih;
                scanf(" %c", &pilih);
                getchar();
                if (pilih == 'y' || pilih == 'Y') {
                    edit_status_pengambilan();
                }
                break;
                
            case 4:
                system("cls");
                load_from_file(&history_head);
                display_history(&history_head);
                break;
                
            case 5:
                system("cls");
                printf("\nTerima kasih telah menggunakan sistem laundry kami!\n");
                save_to_file(history_head);
                // Save queue data before exit
                save_queue_to_file();
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
