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
    printf("||Tipe Layanan: %s\n", nama_paket[print.datastruk->paket]);
    
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
    switch (print.metode - 1) {
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

void order(antrian_laundry * neworder) {
    pesanan out;
    printf("\nPilih metode pembayaran:\n");
    printf("1. Tunai\n");
    printf("2. Transfer Bank\n");
    printf("3. E-Wallet\n");
    printf("Pilihan: ");
    scanf("%d", &out.metode);
    getchar();

    // Set harga berdasarkan paket
    switch (neworder->paket) {
        case REGULER:
            out.harga = 15000;
            break;
        case PREMIUM:
            out.harga = 25000;
            break;
        case REPAIRMENT:
            out.harga = 35000;
            break;
        case REPAINT:
            out.harga = 45000;
            break;
    }

    // Simpan data pesanan
    out.datastruk = neworder;
    latest_order = out;
}