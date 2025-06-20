#include "History.h"
#include "Tampilan.h"

// Global variable definition
history_node* history_head = NULL;

// Array untuk nama paket
const char* nama_paket_history[] = {
    "Reguler Wash (1 hari)",
    "Premium Wash (6 jam)",
    "Repairment (2 hari)",
    "Repaint (3 hari)"
};

// Fungsi untuk mengecek dan menjalankan auto-delete jika diperlukan
void check_and_run_auto_delete(history_node** history_head) {
    FILE* file = fopen("data/last_cleanup.dat", "rb");
    if (file == NULL) {
        // Jika file tidak ada, buat file baru dan jalankan cleanup
        auto_delete_old_history(history_head);
        return;
    }

    time_t last_cleanup;
    fread(&last_cleanup, sizeof(time_t), 1, file);
    fclose(file);

    time_t current_time = time(NULL);
    // Jika sudah lebih dari 24 jam sejak cleanup terakhir
    if (current_time - last_cleanup >= 24 * 60 * 60) {
        auto_delete_old_history(history_head);
    }
}

// Fungsi untuk menghapus history yang lebih dari 7 hari
void auto_delete_old_history(history_node** history_head) {
    if (*history_head == NULL) return;

    time_t current_time = time(NULL);
    time_t cutoff_time = current_time - (7 * 24 * 60 * 60); // 7 hari dalam detik

    // Hapus node dari awal yang lebih tua dari cutoff_time
    while (*history_head != NULL && (*history_head)->data.datastruk->waktu_pesan < cutoff_time) {
        history_node* temp = *history_head;
        *history_head = (*history_head)->next;
        free(temp->data.datastruk);
        free(temp);
    }

    // Hapus node yang lebih tua dari cutoff_time di tengah atau akhir list
    history_node* current = *history_head;
    while (current != NULL && current->next != NULL) {
        if (current->next->data.datastruk->waktu_pesan < cutoff_time) {
            history_node* temp = current->next;
            current->next = temp->next;
            free(temp->data.datastruk);
            free(temp);
        } else {
            current = current->next;
        }
    }

    // Update waktu cleanup terakhir
    FILE* file = fopen("data/last_cleanup.dat", "wb");
    if (file != NULL) {
        time_t now = time(NULL);
        fwrite(&now, sizeof(time_t), 1, file);
        fclose(file);
    }
}

void display_history(history_node** history_head_ptr) {
    check_and_run_auto_delete(history_head_ptr);
    int i, j;
    
    history_node* history_head = *history_head_ptr;
    
    if (history_head == NULL) {
        printf("\nTidak ada riwayat pesanan.\n");
        return;
    }

    // Buat array untuk menyimpan pointer ke node
    int total_entries = count_history_entries(history_head);
    history_node** nodes = (history_node**)malloc(total_entries * sizeof(history_node*));
    if (nodes == NULL) {
        printf("Error: Alokasi memori gagal\n");
        return;
    }

    // Isi array dengan pointer ke node
    history_node* current = history_head;
    for (i = 0; i < total_entries; i++) {
        nodes[i] = current;
        current = current->next;
    }

    // Urutkan array berdasarkan ID secara descending
    for (i = 0; i < total_entries - 1; i++) {
        for (j = 0; j < total_entries - i - 1; j++) {
            if (strcmp(nodes[j]->data.datastruk->id, nodes[j + 1]->data.datastruk->id) < 0) {
                history_node* temp = nodes[j];
                nodes[j] = nodes[j + 1];
                nodes[j + 1] = temp;
            }
        }
    }

    // Inisialisasi variabel untuk paginasi
    int current_page = 0;
    int entries_per_page = 3;
    int total_pages = (total_entries + entries_per_page - 1) / entries_per_page;
    char choice;

    while (1) {
        system("cls");
        tampilkan_history();
        printf("\n\nHalaman %d dari %d\n\n", current_page + 1, total_pages);

        // Menampilkan entri untuk halaman saat ini
        int start_idx = current_page * entries_per_page;
        int end_idx = start_idx + entries_per_page;
        if (end_idx > total_entries) {
            end_idx = total_entries;
        }

        // Menampilkan entri untuk halaman saat ini
        for (i = start_idx; i < end_idx; i++) {
            printf("+======================================================+");
            printf("\n%d. ID: %s", i + 1, nodes[i]->data.datastruk->id);
            printf("\n   Nama: %s", nodes[i]->data.datastruk->nama_pelanggan);
            printf("\n   No. Telp: %s", nodes[i]->data.datastruk->no_telp);
            printf("\n   Alamat: %s", nodes[i]->data.datastruk->alamat);
            printf("\n   Paket: %s", nama_paket_history[nodes[i]->data.datastruk->paket]);
            printf("\n   Metode Pembayaran: ");
            switch (nodes[i]->data.metode - 1) {
                case TUNAI:
                    printf("Tunai");
                    break;
                case TRANSFER:
                    printf("Transfer Bank");
                    break;
                case EWALLET:
                    printf("E-Wallet");
                    break;
            }
            printf("\n   Total Pembayaran: Rp %d", nodes[i]->data.harga);
            printf("\n   Waktu Pesan: %s", ctime(&nodes[i]->data.datastruk->waktu_pesan));
            printf("   Waktu Selesai: %s", ctime(&nodes[i]->data.datastruk->waktu_selesai));
            printf("+======================================================+\n");
        }

        // Menampilkan opsi navigasi
        printf("\nNavigasi:\n");
        if (current_page > 0) {
            printf("b - Halaman sebelumnya\n");
        }
        if (current_page < total_pages - 1) {
            printf("n - Halaman berikutnya\n");
        }
        printf("q - Kembali ke menu utama\n");
        printf("\nPilihan: ");

        choice = getch();
        printf("%c\n", choice);

        // Memproses input navigasi pengguna
        switch (choice) {
            case 'n':
            case 'N':
                if (current_page < total_pages - 1) {
                    current_page++;
                } else {
                    printf("\nAnda sudah di halaman terakhir!\n");
                    getch();
                }
                break;
            case 'b':
            case 'B':
                if (current_page > 0) {
                    current_page--;
                } else {
                    printf("\nAnda sudah di halaman pertama!\n");
                    getch();
                }
                break;
            case 'q':
            case 'Q':
                free(nodes);
                return;
            default:
                printf("\nPilihan tidak valid!\n");
                getch();
                break;
        }
    }
}

