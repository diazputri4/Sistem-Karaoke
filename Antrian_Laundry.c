#include "Antrian_Laundry.h"

const char* nama_paket[] = {
    "Reguler Wash (1 hari)",
    "Premium Wash (6 jam)",
    "Repairment (2 hari)",
    "Repaint (3 hari)"
};

const int durasi_paket[] = {
    86400,  // 1 hari dalam detik
    21600,  // 6 jam dalam detik
    172800, // 2 hari dalam detik
    259200  // 3 hari dalam detik
};

int isEmpty(antrian_laundry * cek) {
    if (cek != NULL) {
        return 0; // Antrian tidak kosong
    } else {
        return 1; // Antrian kosong
    }
}

int isDigit(char c) {
    return (c >= '0' && c <= '9'); // Cek apakah karakter adalah digit
}

void clean_stdin(char * buffer) {
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0'; // Hapus newline
    }
}

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

void input_data(antrian_laundry ** hasil) {
    antrian_laundry * new = (antrian_laundry *)malloc(sizeof(antrian_laundry));
    if (new == NULL) {
        printf("Alokasi memori gagal!\n");
        *hasil = NULL;
        return;
    }

    char buffer[100];
    printf("\n\nNama: ");
    fgets(buffer, sizeof(buffer), stdin);
    clean_stdin(buffer);
    strncpy(new->nama_pelanggan, buffer, sizeof(new->nama_pelanggan) - 1);
    new->nama_pelanggan[sizeof(new->nama_pelanggan) - 1] = '\0'; // Pastikan null-terminated

    int valid = 0;
    while (!valid) {
        printf("Nomor telepon: ");
        fgets(buffer, sizeof(buffer), stdin);
        clean_stdin(buffer);
        if (validasi_nomor_hp(buffer)) {
            strncpy(new->no_telp, buffer, sizeof(new->no_telp) - 1);
            new->no_telp[sizeof(new->no_telp) - 1] = '\0';
            valid = 1;
        } else {
            printf("Nomor telepon tidak valid. Harus diawali dengan '08' dan panjang 11-13 digit.\n");
        }
    }

    printf("Alamat: ");
    fgets(buffer, sizeof(buffer), stdin);
    clean_stdin(buffer);
    strncpy(new->alamat, buffer, sizeof(new->alamat) - 1);
    new->alamat[sizeof(new->alamat) - 1] = '\0'; // Pastikan null-terminated

    // Tambahan untuk paket
    tampilkan_menu_layanan();
    printf("\n\nPilihan: ");
    int pilihan_paket;
    scanf("%d", &pilihan_paket);
    getchar();
    
    if (pilihan_paket < 1 || pilihan_paket > 4) {
        printf("Pilihan tidak valid!\n");
        free(new);
        *hasil = NULL;
        return;
    }
    
    new->paket = pilihan_paket - 1;
    generate_id(new->id);
    new->waktu_pesan = time(NULL);
    new->waktu_selesai = new->waktu_pesan + durasi_paket[new->paket];
    new->sudah_selesai = false;
    new->nextnode = NULL;
    printf("Pesanan berhasil dibuat! ID Anda: %s\n", new->id);
    *hasil = new;
}

// Tambahkan deklarasi 5 antrian terpisah
antrian_laundry *antrian_reguler = NULL;
antrian_laundry *antrian_premium = NULL;
antrian_laundry *antrian_repairment = NULL;
antrian_laundry *antrian_repaint = NULL;
antrian_laundry *global_pesanan_baru = NULL;

void enqueue() {
    antrian_laundry *newantrian = NULL;
    input_data(&newantrian);
    if (newantrian == NULL) {
        return;
    }
    
    global_pesanan_baru = newantrian;
    // Menambahkan ke antrian yang sesuai berdasarkan paket
    switch (newantrian->paket) {
        case REGULER:
            if (isEmpty(antrian_reguler)) {
                antrian_reguler = newantrian;
            } else {
                antrian_laundry *sementara = antrian_reguler;
                while (sementara->nextnode != NULL) {
                    sementara = sementara->nextnode;
                }
                sementara->nextnode = newantrian;
            }
            break;
        case PREMIUM:
            if (isEmpty(antrian_premium)) {
                antrian_premium = newantrian;
            } else {
                antrian_laundry *sementara = antrian_premium;
                while (sementara->nextnode != NULL) {
                    sementara = sementara->nextnode;
                }
                sementara->nextnode = newantrian;
            }
            break;
        case REPAIRMENT:
            if (isEmpty(antrian_repairment)) {
                antrian_repairment = newantrian;
            } else {
                antrian_laundry *sementara = antrian_repairment;
                while (sementara->nextnode != NULL) {
                    sementara = sementara->nextnode;
                }
                sementara->nextnode = newantrian;
            }
            break;
        case REPAINT:
            if (isEmpty(antrian_repaint)) {
                antrian_repaint = newantrian;
            } else {
                antrian_laundry *sementara = antrian_repaint;
                while (sementara->nextnode != NULL) {
                    sementara = sementara->nextnode;
                }
                sementara->nextnode = newantrian;
            }
            break;
    }
}

