#include <stdio.h>

#define N 6  // Jumlahdata

// Fungsi untuk menghitung laju perubahan temperatur (dT/dt) menggunakan metode beda hingga
void hitungLajuPendinginan(double T[], double dt, double dTdt[]) {
    for (int i = 0; i < N; i++) {
        if (i == 0) {
            // Titik awal (beda maju)
            dTdt[i] = (T[i + 1] - T[i]) / dt;
        } else if (i == N - 1) {
            // Titik akhir (beda mundur)
            dTdt[i] = (T[i] - T[i - 1]) / dt;
        } else {
            // Titik tengah (beda tengah)
            dTdt[i] = (T[i + 1] - T[i - 1]) / (2 * dt);
        }
    }
}

// Fungsi untuk menghitung regresi linier untuk menemukan konstanta pendinginan k
void regresiLinier(double x[], double y[], double sum_x, double sum_y, double sum_xy, double sum_x2, double *m, double *c) {
    *m = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x);
    *c = (sum_y - (*m) * sum_x) / N;
}

int main() {
    double T[N] = {80.0, 44.5, 30.0, 24.1, 21.7, 20.7}; // Data temperatur
    double T_a = 20.0;  // Temperatur lingkungan (dalam °C)
    double dTdt[N];  // Array untuk menyimpan hasil laju pendinginan
    double dt = 5.0;  // Interval waktu (5 menit)

    hitungLajuPendinginan(T, dt, dTdt);

    // Membuka file untuk menyimpan hasil CSV
    FILE *file = fopen("output.csv", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    // Menulis header ke file CSV
    fprintf(file, "Waktu (menit),Temperatur (°C),dT/dt (°C/menit),T - T_a (°C)\n");
    // Menulis data ke file CSV
    for (int i = 0; i < N; i++) {
        fprintf(file, "%d,%.2f,%.2f,%.2f\n", i * 5, T[i], dTdt[i], T[i] - T_a);
    }

    // Perhitungan regresi linier
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;
    for (int i = 0; i < N; i++) {
        double x = T[i] - T_a;
        double y = dTdt[i];
        sum_x += x;
        sum_y += y;
        sum_xy += x * y;
        sum_x2 += x * x;
    }

    // Variabel untuk slope (m) dan intercept (c)
    double m, c;
    regresiLinier(T, dTdt, sum_x, sum_y, sum_xy, sum_x2, &m, &c);

    // Menulis hasil regresi linier ke file CSV
    fprintf(file, "\nHasil Regresi Linier:\n");
    fprintf(file, "Slope (m),%.3f\n", m);
    fprintf(file, "Intercept (c),%.3f\n", c);
    fprintf(file, "Konstanta pendinginan k,%.3f per menit\n", -m);
    // Menutup file
    fclose(file);

    printf("Data telah disimpan ke output.csv\n");

    return 0;
}
