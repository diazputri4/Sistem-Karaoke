#include "Antrian_Laundry.h"

// Konstanta untuk paket
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

int id_pesanan_berikutnya = 1;

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

int validasi_no_telp(const char * nomor) {
    size_t i = 0;
    while (i < strlen(nomor)) {
        if(!isDigit(nomor[i])) {
            return 0; // Tidak valid jika ada karakter non-digit
        }
        i++;
    }
    return 1; // Valid jika hanya berisi digit
}

void input_data(antrian_laundry ** hasil) {
    antrian_laundry * new = (antrian_laundry *)malloc(sizeof(antrian_laundry));
    if (new == NULL) {
        printf("Alokasi memori gagal!\n");
        *hasil = NULL;
        return;
    }

    char buffer[100];

    printf("Nama: ");
    fgets(buffer, sizeof(buffer), stdin);
    clean_stdin(buffer);
    strncpy(new->nama_pelanggan, buffer, sizeof(new->nama_pelanggan) - 1);
    new->nama_pelanggan[sizeof(new->nama_pelanggan) - 1] = '\0'; // Pastikan null-terminated

    int valid = 0;
    while (!valid) {
        printf("Nomor telepon: ");
        fgets(buffer, sizeof(buffer), stdin);
        clean_stdin(buffer);
        if (validasi_no_telp(buffer)) {
            new->no_telp = atoi(buffer);
            valid = 1;
        } else {
            printf("Nomor telepon tidak valid. Silakan coba lagi.\n");
        }
    }

    printf("Alamat: ");
    fgets(buffer, sizeof(buffer), stdin);
    clean_stdin(buffer);
    strncpy(new->alamat, buffer, sizeof(new->alamat) - 1);
    new->alamat[sizeof(new->alamat) - 1] = '\0'; // Pastikan null-terminated

    // Tambahan untuk paket
    printf("\nPilih paket laundry:\n");
    printf("1. Reguler Wash (1 hari)\n");
    printf("2. Premium Wash (6 jam)\n");
    printf("3. Repairment (2 hari)\n");
    printf("4. Repaint (3 hari)\n");
    printf("Pilihan: ");
    
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
    new->id = id_pesanan_berikutnya++;
    new->waktu_pesan = time(NULL);
    new->waktu_selesai = new->waktu_pesan + durasi_paket[new->paket];
    new->sudah_selesai = false;
    new->nextnode = NULL;
    *hasil = new;
}

// Tambahkan deklarasi 4 antrian terpisah
antrian_laundry *antrian_reguler = NULL;
antrian_laundry *antrian_premium = NULL;
antrian_laundry *antrian_repairment = NULL;
antrian_laundry *antrian_repaint = NULL;

void enqueue(antrian_laundry **in) {
    antrian_laundry *newantrian = NULL;
    input_data(&newantrian);
    if (newantrian == NULL) {
        return;
    }

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
    printf("\n=== Antrian %s ===\n", kategori);
    if (isEmpty(antrian)) {
        printf("Antrian kosong!\n");
        return;
    }
    
    antrian_laundry * current = antrian;
    int count = 1;
    printf("\n=========================================================================");
    while (current != NULL) {
        printf("\n%d. %s - %d - %s", count, current->nama_pelanggan, current->no_telp, current->alamat);
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
void display_antrian(antrian_laundry ** awal, antrian_laundry * display) {
    tampilan_antrian();
    
    // Tampilkan semua antrian menggunakan fungsi helper
    tampilkan_antrian_kategori(antrian_reguler, "Reguler Wash");
    tampilkan_antrian_kategori(antrian_premium, "Premium Wash");
    tampilkan_antrian_kategori(antrian_repairment, "Repairment");
    tampilkan_antrian_kategori(antrian_repaint, "Repaint");
}

void cari_antrian(antrian_laundry ** awal, antrian_laundry * display) {
    if (isEmpty(display)) {
        printf("Antrian kosong!\n");
        return;
    }

    char nama[30];
    printf("\nMasukkan nama pelanggan yang ingin dicari: ");
    fgets(nama, sizeof(nama), stdin);
    clean_stdin(nama);

    antrian_laundry * current = display;
    int found = 0;

    while (current != NULL) {
        if (strcmp(current->nama_pelanggan, nama) == 0) {
            printf("\nPelanggan ditemukan: %s - %d - %s\n", current->nama_pelanggan, current->no_telp, current->alamat);
            found = 1;
            break;
        }
        current = current->nextnode;
    }

    if (!found) {
        printf("Pelanggan dengan nama '%s' tidak ditemukan dalam antrian.\n", nama);
    }
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

/*
void periksa_status_pesanan(antrian_laundry ** awal) {
    int id_pesanan;
    printf("\nMasukkan ID Pesanan yang ingin diperiksa: ");
    scanf("%d", &id_pesanan);
    getchar();
    
    // Cari di semua antrian
    antrian_laundry * current;
    bool ditemukan = false;
    
    // Cek antrian reguler
    current = antrian_reguler;
    while (current != NULL) {
        if (current->id == id_pesanan) {
            ditemukan = true;
            break;
        }
        current = current->nextnode;
    }
    
    // Cek antrian premium
    if (!ditemukan) {
        current = antrian_premium;
        while (current != NULL) {
            if (current->id == id_pesanan) {
                ditemukan = true;
                break;
            }
            current = current->nextnode;
        }
    }
    
    // Cek antrian repairment
    if (!ditemukan) {
        current = antrian_repairment;
        while (current != NULL) {
            if (current->id == id_pesanan) {
                ditemukan = true;
                break;
            }
            current = current->nextnode;
        }
    }
    
    // Cek antrian repaint
    if (!ditemukan) {
        current = antrian_repaint;
        while (current != NULL) {
            if (current->id == id_pesanan) {
                ditemukan = true;
                break;
            }
            current = current->nextnode;
        }
    }
    
    if (ditemukan) {
        printf("\n=== Status Pesanan #%d ===\n", current->id);
        printf("Pelanggan: %s\n", current->nama_pelanggan);
        printf("No. Telp: %d\n", current->no_telp);
        printf("Alamat: %s\n", current->alamat);
        printf("Paket: %s\n", nama_paket[current->paket]);
        printf("Waktu pemesanan: ");
        tampilkan_waktu(current->waktu_pesan);
        printf("\nEstimasi selesai: ");
        tampilkan_waktu(current->waktu_selesai);
        
        if (current->sudah_selesai) {
            printf("\nStatus: SELESAI\n");
            dequeue(&current);
        } else if (time(NULL) >= current->waktu_selesai) {
            printf("\nStatus: MENUNGGU PENGAMBILAN\n");
            printf("Pesanan sudah selesai dan menunggu diambil.\n");
        } else {
            time_t sisa_waktu = current->waktu_selesai - time(NULL);
            int jam = sisa_waktu / 3600;
            int menit = (sisa_waktu % 3600) / 60;
            
            printf("\nStatus: DALAM PROSES\n");
            printf("Estimasi waktu tersisa: %d jam %d menit\n", jam, menit);
        }
    } else {
        printf("Pesanan dengan ID #%d tidak ditemukan.\n", id_pesanan);
    }
}
*/

// Fungsi kosong sebagai placeholder
void periksa_status_pesanan(antrian_laundry ** awal) {
    // Fungsi akan diimplementasikan oleh teman
}