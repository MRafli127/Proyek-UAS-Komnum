#include <stdio.h>

#define N 6  // jumlah data

int main() {
    // Data waktu (menit)
    double t[N] = {0, 5, 10, 15, 20, 25};
    // Data suhu T (°C)
    double T[N] = {80.0, 44.5, 30.0, 24.1, 21.7, 20.7};
    // Suhu lingkungan
    double Ta = 20.0;
    // Interval waktu (menit)
    double dt = 5.0;

    double dTdt[N];    // array turunan suhu
    double x[N];       // T - Ta
    double y[N];       // dT/dt

    // Hitung dT/dt menggunakan beda hingga
    
    // Titik awal (beda maju)
    dTdt[0] = (T[1] - T[0]) / dt;
    // Titik tengah (beda tengah)
    for (int i = 1; i < N - 1; i++) {
        dTdt[i] = (T[i + 1] - T[i - 1]) / (2 * dt);
    }
    // Titik akhir (beda mundur)
    dTdt[N - 1] = (T[N - 1] - T[N - 2]) / dt;
    
    // Hitung x = T - Ta dan y = dT/dt
    for (int i = 0; i < N; i++) {
        x[i] = T[i] - Ta;
        y[i] = dTdt[i];
    }

    // Hitung regresi linier y = m*x + c
    double sum_x = 0, sum_y = 0, sum_xy = 0, sum_x2 = 0;

    for (int i = 0; i < N; i++) {
        sum_x += x[i];
        sum_y += y[i];
        sum_xy += x[i] * y[i];
        sum_x2 += x[i] * x[i];
    }

    double m = (N * sum_xy - sum_x * sum_y) / (N * sum_x2 - sum_x * sum_x);
    double c = (sum_y - m * sum_x) / N;

    double k = -m;  // k adalah -m dari regresi

    // Cetak hasil
    printf("Waktu (menit)\tT (°C)\t\t dT/dt (°C/menit)\t T - Ta (°C)\n");
    for (int i = 0; i < N; i++) {
        printf("%10.1f\t%7.2f\t%17.4f\t%11.2f\n", t[i], T[i], dTdt[i], x[i]);
    }

    printf("\nHasil regresi linier: y = m*x + c\n");
    printf("m = %.4f, c = %.4f\n", m, c);
    printf("Konstanta pendinginan k = %.4f per menit\n", k);

    return 0;
}
