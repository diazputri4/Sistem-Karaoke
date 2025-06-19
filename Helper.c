#include "Helper.h"
#include "History.h"
// Fungsi untuk mendapatkan nomor antrian terakhir dari history
int get_last_queue_number() {
    if (history_head == NULL) {
        return 0;
    }

    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    int current_day = tm_now->tm_mday;
    int current_month = tm_now->tm_mon + 1;
    int current_year = tm_now->tm_year - 100;

    int max_queue = 0;
    history_node* current = history_head;

    while (current != NULL) {
        // Parse ID untuk mendapatkan tanggal dan nomor antrian
        int queue_num, day, month, year;
        sscanf(current->data.datastruk->id, "%02d%02d%02d%02d", 
               &queue_num, &day, &month, &year);

        // Jika tanggal sama dengan hari ini, bandingkan nomor antrian
        if (day == current_day && month == current_month && year == current_year) {
            if (queue_num > max_queue) {
                max_queue = queue_num;
            }
        }

        current = current->next;
    }

    return max_queue;
}

// Fungsi untuk mendapatkan nomor antrian hari ini
int get_nomor_antrian_hari_ini() {
    static int nomor_antrian = 0;
    static time_t last_reset = 0;
    time_t now = time(NULL);
    struct tm* tm_now = localtime(&now);
    
    // Reset nomor antrian setiap hari baru
    if (last_reset == 0 || tm_now->tm_mday != localtime(&last_reset)->tm_mday) {
        // Cek history untuk nomor antrian terakhir jika masih di hari yang sama
        nomor_antrian = get_last_queue_number();
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
    printf(id, "%02d%02d%02d%02d", nomor_antrian, tanggal, bulan, tahun);
}
