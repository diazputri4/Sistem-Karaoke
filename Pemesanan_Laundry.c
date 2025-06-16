#include "Pemesanan_Laundry.h"

pesanan latest_order;

void tampilkan_struk_pembayaran(pesanan print) {
    printf("\n");
    printf("==========================================\n");
    printf("||           STRUK PEMBAYARAN           ||\n");
    printf("==========================================\n");
    printf("||ID Pesanan: %s\n", print.datastruk->id);
    printf("||Nama: %s\n", print.datastruk->nama_pelanggan);
    printf("||No. Telepon: %s\n", print.datastruk->no_telp);
    printf("||Alamat: %s\n", print.datastruk->alamat);
    
    // Tampilkan layanan yang dipilih
    printf("||Layanan: %s\n", print.nama_layanan);
    
    // Format waktu lebih rapi
    struct tm* tm_pesan = localtime(&print.datastruk->waktu_pesan);
    printf("||Waktu Pesanan: %02d/%02d/%04d %02d:%02d:%02d\n", 
           tm_pesan->tm_mday, tm_pesan->tm_mon + 1, tm_pesan->tm_year + 1900,
           tm_pesan->tm_hour, tm_pesan->tm_min, tm_pesan->tm_sec);
    
    struct tm* tm_selesai = localtime(&print.datastruk->waktu_selesai);
    printf("||Estimasi Selesai: %02d/%02d/%04d %02d:%02d:%02d\n", 
           tm_selesai->tm_mday, tm_selesai->tm_mon + 1, tm_selesai->tm_year + 1900,
           tm_selesai->tm_hour, tm_selesai->tm_min, tm_selesai->tm_sec);
    
    // Tampilkan metode pembayaran
    printf("||Metode Pembayaran: ");
    switch (print.metode) {
        case TUNAI:
            printf("Tunai\n");
            break;
        case TRANSFER:
            printf("Transfer Bank\n");
            break;
        case EWALLET:
            printf("E-Wallet\n");
            break;
    }
    
    printf("||Total Pembayaran: Rp %d\n", print.harga);
    
    printf("==========================================\n");
    printf("||           TERIMA KASIH               ||\n");
    printf("||      Simpan struk pembayaran Anda    ||\n");
    printf("==========================================\n");
}

// Menu layanan sudah ada di Antrian_Laundry.c, tidak perlu duplikasi

// Fungsi untuk menampilkan katalog dan memproses pilihan Regular Wash
int proses_regular_wash(char* nama_layanan, int* harga, int* estimasi) {
    printf("\n>> REGULAR WASH\n");
    printf("1. Deep Clean         - Rp 40.000 \n");
    printf("2. Deep Clean Hard    - Rp 50.000 \n"); 
    printf("3. Kids Shoes         - Rp 25.000 \n");
    printf("4. Boots              - Rp 60.000 \n");
    printf("5. Boots Hard         - Rp 70.000 \n");
    printf("Pilih layanan (1-5): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    getchar();
    
    if (pilihan < 1 || pilihan > 5) {
        printf("? Pilihan tidak valid!\n");
        return 0;
    }
    
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
    return 1;
}

// Fungsi untuk menampilkan katalog dan memproses pilihan Premium Wash
int proses_premium_wash(char* nama_layanan, int* harga, int* estimasi) {
    printf("\n>> PREMIUM WASH\n");
    printf("1. Premium Clean      - Rp 55.000 \n");
    printf("2. Premium Clean Hard - Rp 65.000 \n");
    printf("3. One Day Service    - Rp 70.000 \n");
    printf("4. One Day Service Hard - Rp 80.000\n");
    printf("5. Premium Clean Boots - Rp 80.000 \n");
    printf("Pilih layanan (1-5): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    getchar();
    
    if (pilihan < 1 || pilihan > 5) {
        printf("? Pilihan tidak valid!\n");
        return 0;
    }
    
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
    return 1;
}

// Fungsi untuk menampilkan katalog dan memproses pilihan Repairment
int proses_repairment(char* nama_layanan, int* harga, int* estimasi) {
    printf("\n>> REPAIRMENT (Include Wash)\n");
    printf("1. Restitch           - Rp 85.000 \n");
    printf("2. Reglue             - Rp 80.000 \n");
    printf("3. Unyellowing        - Rp 80.000 \n");
    printf("Pilih layanan (1-3): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    getchar();
    
    if (pilihan < 1 || pilihan > 3) {
        printf("? Pilihan tidak valid!\n");
        return 0;
    }
    
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
    return 1;
}

// Fungsi untuk menampilkan katalog dan memproses pilihan Repaint
int proses_repaint(char* nama_layanan, int* harga, int* estimasi) {
    printf("\n>> REPAINT (Include Wash)\n");
    printf("1. Repaint Upper      - Rp 150.000 \n");
    printf("2. Repaint Midsole    - Rp 125.000 \n");
    printf("Pilih layanan (1-2): ");
    
    int pilihan;
    scanf("%d", &pilihan);
    getchar();
    
    if (pilihan < 1 || pilihan > 2) {
        printf("? Pilihan tidak valid!\n");
        return 0;
    }
    
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
    return 1;
}

void order(antrian_laundry * neworder) {
    pesanan out;
    
    // Menu layanan sudah ditampilkan di input_data() dari Antrian_Laundry.c
    // Langsung menggunakan paket yang sudah dipilih
    int kategori_layanan = neworder->paket + 1; // Konversi dari enum (0-3) ke menu (1-4)
    
    // Proses berdasarkan kategori yang dipilih
    char nama_layanan[100];
    int harga, estimasi;
    int berhasil = 0;
    
    switch (kategori_layanan) {
        case 1:
            berhasil = proses_regular_wash(nama_layanan, &harga, &estimasi);
            break;
        case 2:
            berhasil = proses_premium_wash(nama_layanan, &harga, &estimasi);
            break;
        case 3:
            berhasil = proses_repairment(nama_layanan, &harga, &estimasi);
            break;
        case 4:
            berhasil = proses_repaint(nama_layanan, &harga, &estimasi);
            break;
    }
    
    if (!berhasil) {
        return; // Keluar jika pilihan tidak valid
    }
    
    // Harga langsung tanpa perhitungan jumlah dan diskon
    out.harga = harga;
    
    // Simpan info layanan
    strcpy(out.nama_layanan, nama_layanan);
    
    // Hitung waktu selesai
    time_t waktu_sekarang = time(NULL);
    neworder->waktu_selesai = waktu_sekarang + (estimasi * 24 * 60 * 60); // estimasi dalam detik
    
    printf("\n=== RINGKASAN PESANAN ===\n");
    printf("Layanan: %s\n", nama_layanan);
    printf("Harga: Rp %d\n", harga);
    printf("Estimasi selesai: %d hari\n", estimasi);
    
    printf("\nPilih metode pembayaran:\n");
    printf("1. Tunai\n");
    printf("2. Transfer Bank\n");
    printf("3. E-Wallet\n");
    printf("Pilihan: ");
    scanf("%d", &out.metode);
    getchar();
    
    if (out.metode < 1 || out.metode > 3) {
        printf("? Metode pembayaran tidak valid!\n");
        return;
    }
    
    // Konversi ke enum (karena user input 1-3, tapi enum dimulai dari 0)
    out.metode = out.metode - 1;

    // Simpan data pesanan
    out.datastruk = neworder;
    latest_order = out;
    
    printf("\n? Pesanan berhasil dibuat!\n");
}
