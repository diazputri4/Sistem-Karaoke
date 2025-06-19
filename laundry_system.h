#ifndef LAUNDRY_SYSTEM_H
#define LAUNDRY_SYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include "Antrian_Laundry.h"
#include "tampilan_struk.h"

// Deklarasi fungsi-fungsi sistem
void clear_screen();
void buat_pesanan(antrian_laundry** q);
void list_antrian(antrian_laundry* q);
void detail_status_pesanan(antrian_laundry* q);
void riwayat_pesanan_hari_ini();

#endif 
