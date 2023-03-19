#include <stdio.h>

void lyd(int lyd[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            scanf("%d", &lyd[i][j]);
        }
    }
    printf("\n");
}

void kali(int lyd1[3][3], int lyd2[3][3], int hasil[3][3]) {
    int i, j, k; 
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            hasil[i][j] = 0;
            for (k = 0; k < 3; k++) {
                hasil[i][j] += lyd1[i][k] * lyd2[k][j];
            }
        }
    }
}

void tambah(int lyd1[3][3], int lyd2[3][3], int hasil[3][3]) {
    int i, j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            hasil[i][j] = lyd1[i][j] + lyd2[i][j];
        }
    }
}

void transpose(int lyd[3][3],int hasil[3][3]) {
    int i,j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            hasil[i][j] = lyd[j][i];
        }
    }
}

void perinter(int hasil[3][3]) {
    int i,j;
    for (i = 0; i < 3; i++) {
        for (j = 0; j < 3; j++) {
            printf("%d ", hasil[i][j]);
        }
    printf("\n");
    }
}

int main() {
    int lyd1[3][3], lyd2[3][3], hasil[3][3], pilihan, i, j;

    printf("Masukkan Matrix Pertama(3 x 3)\n");
    lyd(lyd1);
    printf("Masukkan Matrix Kedua(3 x 3)\n");
    lyd(lyd2);

    do{
        printf("1. Perkalian Dua Buah Matrix\n");
        printf("2. Penjumlahan Dua Buah Matrix\n");
        printf("3. Transpose Dua Buah Matrix\n");
        printf("4. Keluar\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                kali(lyd1, lyd2, hasil);
                perinter(hasil);
                break;
            case 2:
                tambah(lyd1, lyd2, hasil);
                perinter(hasil);
                break;
            case 3:
                transpose(lyd1, hasil);
                printf("Transpose Matrix Pertama: \n");
                perinter(hasil);
                transpose(lyd2, hasil);
                printf("Transpose Matrix Kedua: \n");
                perinter(hasil);
                break;
        }
    }while(pilihan !=4);
    return 0;
}