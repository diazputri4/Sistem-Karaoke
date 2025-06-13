#include "laundry_system.h"

/*
Nama: validasi_nomor_hp
Parameter yang dibutuhkan: char* no_hp (string nomor HP)
Proses yang dilakukan: Memvalidasi nomor HP harus diawali 08 dan berjumlah 11-13 digit
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: 1 jika valid, 0 jika tidak valid
*/
int validasi_nomor_hp(char* no_hp) {
    int len = strlen(no_hp);
    
    // Cek panjang nomor (11-13 digit)
    if (len < 11 || len > 13) {
        return 0;
    }
    
    // Cek apakah diawali dengan "08"
    if (no_hp[0] != '0' || no_hp[1] != '8') {
        return 0;
    }
    
    // Cek apakah semua karakter adalah digit
    int i = 0;
    while (i < len) {
        if (no_hp[i] < '0' || no_hp[i] > '9') {
            return 0;
        }
        i++;
    }
    
    return 1;
}

/*
Nama: generate_id_pesanan
Parameter yang dibutuhkan: char* id_pesanan (string untuk menyimpan ID pesanan)
Proses yang dilakukan: Membuat ID pesanan dengan format: 3 digit urutan + 6 digit tanggal (DDMMYY)
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: ID pesanan yang unik untuk hari ini
*/
void generate_id_pesanan(char* id_pesanan) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    // Baca file counter untuk mendapatkan urutan pesanan hari ini
    FILE* file = fopen("counter.txt", "r");
    int counter = 1;
    char tanggal_file[20];
    
    if (file != NULL) {
        fscanf(file, "%d %s", &counter, tanggal_file);
        fclose(file);
        
        // Cek apakah tanggal hari ini sama dengan tanggal di file
        char tanggal_hari_ini[20];
        strftime(tanggal_hari_ini, sizeof(tanggal_hari_ini), "%d%m%y", tm_info);
        
        if (strcmp(tanggal_file, tanggal_hari_ini) == 0) {
            counter++;
        } else {
            counter = 1;
        }
    }
    
    // Simpan counter baru ke file
    file = fopen("counter.txt", "w");
    if (file != NULL) {
        char tanggal_hari_ini[20];
        strftime(tanggal_hari_ini, sizeof(tanggal_hari_ini), "%d%m%y", tm_info);
        fprintf(file, "%d %s", counter, tanggal_hari_ini);
        fclose(file);
    }
    
    // Format ID pesanan: 001120625 (3 digit counter + 6 digit tanggal)
    sprintf(id_pesanan, "%03d%02d%02d%02d", counter, tm_info->tm_mday, tm_info->tm_mon + 1, tm_info->tm_year % 100);
}

/*
Nama: get_tanggal_hari_ini
Parameter yang dibutuhkan: char* tanggal (string untuk menyimpan tanggal)
Proses yang dilakukan: Mendapatkan tanggal hari ini dalam format DD/MM/YYYY
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: String tanggal hari ini
*/
void get_tanggal_hari_ini(char* tanggal) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(tanggal, 20, "%d/%m/%Y", tm_info);
}

/*
Nama: hitung_tanggal_selesai
Parameter yang dibutuhkan: char* tanggal_selesai (string untuk menyimpan tanggal), int estimasi_hari (jumlah hari estimasi)
Proses yang dilakukan: Menghitung tanggal selesai berdasarkan estimasi hari kerja
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: String tanggal estimasi selesai
*/
void hitung_tanggal_selesai(char* tanggal_selesai, int estimasi_hari) {
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    // Tambahkan estimasi hari
    tm_info->tm_mday += estimasi_hari;
    mktime(tm_info);
    
    strftime(tanggal_selesai, 20, "%d/%m/%Y", tm_info);
}

/*
Nama: simpan_riwayat
Parameter yang dibutuhkan: Pesanan pesanan (data pesanan yang akan disimpan)
Proses yang dilakukan: Menyimpan data pesanan ke file riwayat untuk hari ini
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: File riwayat_DDMMYYYY.txt berisi data pesanan
*/
void simpan_riwayat(Pesanan pesanan) {
    char nama_file[50];
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    // Format nama file: riwayat_DDMMYYYY.txt
    strftime(nama_file, sizeof(nama_file), "riwayat_%d%m%Y.txt", tm_info);
    
    FILE* file = fopen(nama_file, "a");
    if (file != NULL) {
        fprintf(file, "ID: %s | Nama: %s | HP: %s | Total: Rp %d | Tanggal: %s\n",
                pesanan.id_pesanan, pesanan.nama_pelanggan, pesanan.no_hp, 
                pesanan.total_bayar, pesanan.tanggal_terima);
        
        int i = 0;
        while (i < pesanan.total_layanan) {
            fprintf(file, "  - %s x%d = Rp %d\n", 
                    pesanan.layanan[i].nama_layanan, 
                    pesanan.layanan[i].jumlah,
                    pesanan.layanan[i].harga_satuan * pesanan.layanan[i].jumlah);
            i++;
        }
        fprintf(file, "----------------------------------------\n");
        fclose(file);
    }
}

/*
Nama: cetak_struk
Parameter yang dibutuhkan: Pesanan pesanan (data pesanan untuk dicetak)
Proses yang dilakukan: Mencetak struk pesanan dengan format yang rapi
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Struk pesanan yang tercetak di layar
*/
void cetak_struk(Pesanan pesanan) {
    system("cls");
    printf("==================================================\n");
    printf("              ?? STRUK PESANAN LAUNDRY SEPATU\n");
    printf("               CLEAN & SHINE LAUNDRY\n");
    printf("==================================================\n\n");
    
    printf("?? ID Pesanan        : %s\n", pesanan.id_pesanan);
    printf("?? Tanggal Terima    : %s\n", pesanan.tanggal_terima);
    printf("?? Nama Pelanggan    : %s\n", pesanan.nama_pelanggan);
    printf("?? No. HP            : %s\n", pesanan.no_hp);
    
    printf("\n--------------------------------------------------\n");
    printf("?? Layanan yang Dipilih:\n");
    
    int i = 0;
    while (i < pesanan.total_layanan) {
        printf("%d. %s x%d\n", i+1, pesanan.layanan[i].nama_layanan, pesanan.layanan[i].jumlah);
        printf("   Harga               : Rp %d\n", pesanan.layanan[i].harga_satuan * pesanan.layanan[i].jumlah);
        printf("   Estimasi            : %d hari\n", pesanan.layanan[i].estimasi_hari);
        printf("\n");
        i++;
    }
    
    printf("--------------------------------------------------\n");
    printf("?? **Subtotal**         : Rp %d\n", pesanan.subtotal);
    printf("?? **Diskon**           : Rp %d\n", pesanan.diskon);
    printf("--------------------------------------------------\n");
    printf("**Total Bayar**        : Rp %d\n", pesanan.total_bayar);
    printf("--------------------------------------------------\n");
    printf("?? Estimasi Selesai    : %s\n", pesanan.tanggal_selesai);
    printf("--------------------------------------------------\n\n");
    
    printf("?? Terima kasih telah menggunakan layanan kami!\n");
    printf("    *Pastikan untuk mengambil sepatu Anda tepat waktu.*\n\n");
    printf("==================================================\n");
}
