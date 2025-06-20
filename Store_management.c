#include "Store_management.h"

// Fungsi untuk mendapatkan waktu operasional toko
waktu_operasional get_waktu_operasional() {
    waktu_operasional waktu = {
        .buka_jam = 10,
        .buka_menit = 0,
        .tutup_jam = 20,
        .tutup_menit = 0
    };
    return waktu;
}

// Fungsi untuk mengecek apakah toko sedang buka
int is_toko_buka() {
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    
    waktu_operasional waktu = get_waktu_operasional();
    
    // Konversi waktu saat ini ke menit
    int waktu_sekarang = tm_now->tm_hour * 60 + tm_now->tm_min;
    
    // Konversi waktu buka dan tutup ke menit
    int waktu_buka = waktu.buka_jam * 60 + waktu.buka_menit;
    int waktu_tutup = waktu.tutup_jam * 60 + waktu.tutup_menit;
    
    // Cek apakah waktu saat ini berada di antara waktu buka dan tutup
    return (waktu_sekarang >= waktu_buka && waktu_sekarang < waktu_tutup);
}

// Fungsi untuk menampilkan status toko
void tampilkan_status_toko() {
    printf("\n+========================================= STATUS LAUNDRY =========================================+\n");
    
    waktu_operasional waktu = get_waktu_operasional();
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    
    printf("                                  Waktu Operasional: %02d:%02d - %02d:%02d\n", 
           waktu.buka_jam, waktu.buka_menit,
           waktu.tutup_jam, waktu.tutup_menit);
    
    printf("                                        Waktu Sekarang: %02d:%02d\n", 
           tm_now->tm_hour, tm_now->tm_min);
    
    if (is_toko_buka()) {
        printf("                                     Status: TOKO SEDANG BUKA\n");
        printf("                                 Anda dapat mengakses semua menu.\n");
    } else {
        printf("                                     Status: TOKO SEDANG TUTUP\n");
        printf("                             Anda hanya dapat mengakses menu History.\n");
    }
    printf("++================================================================================================++");
}
