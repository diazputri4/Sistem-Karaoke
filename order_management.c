#include "laundry_system.h"

/*
Nama: tampilkan_katalog_wash_regular
Parameter yang dibutuhkan: Tidak ada
Proses yang dilakukan: Membaca dan menampilkan katalog layanan Regular Wash dari file
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan menu Regular Wash dengan harga dan estimasi
*/
void tampilkan_katalog_wash_regular() {
    printf("\n?? REGULAR WASH\n");
    printf("1. Deep Clean         - Rp 40.000 (3 hari)\n");
    printf("2. Deep Clean Hard    - Rp 50.000 (4 hari)\n"); 
    printf("3. Kids Shoes         - Rp 25.000 (3 hari)\n");
    printf("4. Boots              - Rp 60.000 (3 hari)\n");
    printf("5. Boots Hard         - Rp 70.000 (4 hari)\n");
}

/*
Nama: tampilkan_katalog_wash_premium
Parameter yang dibutuhkan: Tidak ada
Proses yang dilakukan: Membaca dan menampilkan katalog layanan Premium Wash dari file
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan menu Premium Wash dengan harga dan estimasi
*/
void tampilkan_katalog_wash_premium() {
    printf("\n?? PREMIUM WASH\n");
    printf("1. Premium Clean      - Rp 55.000 (1 hari)\n");
    printf("2. Premium Clean Hard - Rp 65.000 (1 hari)\n");
    printf("3. One Day Service    - Rp 70.000 (1 hari)\n");
    printf("4. One Day Service Hard - Rp 80.000 (1 hari)\n");
    printf("5. Premium Clean Boots - Rp 80.000 (4 hari)\n");
}

/*
Nama: tampilkan_katalog_repair
Parameter yang dibutuhkan: Tidak ada
Proses yang dilakukan: Membaca dan menampilkan katalog layanan Repairment dari file
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan menu Repairment dengan harga dan estimasi
*/
void tampilkan_katalog_repair() {
    printf("\n?? REPAIRMENT (Include Wash)\n");
    printf("1. Restitch           - Rp 85.000 (5 hari)\n");
    printf("2. Reglue             - Rp 80.000 (5 hari)\n");
    printf("3. Unyellowing        - Rp 80.000 (5 hari)\n");
}

/*
Nama: tampilkan_katalog_repaint
Parameter yang dibutuhkan: Tidak ada
Proses yang dilakukan: Membaca dan menampilkan katalog layanan Repaint dari file
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Tampilan menu Repaint dengan harga dan estimasi
*/
void tampilkan_katalog_repaint() {
    printf("\n?? REPAINT (Include Wash)\n");
    printf("1. Repaint Upper      - Rp 150.000 (7 hari)\n");
    printf("2. Repaint Midsole    - Rp 125.000 (7 hari)\n");
}

/*
Nama: get_layanan_info
Parameter yang dibutuhkan: int tipe_layanan, int sub_tipe, int pilihan, char* nama_layanan, int* harga, int* estimasi
Proses yang dilakukan: Mengambil informasi detail layanan berdasarkan tipe dan pilihan
Input yang diperlukan: Tidak ada input dari user
Output yang dihasilkan: Nama layanan, harga, dan estimasi waktu melalui parameter pointer
*/
void get_layanan_info(int tipe_layanan, int sub_tipe, int pilihan, char* nama_layanan, int* harga, int* estimasi) {
    if (tipe_layanan == 1) { // Wash Only
        if (sub_tipe == 1) { // Regular Wash
            switch (pilihan) {
                case 1:
                    strcpy(nama_layanan, "Deep Clean");
                    *harga = 40000;
                    *estimasi = 3;
                    break;
                case 2:
                    strcpy(nama_layanan, "Deep Clean Hard");
                    *harga = 50000;
                    *estimasi = 4;
                    break;
                case 3:
                    strcpy(nama_layanan, "Kids Shoes");
                    *harga = 25000;
                    *estimasi = 3;
                    break;
                case 4:
                    strcpy(nama_layanan, "Boots");
                    *harga = 60000;
                    *estimasi = 3;
                    break;
                case 5:
                    strcpy(nama_layanan, "Boots Hard");
                    *harga = 70000;
                    *estimasi = 4;
                    break;
            }
        } else { // Premium Wash
            switch (pilihan) {
                case 1:
                    strcpy(nama_layanan, "Premium Clean");
                    *harga = 55000;
                    *estimasi = 1;
                    break;
                case 2:
                    strcpy(nama_layanan, "Premium Clean Hard");
                    *harga = 65000;
                    *estimasi = 1;
                    break;
                case 3:
                    strcpy(nama_layanan, "One Day Service");
                    *harga = 70000;
                    *estimasi = 1;
                    break;
                case 4:
                    strcpy(nama_layanan, "One Day Service Hard");
                    *harga = 80000;
                    *estimasi = 1;
                    break;
                case 5:
                    strcpy(nama_layanan, "Premium Clean Boots");
                    *harga = 80000;
                    *estimasi = 4;
                    break;
            }
        }
    } else if (tipe_layanan == 2) { // Repairment
        switch (pilihan) {
            case 1:
                strcpy(nama_layanan, "Restitch");
                *harga = 85000;
                *estimasi = 5;
                break;
            case 2:
                strcpy(nama_layanan, "Reglue");
                *harga = 80000;
                *estimasi = 5;
                break;
            case 3:
                strcpy(nama_layanan, "Unyellowing");
                *harga = 80000;
                *estimasi = 5;
                break;
        }
    } else if (tipe_layanan == 3) { // Repaint
        switch (pilihan) {
            case 1:
                strcpy(nama_layanan, "Repaint Upper");
                *harga = 150000;
                *estimasi = 7;
                break;
            case 2:
                strcpy(nama_layanan, "Repaint Midsole");
                *harga = 125000;
                *estimasi = 7;
                break;
        }
    }
}