// Fungsi untuk menghitung jumlah entri dalam history
int count_history_entries(history_node* head) {
    int count = 0;
    history_node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Fungsi untuk menyimpan history ke file
void save_to_file(history_node* history_head) {
    FILE* file = fopen("data/history.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk penulisan\n");
        return;
    }

    history_node* current = history_head;
    while (current != NULL) {
        // Save pesanan data
        fwrite(&current->data.metode, sizeof(metode_pembayaran), 1, file);
        fwrite(&current->data.harga, sizeof(int), 1, file);
        
        // Save antrian_laundry data with correct sizes
        fwrite(current->data.datastruk->id, sizeof(char), 8, file);
        fwrite(current->data.datastruk->nama_pelanggan, sizeof(char), 30, file);
        fwrite(current->data.datastruk->no_telp, sizeof(char), 14, file);
        fwrite(current->data.datastruk->alamat, sizeof(char), 50, file);
        fwrite(&current->data.datastruk->paket, sizeof(Jenis_Paket), 1, file);
        fwrite(&current->data.datastruk->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->data.datastruk->waktu_selesai, sizeof(time_t), 1, file);
        fwrite(&current->data.datastruk->sudah_selesai, sizeof(bool), 1, file);
        
        // Save additional pesanan fields
        fwrite(current->data.nama_layanan, sizeof(char), 100, file);
        fwrite(&current->data.jumlah, sizeof(int), 1, file);
        fwrite(&current->data.harga_satuan, sizeof(int), 1, file);
        fwrite(&current->data.subtotal, sizeof(int), 1, file);
        fwrite(&current->data.diskon, sizeof(int), 1, file);
        fwrite(&current->data.estimasi_hari, sizeof(int), 1, file);
        
        current = current->next;
    }

    fclose(file);
}