void dequeue(antrian_laundry ** del) {
    if (isEmpty(*del)) {
        printf("\nAntrian sudah kosong!\n");
        return;
    }
    printf("\nMenghapus Antrian: %s\n", (*del)->nama_pelanggan);
    antrian_laundry * temp = *del;
    *del = (*del)->nextnode;
    free(temp);
}

// Tambahkan fungsi helper untuk menampilkan antrian berdasarkan kategori
void tampilkan_antrian_kategori(antrian_laundry *antrian, const char* kategori) {
    printf("\n Antrian %s \n", kategori);
    if (isEmpty(antrian)) {
        printf("Antrian kosong!\n");
        return;
    }
    
    antrian_laundry * current = antrian;
    int count = 1;
    printf("\n=========================================================================");
    while (current != NULL) {
        // Ensure strings are properly terminated
        char nama[31] = {0};  // +1 for null terminator
        char no_telp[15] = {0};  // +1 for null terminator
        char alamat[51] = {0};  // +1 for null terminator
        
        strncpy(nama, current->nama_pelanggan, sizeof(nama) - 1);
        strncpy(no_telp, current->no_telp, sizeof(no_telp) - 1);
        strncpy(alamat, current->alamat, sizeof(alamat) - 1);
        
        printf("\n%d. %s - %s - %s", count, nama, no_telp, alamat);
        printf("\n   Paket: %s", nama_paket[current->paket]);
        printf("\n   Waktu pemesanan: ");
        tampilkan_waktu(current->waktu_pesan);
        printf("\n   Estimasi selesai: ");
        tampilkan_waktu(current->waktu_selesai);
        printf("\n   Status: %s", current->sudah_selesai ? "SELESAI" : 
               (time(NULL) >= current->waktu_selesai ? "MENUNGGU PENGAMBILAN" : "DALAM PROSES"));
        current = current->nextnode;
        count++;
        printf("\n=========================================================================");
    }
}

// Modifikasi fungsi display_antrian untuk menggunakan fungsi helper
void display_antrian() {
    tampilan_antrian();
    
    // Tampilkan semua antrian menggunakan fungsi helper
    tampilkan_antrian_kategori(antrian_reguler, "Reguler Wash");
    tampilkan_antrian_kategori(antrian_premium, "Premium Wash");
    tampilkan_antrian_kategori(antrian_repairment, "Repairment");
    tampilkan_antrian_kategori(antrian_repaint, "Repaint");
}

// Fungsi-fungsi baru dari Queue_Sepatu
void tampilkan_waktu(time_t waktu) {
    struct tm *info_waktu = localtime(&waktu);
    char buffer[20];
    strftime(buffer, 20, "%d/%m/%Y %H:%M", info_waktu);
    printf("%s", buffer);
}

void perbarui_status_pesanan(antrian_laundry ** awal) {
    // Update status di semua antrian
    antrian_laundry * current;
    
    // Update antrian reguler
    current = antrian_reguler;
    while (current != NULL) {
        if (!current->sudah_selesai && time(NULL) >= current->waktu_selesai) {
            current->sudah_selesai = true;
        }
        current = current->nextnode;
    }
    
    // Update antrian premium
    current = antrian_premium;
    while (current != NULL) {
        if (!current->sudah_selesai && time(NULL) >= current->waktu_selesai) {
            current->sudah_selesai = true;
        }
        current = current->nextnode;
    }
    
    // Update antrian repairment
    current = antrian_repairment;
    while (current != NULL) {
        if (!current->sudah_selesai && time(NULL) >= current->waktu_selesai) {
            current->sudah_selesai = true;
        }
        current = current->nextnode;
    }
    
    // Update antrian repaint
    current = antrian_repaint;
    while (current != NULL) {
        if (!current->sudah_selesai && time(NULL) >= current->waktu_selesai) {
            current->sudah_selesai = true;
        }
        current = current->nextnode;
    }
}