/*
Nama: buat_pesanan
Parameter yang dibutuhkan: Queue* q_wash, Queue* q_repair, Queue* q_repaint (pointer ke queue masing-masing tipe layanan)
Proses yang dilakukan: Membuat pesanan baru dengan alur lengkap dari input identitas hingga konfirmasi
Input yang diperlukan: Nama pelanggan, nomor HP, pilihan layanan, jumlah sepatu
Output yang dihasilkan: Pesanan baru yang disimpan ke queue dan riwayat
*/
void buat_pesanan(Queue* q_wash, Queue* q_repair, Queue* q_repaint) {
    system("cls");
    Pesanan pesanan = {0};
    
    printf("=== BUAT PESANAN BARU ===\n\n");
    
    // 1. Input Identitas Pelanggan
    printf("?? INPUT IDENTITAS PELANGGAN\n");
    printf("Nama Pelanggan: ");
    fgets(pesanan.nama_pelanggan, sizeof(pesanan.nama_pelanggan), stdin);
    pesanan.nama_pelanggan[strcspn(pesanan.nama_pelanggan, "\n")] = 0; // Hapus newline
    
    // Validasi nomor HP
    int hp_valid = 0;
    while (!hp_valid) {
        printf("Nomor HP (08xxxxxxxxx): ");
        fgets(pesanan.no_hp, sizeof(pesanan.no_hp), stdin);
        pesanan.no_hp[strcspn(pesanan.no_hp, "\n")] = 0;
        
        if (validasi_nomor_hp(pesanan.no_hp)) {
            hp_valid = 1;
        } else {
            printf("? Nomor HP tidak valid! Harus diawali 08 dan berjumlah 11-13 digit.\n");
        }
    }
    
    // Generate ID pesanan dan tanggal
    generate_id_pesanan(pesanan.id_pesanan);
    get_tanggal_hari_ini(pesanan.tanggal_terima);
    
    int total_item = 0;
    int estimasi_terlama = 0;
    char lanjut = 'y';
    
    // Loop untuk menambah layanan
    while (lanjut == 'y' || lanjut == 'Y') {
        system("cls");
        printf("=== PILIH LAYANAN ===\n\n");
        
        // 2. Pilih Tipe Layanan
        printf("?? TIPE LAYANAN:\n");
        printf("1. Wash Only\n");
        printf("2. Repairment (Include Wash)\n");
        printf("3. Repaint (Include Wash)\n");
        printf("Pilih tipe layanan (1-3): ");
        
        int tipe_layanan;
        scanf("%d", &tipe_layanan);
        getchar();
        
        if (tipe_layanan < 1 || tipe_layanan > 3) {
            printf("? Pilihan tidak valid!\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
            continue;
        }
        
        int sub_tipe = 0;
        if (tipe_layanan == 1) { // Wash Only
            printf("\n?? SUB KATEGORI WASH:\n");
            printf("1. Regular Wash\n");
            printf("2. Premium Wash\n");
            printf("Pilih sub kategori (1-2): ");
            scanf("%d", &sub_tipe);
            getchar();
            
            if (sub_tipe < 1 || sub_tipe > 2) {
                printf("? Pilihan tidak valid!\n");
                printf("Tekan Enter untuk melanjutkan...");
                getchar();
                continue;
            }
        }
        
        // 3. Tampilkan katalog dan pilih layanan spesifik
        system("cls");
        if (tipe_layanan == 1) {
            if (sub_tipe == 1) {
                tampilkan_katalog_wash_regular();
            } else {
                tampilkan_katalog_wash_premium();
            }
            printf("Pilih layanan (1-5): ");
        } else if (tipe_layanan == 2) {
            tampilkan_katalog_repair();
            printf("Pilih layanan (1-3): ");
        } else {
            tampilkan_katalog_repaint();
            printf("Pilih layanan (1-2): ");
        }
        
        int pilihan_layanan;
        scanf("%d", &pilihan_layanan);
        getchar();
        
        // Validasi pilihan
        int max_pilihan = (tipe_layanan == 1) ? 5 : (tipe_layanan == 2) ? 3 : 2;
        if (pilihan_layanan < 1 || pilihan_layanan > max_pilihan) {
            printf("? Pilihan tidak valid!\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
            continue;
        }
        
        // Input jumlah sepatu
        printf("Jumlah sepatu: ");
        int jumlah;
        scanf("%d", &jumlah);
        getchar();
        
        if (jumlah <= 0) {
            printf("? Jumlah sepatu harus lebih dari 0!\n");
            printf("Tekan Enter untuk melanjutkan...");
            getchar();
            continue;
        }
        
        // Ambil info layanan
        char nama_layanan[100];
        int harga, estimasi;
        get_layanan_info(tipe_layanan, sub_tipe, pilihan_layanan, nama_layanan, &harga, &estimasi);
        
        // Simpan layanan ke pesanan
        strcpy(pesanan.layanan[pesanan.total_layanan].nama_layanan, nama_layanan);
        pesanan.layanan[pesanan.total_layanan].jumlah = jumlah;
        pesanan.layanan[pesanan.total_layanan].harga_satuan = harga;
        pesanan.layanan[pesanan.total_layanan].estimasi_hari = estimasi;
        pesanan.total_layanan++;
        
        total_item += jumlah;
        if (estimasi > estimasi_terlama) {
            estimasi_terlama = estimasi;
        }
        
        // 4. Tanya apakah ingin menambah layanan
        printf("\n? Layanan berhasil ditambahkan!\n");
        printf("Tambah layanan lain? (y/n): ");
        scanf("%c", &lanjut);
        getchar();
    }
    
    // 5. Hitung total dan diskon
    pesanan.subtotal = 0;
    int i = 0;
    while (i < pesanan.total_layanan) {
        pesanan.subtotal += pesanan.layanan[i].harga_satuan * pesanan.layanan[i].jumlah;
        i++;
    }
    
    // Diskon 15% jika total item >= 3
    if (total_item >= 3) {
        pesanan.diskon = (int)(pesanan.subtotal * 0.15);
    } else {
        pesanan.diskon = 0;
    }
    
    pesanan.total_bayar = pesanan.subtotal - pesanan.diskon;
    pesanan.estimasi_selesai = estimasi_terlama;
    
    // 6. Hitung tanggal selesai
    hitung_tanggal_selesai(pesanan.tanggal_selesai, estimasi_terlama);
    
    // 7. Tampilkan ringkasan pesanan
    system("cls");
    printf("=== RINGKASAN PESANAN ===\n\n");
    printf("ID Pesanan: %s\n", pesanan.id_pesanan);
    printf("Nama: %s\n", pesanan.nama_pelanggan);
    printf("HP: %s\n", pesanan.no_hp);
    printf("Tanggal Terima: %s\n", pesanan.tanggal_terima);
    printf("\nLayanan yang dipilih:\n");
    
    i = 0;
    while (i < pesanan.total_layanan) {
        printf("- %s x%d = Rp %d\n", 
               pesanan.layanan[i].nama_layanan,
               pesanan.layanan[i].jumlah,
               pesanan.layanan[i].harga_satuan * pesanan.layanan[i].jumlah);
        i++;
    }
    
    printf("\nSubtotal: Rp %d\n", pesanan.subtotal);
    if (pesanan.diskon > 0) {
        printf("Diskon (15%%): Rp %d\n", pesanan.diskon);
    }
    printf("Total Bayar: Rp %d\n", pesanan.total_bayar);
    printf("Estimasi Selesai: %s (%d hari)\n", pesanan.tanggal_selesai, estimasi_terlama);
    
    // 8. Konfirmasi pesanan
    char konfirmasi;
    printf("\nKonfirmasi pesanan? (y/n): ");
    scanf("%c", &konfirmasi);
    getchar();
    
    if (konfirmasi == 'y' || konfirmasi == 'Y') {
        // Tentukan queue yang tepat berdasarkan layanan
        Queue* target_queue = q_wash; // Default ke wash
        
        // Cek tipe layanan untuk menentukan queue
        i = 0;
        while (i < pesanan.total_layanan) {
            if (strstr(pesanan.layanan[i].nama_layanan, "Restitch") ||
                strstr(pesanan.layanan[i].nama_layanan, "Reglue") ||
                strstr(pesanan.layanan[i].nama_layanan, "Unyellowing")) {
                target_queue = q_repair;
                break;
            } else if (strstr(pesanan.layanan[i].nama_layanan, "Repaint")) {
                target_queue = q_repaint;
                break;
            }
            i++;
        }
        
        enqueue(target_queue, pesanan);
        cetak_struk(pesanan);
        simpan_riwayat(pesanan);
        
        printf("\n? Pesanan berhasil dibuat dan disimpan!\n");
    } else {
        printf("\n? Pesanan dibatalkan.\n");
    }
    
    printf("Tekan Enter untuk kembali ke menu utama...");
    getchar();
}
