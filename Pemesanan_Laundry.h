#ifndef PEMESANAN_LAUNDRY_H
#define PEMESANAN_LAUNDRY_H

#include "Antrian_Laundry.h"
#include "Helper.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

typedef enum {
    TUNAI,
    TRANSFER,
    EWALLET
} metode_pembayaran;

typedef struct {
    antrian_laundry* datastruk;
    metode_pembayaran metode;
    int harga;
} pesanan;

extern pesanan latest_order;

void tampilkan_struk_pembayaran(pesanan print);
void order(antrian_laundry * neworder);

#endif 