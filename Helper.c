#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

// Fungsi untuk mendapatkan nomor antrian hari ini
int get_nomor_antrian_hari_ini() {
    static int nomor_antrian = 0;
    static time_t last_reset = 0;
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    
    // Reset nomor antrian setiap hari baru
    if (last_reset == 0 || tm_now->tm_mday != localtime(&last_reset)->tm_mday) {
        nomor_antrian = 0;
        last_reset = now;
    }
    
    return ++nomor_antrian;
}

// Fungsi untuk generate ID baru
void generate_id(char* id) {
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    
    int nomor_antrian = get_nomor_antrian_hari_ini();
    int tanggal = tm_now->tm_mday;
    int bulan = tm_now->tm_mon + 1;
    int tahun = tm_now->tm_year - 100; // Mengambil 2 digit terakhir tahun
    
    // Format: XXDDMMYY
    sprintf(id, "%02d%02d%02d%02d", nomor_antrian, tanggal, bulan, tahun);
}