// Fungsi untuk dealokasi memori antrian
void dealokasi_antrian() {
    antrian_laundry* current;
    antrian_laundry* temp;

    // Dealokasi antrian reguler
    current = antrian_reguler;
    while (current != NULL) {
        temp = current;
        current = current->nextnode;
        free(temp);
    }
    antrian_reguler = NULL;

    // Dealokasi antrian premium
    current = antrian_premium;
    while (current != NULL) {
        temp = current;
        current = current->nextnode;
        free(temp);
    }
    antrian_premium = NULL;

    // Dealokasi antrian repairment
    current = antrian_repairment;
    while (current != NULL) {
        temp = current;
        current = current->nextnode;
        free(temp);
    }
    antrian_repairment = NULL;

    // Dealokasi antrian repaint
    current = antrian_repaint;
    while (current != NULL) {
        temp = current;
        current = current->nextnode;
        free(temp);
    }
    antrian_repaint = NULL;

    // Dealokasi global pesanan baru jika masih ada
    if (global_pesanan_baru != NULL) {
        free(global_pesanan_baru);
        global_pesanan_baru = NULL;
    }
}

// Helper function untuk membaca satu node antrian
antrian_laundry* read_queue_node(FILE* file) {
    antrian_laundry* new_node = (antrian_laundry*)malloc(sizeof(antrian_laundry));
    if (new_node == NULL) {
        printf("Error: Alokasi memori gagal\n");
        return NULL;
    }

    // Baca data node
    if (fread(new_node->id, sizeof(char), 8, file) != 8) {
        free(new_node);
        return NULL;
    }
    new_node->id[8] = '\0';

    if (fread(new_node->nama_pelanggan, sizeof(char), 30, file) != 30) {
        free(new_node);
        return NULL;
    }
    new_node->nama_pelanggan[29] = '\0';

    if (fread(new_node->no_telp, sizeof(char), 14, file) != 14) {
        free(new_node);
        return NULL;
    }
    new_node->no_telp[13] = '\0';

    if (fread(new_node->alamat, sizeof(char), 50, file) != 50) {
        free(new_node);
        return NULL;
    }
    new_node->alamat[49] = '\0';

    if (fread(&new_node->paket, sizeof(Jenis_Paket), 1, file) != 1) {
        free(new_node);
        return NULL;
    }
    if (fread(&new_node->waktu_pesan, sizeof(time_t), 1, file) != 1) {
        free(new_node);
        return NULL;
    }
    if (fread(&new_node->waktu_selesai, sizeof(time_t), 1, file) != 1) {
        free(new_node);
        return NULL;
    }
    if (fread(&new_node->sudah_selesai, sizeof(bool), 1, file) != 1) {
        free(new_node);
        return NULL;
    }

    new_node->nextnode = NULL;
    return new_node;
}

// Fungsi untuk menyimpan antrian ke file
void save_queue_to_file() {
    FILE* file = fopen("data/queue.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file antrian untuk penulisan\n");
        return;
    }

    // Simpan setiap antrian
    antrian_laundry* current;
    
    // Simpan antrian reguler
    current = antrian_reguler;
    while (current != NULL) {
        fwrite(current->id, sizeof(char), 8, file);
        fwrite(current->nama_pelanggan, sizeof(char), 30, file);
        fwrite(current->no_telp, sizeof(char), 14, file);
        fwrite(current->alamat, sizeof(char), 50, file);
        fwrite(&current->paket, sizeof(Jenis_Paket), 1, file);
        fwrite(&current->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->waktu_selesai, sizeof(time_t), 1, file);
        fwrite(&current->sudah_selesai, sizeof(bool), 1, file);
        current = current->nextnode;
    }
    // Tulis penanda akhir antrian reguler
    char end_marker = '\0';
    fwrite(&end_marker, sizeof(char), 1, file);

    // Simpan antrian premium
    current = antrian_premium;
    while (current != NULL) {
        fwrite(current->id, sizeof(char), 8, file);
        fwrite(current->nama_pelanggan, sizeof(char), 30, file);
        fwrite(current->no_telp, sizeof(char), 14, file);
        fwrite(current->alamat, sizeof(char), 50, file);
        fwrite(&current->paket, sizeof(Jenis_Paket), 1, file);
        fwrite(&current->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->waktu_selesai, sizeof(time_t), 1, file);
        fwrite(&current->sudah_selesai, sizeof(bool), 1, file);
        current = current->nextnode;
    }
    fwrite(&end_marker, sizeof(char), 1, file);

    // Simpan antrian repairment
    current = antrian_repairment;
    while (current != NULL) {
        fwrite(current->id, sizeof(char), 8, file);
        fwrite(current->nama_pelanggan, sizeof(char), 30, file);
        fwrite(current->no_telp, sizeof(char), 14, file);
        fwrite(current->alamat, sizeof(char), 50, file);
        fwrite(&current->paket, sizeof(Jenis_Paket), 1, file);
        fwrite(&current->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->waktu_selesai, sizeof(time_t), 1, file);
        fwrite(&current->sudah_selesai, sizeof(bool), 1, file);
        current = current->nextnode;
    }
    fwrite(&end_marker, sizeof(char), 1, file);

    // Simpan antrian repaint
    current = antrian_repaint;
    while (current != NULL) {
        fwrite(current->id, sizeof(char), 8, file);
        fwrite(current->nama_pelanggan, sizeof(char), 30, file);
        fwrite(current->no_telp, sizeof(char), 14, file);
        fwrite(current->alamat, sizeof(char), 50, file);
        fwrite(&current->paket, sizeof(Jenis_Paket), 1, file);
        fwrite(&current->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->waktu_selesai, sizeof(time_t), 1, file);
        fwrite(&current->sudah_selesai, sizeof(bool), 1, file);
        current = current->nextnode;
    }
    fwrite(&end_marker, sizeof(char), 1, file);

    fclose(file);
}

