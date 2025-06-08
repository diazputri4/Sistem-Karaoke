#ifndef ANTRIAN_LAUNDRY_H
#define ANTRIAN_LAUNDRY_H

#include "Tampilan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    char nama_pelanggan[30];
    int no_telp;
    char alamat[50];
    struct node * nextnode;
} antrian_laundry;

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

    new->nextnode = NULL;
    *hasil = new;
}

void enqueue(antrian_laundry **in) {
    antrian_laundry *newantrian = NULL;
    input_data(&newantrian);
    if (newantrian == NULL) {
        return;
    }
    if (isEmpty(*in)) {
        *in = newantrian;
        return;
    }
    antrian_laundry *sementara = *in;
    while (sementara->nextnode != NULL) {
        sementara = sementara->nextnode;
    }
    sementara->nextnode = newantrian;
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

void display_antrian(antrian_laundry ** awal, antrian_laundry * display) {
    tampilan_antrian();
    if (isEmpty(display)) {
        printf("Antrian kosong!\n");
        return;
    }

    antrian_laundry * current = display;
    int count = 1;

    printf("\n=========================================================================");
    while (current != NULL) {
        printf("\n%d. %s - %d - %s", count, current->nama_pelanggan, current->no_telp, current->alamat);
        current = current->nextnode;
        count++;
        printf("\n=========================================================================");
    }
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

#endif
