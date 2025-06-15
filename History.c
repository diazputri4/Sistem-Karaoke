// Perbaikan 1: Ubah signature fungsi display_history
void display_history(history_node** history_head_ptr) {
    // Gunakan pointer ke pointer agar bisa mengubah global variable
    check_and_run_auto_delete(history_head_ptr);
    
    history_node* history_head = *history_head_ptr; // Deref untuk akses data
    
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

// Perbaikan 2: Ubah signature di header file (History.h)
// void display_history(history_node** history_head_ptr);

// Perbaikan 3: Panggil fungsi dengan pointer ke global variable
// Contoh dalam main.c atau file lain:
// display_history(&history_head);

// Perbaikan 4: Tambahkan fungsi debug untuk testing
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

// Perbaikan 5: Force delete untuk testing
void force_delete_old_history() {
    printf("Force delete - menghapus data lebih dari 7 hari...\n");
    auto_delete_old_history(&history_head);
    printf("Force delete selesai.\n");
}

// Perbaikan 6: Reset cleanup timer untuk testing
void reset_cleanup_timer() {
    FILE* file = fopen("data/last_cleanup.dat", "wb");
    if (file != NULL) {
        time_t now = time(NULL) - 1; // Set ke 1 detik lalu agar cleanup langsung berjalan
        fwrite(&now, sizeof(time_t), 1, file);
        fclose(file);
        printf("Cleanup timer telah direset.\n");
    }
}