// Fungsi untuk memuat antrian dari file
void load_queue_from_file() {
    FILE* file = fopen("data/queue.dat", "rb");
    if (file == NULL) {
        printf("File antrian tidak ditemukan. Memulai dengan antrian kosong.\n");
        return;
    }

    // Dealokasi antrian yang ada
    dealokasi_antrian();

    // Baca antrian reguler
    while (1) {
        char marker;
        if (fread(&marker, sizeof(char), 1, file) != 1 || marker == '\0') {
            break;
        }
        fseek(file, -1, SEEK_CUR); // Kembali satu byte

        antrian_laundry* new_node = read_queue_node(file);
        if (new_node == NULL) break;

        if (antrian_reguler == NULL) {
            antrian_reguler = new_node;
        } else {
            antrian_laundry* current = antrian_reguler;
            while (current->nextnode != NULL) {
                current = current->nextnode;
            }
            current->nextnode = new_node;
        }
    }

    // Baca antrian premium
    while (1) {
        char marker;
        if (fread(&marker, sizeof(char), 1, file) != 1 || marker == '\0') {
            break;
        }
        fseek(file, -1, SEEK_CUR);

        antrian_laundry* new_node = read_queue_node(file);
        if (new_node == NULL) break;

        if (antrian_premium == NULL) {
            antrian_premium = new_node;
        } else {
            antrian_laundry* current = antrian_premium;
            while (current->nextnode != NULL) {
                current = current->nextnode;
            }
            current->nextnode = new_node;
        }
    }

    // Baca antrian repairment
    while (1) {
        char marker;
        if (fread(&marker, sizeof(char), 1, file) != 1 || marker == '\0') {
            break;
        }
        fseek(file, -1, SEEK_CUR);

        antrian_laundry* new_node = read_queue_node(file);
        if (new_node == NULL) break;

        if (antrian_repairment == NULL) {
            antrian_repairment = new_node;
        } else {
            antrian_laundry* current = antrian_repairment;
            while (current->nextnode != NULL) {
                current = current->nextnode;
            }
            current->nextnode = new_node;
        }
    }

    // Baca antrian repaint
    while (1) {
        char marker;
        if (fread(&marker, sizeof(char), 1, file) != 1 || marker == '\0') {
            break;
        }
        fseek(file, -1, SEEK_CUR);

        antrian_laundry* new_node = read_queue_node(file);
        if (new_node == NULL) break;

        if (antrian_repaint == NULL) {
            antrian_repaint = new_node;
        } else {
            antrian_laundry* current = antrian_repaint;
            while (current->nextnode != NULL) {
                current = current->nextnode;
            }
            current->nextnode = new_node;
        }
    }

    fclose(file);
}

void show_notification(const char* customer_name, const char* service_type, char* message, char* title) {
        printf(message, "Pesanan dari %s (%s) telah selesai dan telah dihapus dari antrian.", 
                customer_name, service_type);
        printf(title, "Pesanan Selesai");
        MessageBox(NULL, message, title, MB_OK | MB_ICONINFORMATION);
    }

