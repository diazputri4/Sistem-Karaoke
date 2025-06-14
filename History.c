#include "History.h"

// Global variable definition
history_node* history_head = NULL;

// Array untuk nama paket
const char* nama_paket_history[] = {
    "Reguler Wash (1 hari)",
    "Premium Wash (6 jam)",
    "Repairment (2 hari)",
    "Repaint (3 hari)"
};

// Fungsi pembantu untuk menghitung total entri dalam riwayat
// Mengembalikan jumlah total node dalam linked list riwayat
int count_history_entries(history_node* head) {
    int count = 0;
    history_node* current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

// Menyimpan entri baru ke dalam riwayat
// Menerima pointer ke head riwayat dan data pesanan yang akan disimpan
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

    // Menyalin data pesanan ke node baru
    new_node->data = *order;
    new_node->next = NULL;

    // Menambahkan node baru ke awal linked list
    if (*history_head == NULL) {
        *history_head = new_node;
    } else {
        new_node->next = *history_head;
        *history_head = new_node;
    }

    // Menyimpan ke file setelah setiap penambahan entri baru
    save_to_file(*history_head);
}

// Fungsi untuk menampilkan riwayat pesanan dengan sistem paginasi
void display_history(history_node* history_head) {
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
    for (int i = 0; i < total_entries; i++) {
        nodes[i] = current;
        current = current->next;
    }

    // Urutkan array berdasarkan ID secara descending
    for (int i = 0; i < total_entries - 1; i++) {
        for (int j = 0; j < total_entries - i - 1; j++) {
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
        printf("\n=== RIWAYAT PESANAN ===\n");
        printf("Halaman %d dari %d\n\n", current_page + 1, total_pages);

        // Menampilkan entri untuk halaman saat ini
        int start_idx = current_page * entries_per_page;
        int end_idx = start_idx + entries_per_page;
        if (end_idx > total_entries) {
            end_idx = total_entries;
        }

        // Menampilkan entri untuk halaman saat ini
        for (int i = start_idx; i < end_idx; i++) {
            printf("\n=========================================================================");
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
            printf("\n=========================================================================\n");
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

// Membebaskan semua memori yang digunakan oleh linked list riwayat
void free_history(history_node** history_head) {
    history_node* current = *history_head;
    while (current != NULL) {
        history_node* temp = current;
        current = current->next;
        // Tidak perlu membebaskan datastruk karena itu adalah pointer ke node yang sudah ada
        free(temp);
    }
    *history_head = NULL;
}

// Menyimpan seluruh riwayat ke dalam file biner
// File akan berisi semua data riwayat dalam format biner
void save_to_file(history_node* history_head) {
    FILE* file = fopen("data/history.dat", "wb");
    if (file == NULL) {
        printf("Error: Tidak dapat membuka file untuk penulisan\n");
        return;
    }

    history_node* current = history_head;
    while (current != NULL) {
        // Simpan data pesanan
        fwrite(&current->data.metode, sizeof(metode_pembayaran), 1, file);
        fwrite(&current->data.harga, sizeof(int), 1, file);
        
        // Simpan data antrian_laundry
        fwrite(current->data.datastruk->id, sizeof(char), 8, file);
        fwrite(current->data.datastruk->nama_pelanggan, sizeof(char), 50, file);
        fwrite(current->data.datastruk->no_telp, sizeof(char), 15, file);
        fwrite(current->data.datastruk->alamat, sizeof(char), 100, file);
        fwrite(&current->data.datastruk->paket, sizeof(int), 1, file);
        fwrite(&current->data.datastruk->waktu_pesan, sizeof(time_t), 1, file);
        fwrite(&current->data.datastruk->waktu_selesai, sizeof(time_t), 1, file);
        
        current = current->next;
    }

    fclose(file);
}

// Memuat riwayat dari file biner
// Membaca data dari file dan membangun ulang linked list riwayat
void load_from_file(history_node** history_head) {
    FILE* file = fopen("data/history.dat", "rb");
    if (file == NULL) {
        printf("File riwayat tidak ditemukan. Memulai dengan riwayat kosong.\n");
        return;
    }

    // Membersihkan riwayat yang ada
    free_history(history_head);

    while (1) {
        // Alokasi node baru untuk history
        history_node* new_node = (history_node*)malloc(sizeof(history_node));
        if (new_node == NULL) {
            printf("Error: Alokasi memori gagal\n");
            fclose(file);
            return;
        }

        // Alokasi node baru untuk antrian_laundry
        antrian_laundry* new_antrian = (antrian_laundry*)malloc(sizeof(antrian_laundry));
        if (new_antrian == NULL) {
            printf("Error: Alokasi memori gagal\n");
            free(new_node);
            fclose(file);
            return;
        }

        // Baca data pesanan
        if (fread(&new_node->data.metode, sizeof(metode_pembayaran), 1, file) != 1) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_node->data.harga, sizeof(int), 1, file) != 1) {
            free(new_antrian);
            free(new_node);
            break;
        }

        // Baca data antrian_laundry
        if (fread(new_antrian->id, sizeof(char), 8, file) != 8) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(new_antrian->nama_pelanggan, sizeof(char), 50, file) != 50) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(new_antrian->no_telp, sizeof(char), 15, file) != 15) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(new_antrian->alamat, sizeof(char), 100, file) != 100) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_antrian->paket, sizeof(int), 1, file) != 1) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_antrian->waktu_pesan, sizeof(time_t), 1, file) != 1) {
            free(new_antrian);
            free(new_node);
            break;
        }
        if (fread(&new_antrian->waktu_selesai, sizeof(time_t), 1, file) != 1) {
            free(new_antrian);
            free(new_node);
            break;
        }

        // Set pointer datastruk
        new_node->data.datastruk = new_antrian;
        new_node->next = NULL;

        // Tambahkan ke linked list
        if (*history_head == NULL) {
            *history_head = new_node;
        } else {
            new_node->next = *history_head;
            *history_head = new_node;
        }
    }

    fclose(file);
}