#include "Antrian_Laundry.h"
#include "History.h"
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
    // Menggunakan ID terakhir dari history + 1
    new->id = get_last_id() + 1;
    new->waktu_pesan = time(NULL);
    new->waktu_selesai = new->waktu_pesan + durasi_paket[new->paket];
    new->sudah_selesai = false;
    new->nextnode = NULL;
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
    printf("\n=== Antrian %s ===\n", kategori);
    if (isEmpty(antrian)) {
        printf("Antrian kosong!\n");
        return;
    }
    
    antrian_laundry * current = antrian;
    int count = 1;
    printf("\n=========================================================================");
    while (current != NULL) {
        printf("\n%d. %s - %s - %s", count, current->nama_pelanggan, current->no_telp, current->alamat);
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
            printf("\nPelanggan ditemukan: %s - %s - %s\n", 
                   current->nama_pelanggan, current->no_telp, current->alamat);
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