// Fungsi untuk auto-dequeue pesanan yang sudah selesai
void auto_dequeue_completed() {
    antrian_laundry* current;
    antrian_laundry* prev;
    char message[256];
    char title[64];
    
    // Cek dan dequeue antrian reguler
    current = antrian_reguler;
    prev = NULL;
    while (current != NULL) {
        if (current->sudah_selesai) {
            if (prev == NULL) {
                antrian_reguler = current->nextnode;
            } else {
                prev->nextnode = current->nextnode;
            }
            show_notification(current->nama_pelanggan, "Reguler Wash", message, title);
            antrian_laundry* temp = current;
            current = current->nextnode;
            free(temp);
        } else {
            prev = current;
            current = current->nextnode;
        }
    }
    
    // Cek dan dequeue antrian premium
    current = antrian_premium;
    prev = NULL;
    while (current != NULL) {
        if (current->sudah_selesai) {
            if (prev == NULL) {
                antrian_premium = current->nextnode;
            } else {
                prev->nextnode = current->nextnode;
            }
            show_notification(current->nama_pelanggan, "Premium Wash", message, title);
            antrian_laundry* temp = current;
            current = current->nextnode;
            free(temp);
        } else {
            prev = current;
            current = current->nextnode;
        }
    }
    
    // Cek dan dequeue antrian repairment
    current = antrian_repairment;
    prev = NULL;
    while (current != NULL) {
        if (current->sudah_selesai) {
            if (prev == NULL) {
                antrian_repairment = current->nextnode;
            } else {
                prev->nextnode = current->nextnode;
            }
            show_notification(current->nama_pelanggan, "Repairment", message, title);
            antrian_laundry* temp = current;
            current = current->nextnode;
            free(temp);
        } else {
            prev = current;
            current = current->nextnode;
        }
    }
    
    // Cek dan dequeue antrian repaint
    current = antrian_repaint;
    prev = NULL;
    while (current != NULL) {
        if (current->sudah_selesai) {
            if (prev == NULL) {
                antrian_repaint = current->nextnode;
            } else {
                prev->nextnode = current->nextnode;
            }
            show_notification(current->nama_pelanggan, "Repaint", message, title);
            antrian_laundry* temp = current;
            current = current->nextnode;
            free(temp);
        } else {
            prev = current;
            current = current->nextnode;
        }
    }
}



void tampilkan_status_semua_pesanan() {
    const char* tipe_layanan[] = {"REGULER", "PREMIUM", "REPAIRMENT", "REPAINT"};
    antrian_laundry* antrian[] = {antrian_reguler, antrian_premium, antrian_repairment, antrian_repaint};

    printf("=====================================\n");
    for (int i = 0; i < 4; i++) {
        printf("Tipe Layanan: %s\n", tipe_layanan[i]);
        antrian_laundry* curr = antrian[i];
        if (curr == NULL) {
            printf("Tidak ada pesanan.\n");
        }
        while (curr != NULL) {
            printf("ID     : %s\n", curr->id);
            printf("Nama   : %s\n", curr->nama_pelanggan);

            time_t now = time(NULL);
            if (!curr->sudah_selesai && now < curr->waktu_selesai) {
                printf("Status : Dalam Proses\n");
            } else if (!curr->sudah_selesai && now >= curr->waktu_selesai) {
                printf("Status : Selesai\n");
            } else if (curr->sudah_selesai) {
                printf("Status : Menunggu Pengambilan\n");
            }
            printf("-------------------------------------\n");
            curr = curr->nextnode;
        }
    }
    printf("=====================================\n");
    getchar();
}

void edit_status_pengambilan() {
    char id[9];
    int found = 0;
    printf("Masukkan ID pesanan yang ingin diubah statusnya menjadi 'Selesai' dan dikeluarkan dari antrian: ");
    scanf("%8s", id);
    getchar();

    antrian_laundry* *antrians[] = {&antrian_reguler, &antrian_premium, &antrian_repairment, &antrian_repaint};
    for (int i = 0; i < 4; i++) {
        antrian_laundry **head = antrians[i];
        antrian_laundry *curr = *head;
        antrian_laundry *prev = NULL;
        while (curr != NULL) {
            if (strcmp(curr->id, id) == 0 && curr->sudah_selesai) {
                // Hapus node dari linked list
                if (prev == NULL) {
                    *head = curr->nextnode;
                } else {
                    prev->nextnode = curr->nextnode;
                }
                free(curr);
                printf("Status pesanan dengan ID %s berhasil diubah menjadi 'Selesai' dan dikeluarkan dari antrian.\n", id);
                found = 1;
                break;
            }
            prev = curr;
            curr = curr->nextnode;
        }
        if (found) break;
    }
    if (!found) {
        printf("Pesanan dengan ID %s tidak ditemukan atau belum berstatus 'Menunggu Pengambilan'.\n", id);
    }
    printf("Tekan Enter untuk kembali ke menu utama...");
    getchar();
}

