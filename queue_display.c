#include "laundry_system.h"

/*
Nama: list_antrian
Parameter yang dibutuhkan: Queue* q_wash, Queue* q_repair, Queue* q_repaint (pointer ke queue masing-masing tipe)
Proses yang dilakukan: Menampilkan daftar antrian untuk semua tipe layanan
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan list antrian untuk wash, repair, dan repaint
*/
void list_antrian(Queue* q_wash, Queue* q_repair, Queue* q_repaint) {
    system("cls");
    printf("=== DAFTAR ANTRIAN PESANAN ===\n\n");
    
    // Antrian Wash
    printf("?? ANTRIAN WASH (%d pesanan)\n", q_wash->count);
    printf("----------------------------------------\n");
    if (is_empty(q_wash)) {
        printf("Tidak ada antrian wash.\n");
    } else {
        Node* current = q_wash->front;
        int nomor = 1;
        while (current != NULL) {
            printf("%d. ID: %s | %s | %s\n", 
                   nomor, current->data.id_pesanan, 
                   current->data.nama_pelanggan,
                   current->data.tanggal_selesai);
            current = current->next;
            nomor++;
        }
    }
    
    printf("\n?? ANTRIAN REPAIR (%d pesanan)\n", q_repair->count);
    printf("----------------------------------------\n");
    if (is_empty(q_repair)) {
        printf("Tidak ada antrian repair.\n");
    } else {
        Node* current = q_repair->front;
        int nomor = 1;
        while (current != NULL) {
            printf("%d. ID: %s | %s | %s\n", 
                   nomor, current->data.id_pesanan, 
                   current->data.nama_pelanggan,
                   current->data.tanggal_selesai);
            current = current->next;
            nomor++;
        }
    }
    
    printf("\n?? ANTRIAN REPAINT (%d pesanan)\n", q_repaint->count);
    printf("----------------------------------------\n");
    if (is_empty(q_repaint)) {
        printf("Tidak ada antrian repaint.\n");
    } else {
        Node* current = q_repaint->front;
        int nomor = 1;
        while (current != NULL) {
            printf("%d. ID: %s | %s | %s\n", 
                   nomor, current->data.id_pesanan, 
                   current->data.nama_pelanggan,
                   current->data.tanggal_selesai);
            current = current->next;
            nomor++;
        }
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}

/*
Nama: cari_pesanan_by_id
Parameter yang dibutuhkan: Queue* q (pointer ke queue), char* id_pesanan (ID pesanan yang dicari)
Proses yang dilakukan: Mencari pesanan berdasarkan ID dalam queue tertentu
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Pointer ke node yang berisi pesanan, atau NULL jika tidak ditemukan
*/
Node* cari_pesanan_by_id(Queue* q, char* id_pesanan) {
    Node* current = q->front;
    while (current != NULL) {
        if (strcmp(current->data.id_pesanan, id_pesanan) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

/*
Nama: detail_status_pesanan
Parameter yang dibutuhkan: Queue* q_wash, Queue* q_repair, Queue* q_repaint (pointer ke queue masing-masing tipe)
Proses yang dilakukan: Menampilkan detail status pesanan berdasarkan ID yang dimasukkan user
Input yang diperlukan: ID pesanan dari user
Output yang dihasilkan: Detail lengkap pesanan atau pesan tidak ditemukan
*/
void detail_status_pesanan(Queue* q_wash, Queue* q_repair, Queue* q_repaint) {
    system("cls");
    printf("=== DETAIL STATUS PESANAN ===\n\n");
    
    char id_pesanan[20];
    printf("Masukkan ID Pesanan: ");
    fgets(id_pesanan, sizeof(id_pesanan), stdin);
    id_pesanan[strcspn(id_pesanan, "\n")] = 0;
    
    Node* found = NULL;
    char status_antrian[50] = "";
    int posisi_antrian = 0;
    
    // Cari di queue wash
    found = cari_pesanan_by_id(q_wash, id_pesanan);
    if (found != NULL) {
        strcpy(status_antrian, "WASH");
        Node* current = q_wash->front;
        posisi_antrian = 1;
        while (current != found) {
            current = current->next;
            posisi_antrian++;
        }
    }
    
    // Jika belum ditemukan, cari di queue repair
    if (found == NULL) {
        found = cari_pesanan_by_id(q_repair, id_pesanan);
        if (found != NULL) {
            strcpy(status_antrian, "REPAIR");
            Node* current = q_repair->front;
            posisi_antrian = 1;
            while (current != found) {
                current = current->next;
                posisi_antrian++;
            }
        }
    }
    
    // Jika belum ditemukan, cari di queue repaint
    if (found == NULL) {
        found = cari_pesanan_by_id(q_repaint, id_pesanan);
        if (found != NULL) {
            strcpy(status_antrian, "REPAINT");
            Node* current = q_repaint->front;
            posisi_antrian = 1;
            while (current != found) {
                current = current->next;
                posisi_antrian++;
            }
        }
    }
    
    if (found == NULL) {
        printf("? Pesanan dengan ID %s tidak ditemukan!\n", id_pesanan);
        printf("Pastikan ID pesanan benar atau pesanan sudah selesai.\n");
    } else {
        Pesanan p = found->data;
        printf("? PESANAN DITEMUKAN\n");
        printf("=====================================\n");
        printf("ID Pesanan      : %s\n", p.id_pesanan);
        printf("Nama Pelanggan  : %s\n", p.nama_pelanggan);
        printf("No. HP          : %s\n", p.no_hp);
        printf("Tanggal Terima  : %s\n", p.tanggal_terima);
        printf("Status Antrian  : %s (Posisi ke-%d)\n", status_antrian, posisi_antrian);
        printf("Estimasi Selesai: %s\n", p.tanggal_selesai);
        
        printf("\nDetail Layanan:\n");
        int i = 0;
        while (i < p.total_layanan) {
            printf("- %s x%d = Rp %d\n", 
                   p.layanan[i].nama_layanan,
                   p.layanan[i].jumlah,
                   p.layanan[i].harga_satuan * p.layanan[i].jumlah);
            i++;
        }
        
        printf("\nTotal Bayar: Rp %d\n", p.total_bayar);
        
        if (posisi_antrian == 1) {
            printf("\n?? Status: SEDANG DIKERJAKAN\n");
        } else {
            printf("\n? Status: MENUNGGU ANTRIAN\n");
        }
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}

/*
Nama: riwayat_pesanan_hari_ini
Parameter yang dibutuhkan: Tidak ada
Proses yang dilakukan: Membaca dan menampilkan riwayat pesanan dari file riwayat hari ini
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan riwayat pesanan hari ini atau pesan tidak ada riwayat
*/
void riwayat_pesanan_hari_ini() {
    system("cls");
    printf("=== RIWAYAT PESANAN HARI INI ===\n\n");
    
    char nama_file[50];
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    
    // Format nama file: riwayat_DDMMYYYY.txt
    strftime(nama_file, sizeof(nama_file), "riwayat_%d%m%Y.txt", tm_info);
    
    FILE* file = fopen(nama_file, "r");
    if (file == NULL) {
        printf("?? Belum ada riwayat pesanan untuk hari ini.\n");
        printf("File: %s\n", nama_file);
    } else {
        char line[500];
        int ada_data = 0;
        
        while (fgets(line, sizeof(line), file) != NULL) {
            printf("%s", line);
            ada_data = 1;
        }
        
        if (!ada_data) {
            printf("?? Belum ada riwayat pesanan untuk hari ini.\n");
        }
        
        fclose(file);
    }
    
    printf("\nTekan Enter untuk kembali ke menu utama...");
    getchar();
}
