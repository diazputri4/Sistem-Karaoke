#include "History.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

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

// Fungsi untuk mendapatkan ID terakhir dari history
int get_last_id() {
    if (history_head == NULL) {
        return 0;
    }
    
    // Mencari ID tertinggi dalam history
    int highest_id = 0;
    history_node* current = history_head;
    while (current != NULL) {
        if (current->id > highest_id) {
            highest_id = current->id;
        }
        current = current->next;
    }
    return highest_id;
}

// Menyimpan entri baru ke dalam riwayat
// Menerima pointer ke head riwayat dan data pesanan yang akan disimpan
void save_history(history_node** history_head, antrian_laundry* order) {
    if (order == NULL) {
        printf("Error: Tidak ada data pesanan untuk disimpan\n");
        return;
    }

    history_node* new_node = (history_node*)malloc(sizeof(history_node));
    if (new_node == NULL) {
        printf("Error: Alokasi memori gagal\n");
        return;
    }

    // Menyalin data dari struktur antrian_laundry ke history_node
    new_node->id = order->id;
    strncpy(new_node->nama_pelanggan, order->nama_pelanggan, sizeof(new_node->nama_pelanggan) - 1);
    strncpy(new_node->no_telp, order->no_telp, sizeof(new_node->no_telp) - 1);
    strncpy(new_node->alamat, order->alamat, sizeof(new_node->alamat) - 1);
    new_node->paket = order->paket;
    new_node->waktu_pesan = order->waktu_pesan;
    new_node->waktu_selesai = order->waktu_selesai;
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
            if (nodes[j]->id < nodes[j + 1]->id) {
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
            printf("\n%d. ID: %d", i + 1, nodes[i]->id);
            printf("\n   Nama: %s", nodes[i]->nama_pelanggan);
            printf("\n   No. Telp: %s", nodes[i]->no_telp);
            printf("\n   Alamat: %s", nodes[i]->alamat);
            printf("\n   Paket: %s", nama_paket_history[nodes[i]->paket]);
            printf("\n   Waktu Pesan: %s", ctime(&nodes[i]->waktu_pesan));
            printf("   Waktu Selesai: %s", ctime(&nodes[i]->waktu_selesai));
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
        fwrite(current, sizeof(history_node), 1, file);
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

    history_node* current = NULL;
    history_node temp;

    // Membaca data dari file dan membuat node baru untuk setiap entri
    while (fread(&temp, sizeof(history_node), 1, file) == 1) {
        history_node* new_node = (history_node*)malloc(sizeof(history_node));
        if (new_node == NULL) {
            printf("Error: Alokasi memori gagal\n");
            fclose(file);
            return;
        }

        // Menyalin data dari temp ke node baru
        memcpy(new_node, &temp, sizeof(history_node));
        new_node->next = NULL;

        // Menambahkan ke awal linked list
        if (*history_head == NULL) {
            *history_head = new_node;
        } else {
            new_node->next = *history_head;
            *history_head = new_node;
        }
    }

    fclose(file);
}