// Fungsi untuk memuat history dari file
void load_from_file(history_node** history_head) {
    FILE* file = fopen("data/history.dat", "rb");
    if (file == NULL) {
        printf("File riwayat tidak ditemukan. Memulai dengan riwayat kosong.\n");
        return;
    }

    // Membersihkan history yang ada
    free_history(history_head);

    while (1) {
        // Alokasi node baru untuk history
        history_node* new_node = (history_node*)malloc(sizeof(history_node));
        if (new_node == NULL) {
            printf("Error: Alokasi memori gagal\n");
            fclose(file);
            return;
        }

        // Alokasi node baru untuk antrian_laundry (untuk history)
        antrian_laundry* history_antrian = (antrian_laundry*)malloc(sizeof(antrian_laundry));
        if (history_antrian == NULL) {
            printf("Error: Alokasi memori gagal\n");
            free(new_node);
            fclose(file);
            return;
        }

        // Initialize the history_antrian
        memset(history_antrian, 0, sizeof(antrian_laundry));
        history_antrian->nextnode = NULL; // Ensure it's not linked to any queue

        // Baca data pesanan
        if (fread(&new_node->data.metode, sizeof(metode_pembayaran), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.harga, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }

        // Baca data antrian_laundry dengan ukuran yang benar
        if (fread(history_antrian->id, sizeof(char), 8, file) != 8) {
            free(history_antrian);
            free(new_node);
            break;
        }
        history_antrian->id[8] = '\0';

        if (fread(history_antrian->nama_pelanggan, sizeof(char), 30, file) != 30) {
            free(history_antrian);
            free(new_node);
            break;
        }
        history_antrian->nama_pelanggan[29] = '\0';

        if (fread(history_antrian->no_telp, sizeof(char), 14, file) != 14) {
            free(history_antrian);
            free(new_node);
            break;
        }
        history_antrian->no_telp[13] = '\0';

        if (fread(history_antrian->alamat, sizeof(char), 50, file) != 50) {
            free(history_antrian);
            free(new_node);
            break;
        }
        history_antrian->alamat[49] = '\0';

        if (fread(&history_antrian->paket, sizeof(Jenis_Paket), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&history_antrian->waktu_pesan, sizeof(time_t), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&history_antrian->waktu_selesai, sizeof(time_t), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&history_antrian->sudah_selesai, sizeof(bool), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }

        // Baca additional pesanan fields
        if (fread(new_node->data.nama_layanan, sizeof(char), 100, file) != 100) {
            free(history_antrian);
            free(new_node);
            break;
        }
        new_node->data.nama_layanan[99] = '\0';

        if (fread(&new_node->data.jumlah, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.harga_satuan, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.subtotal, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.diskon, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.estimasi_hari, sizeof(int), 1, file) != 1) {
            free(history_antrian);
            free(new_node);
            break;
        }

        // Set pointer datastruk to the history-specific antrian_laundry
        new_node->data.datastruk = history_antrian;
        new_node->next = NULL;

        // Add to history list
        if (*history_head == NULL) {
            *history_head = new_node;
        } else {
            new_node->next = *history_head;
            *history_head = new_node;
        }
    }

    fclose(file);
}

// Fungsi untuk membebaskan memori history
void free_history(history_node** history_head) {
    history_node* current = *history_head;
    while (current != NULL) {
        history_node* temp = current;
        current = current->next;
        free(temp->data.datastruk);
        free(temp);
    }
    *history_head = NULL;
}

// Fungsi untuk menyimpan history baru
void save_history(history_node** history_head, pesanan* order) {
    if (order == NULL || order->datastruk == NULL) {
        printf("Error: Tidak ada data pesanan untuk disimpan\n");
        return;
    }

    history_node* new_node = (history_node*)malloc(sizeof(history_node));
    if (new_node == NULL) {
        printf("Error: Alokasi memori gagal\n");
        return;
    }

    // Create a deep copy of the antrian_laundry data
    antrian_laundry* history_antrian = (antrian_laundry*)malloc(sizeof(antrian_laundry));
    if (history_antrian == NULL) {
        printf("Error: Alokasi memori gagal\n");
        free(new_node);
        return;
    }

    // Copy all data from the original antrian_laundry
    memcpy(history_antrian, order->datastruk, sizeof(antrian_laundry));
    history_antrian->nextnode = NULL; // Ensure it's not linked to any queue

    // Copy the pesanan data
    new_node->data = *order;
    new_node->data.datastruk = history_antrian; // Use the copied antrian_laundry
    new_node->next = NULL;

    // Add to history list
    if (*history_head == NULL) {
        *history_head = new_node;
    } else {
        new_node->next = *history_head;
        *history_head = new_node;
    }

    // Save to file
    save_to_file(*history_head);
}

// Fungsi debug untuk testing auto-delete
void debug_auto_delete() {
    printf("=== DEBUG AUTO DELETE ===\n");
    
    time_t current_time = time(NULL);
    time_t cutoff_time = current_time - (7 * 24 * 60 * 60);
    
    printf("Waktu sekarang: %s", ctime(&current_time));
    printf("Cutoff time (7 hari lalu): %s", ctime(&cutoff_time));
    
    // Cek file last_cleanup.dat
    FILE* file = fopen("data/last_cleanup.dat", "rb");
    if (file != NULL) {
        time_t last_cleanup;
        fread(&last_cleanup, sizeof(time_t), 1, file);
        fclose(file);
        printf("Last cleanup: %s", ctime(&last_cleanup));
        
        if (current_time >= last_cleanup) {
            printf("Status: PERLU CLEANUP\n");
        } else {
            printf("Status: BELUM PERLU CLEANUP\n");
        }
    } else {
        printf("File last_cleanup.dat tidak ditemukan\n");
    }
    
    // Cek history yang akan dihapus
    history_node* current = history_head;
    int count_to_delete = 0;
    while (current != NULL) {
        if (current->data.datastruk->waktu_pesan < cutoff_time) {
            count_to_delete++;
            printf("Data lama ditemukan - ID: %s, Waktu: %s", 
                   current->data.datastruk->id, 
                   ctime(&current->data.datastruk->waktu_pesan));
        }
        current = current->next;
    }
    
    printf("Total data yang akan dihapus: %d\n", count_to_delete);
    printf("=== END DEBUG ===\n");
}

// Fungsi untuk force delete history lama
void force_delete_old_history() {
    printf("Force delete - menghapus data lebih dari 7 hari...\n");
    auto_delete_old_history(&history_head);
    printf("Force delete selesai.\n");
}

// Fungsi untuk reset cleanup timer
void reset_cleanup_timer() {
    FILE* file = fopen("data/last_cleanup.dat", "wb");
    if (file != NULL) {
        time_t now = time(NULL) - 1; // Set ke 1 detik lalu agar cleanup langsung berjalan
        fwrite(&now, sizeof(time_t), 1, file);
        fclose(file);
        printf("Cleanup timer telah direset.\n");
    }
}
