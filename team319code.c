#include <stdio.h>
#define MAX 100
int main() {
    FILE *file = fopen("data.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    double temp[MAX], hum[MAX], shelf[MAX];
    int n = 0;
    while (fscanf(file, "%lf %lf %lf", &temp[n], &hum[n], &shelf[n]) == 3) {
        n++;
    }
    fclose(file);
    double sumX1 = 0, sumX2 = 0, sumY = 0;
    double sumX1X1 = 0, sumX2X2 = 0, sumX1X2 = 0;
    double sumX1Y = 0, sumX2Y = 0;
	int i;
    for (i = 0; i < n; i++) {
        sumX1 += temp[i];
        sumX2 += hum[i];
        sumY  += shelf[i];

        sumX1X1 += temp[i] * temp[i];
        sumX2X2 += hum[i] * hum[i];
        sumX1X2 += temp[i] * hum[i];

        sumX1Y  += temp[i] * shelf[i];
        sumX2Y  += hum[i] * shelf[i];
    }
    double denominator = n * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2)
                         - sumX1 * (sumX1 * sumX2X2 - sumX2 * sumX1X2)
                         + sumX2 * (sumX1 * sumX1X2 - sumX2 * sumX1X1);
    double a_num = sumY * (sumX1X1 * sumX2X2 - sumX1X2 * sumX1X2)
                 - sumX1 * (sumX1Y * sumX2X2 - sumX2Y * sumX1X2)
                 + sumX2 * (sumX1Y * sumX1X2 - sumX2Y * sumX1X1);
    double b_num = n * (sumX1Y * sumX2X2 - sumX2Y * sumX1X2)
                 - sumY * (sumX1 * sumX2X2 - sumX2 * sumX1X2)
                 + sumX2 * (sumX1 * sumX2Y - sumX2 * sumX1Y);
    double c_num = n * (sumX1X1 * sumX2Y - sumX1X2 * sumX1Y)
                 - sumX1 * (sumX1 * sumX2Y - sumX2 * sumX1Y)
                 + sumY * (sumX1 * sumX1X2 - sumX2 * sumX1X1);
    double a = a_num / denominator;
    double b = b_num / denominator;
    double c = c_num / denominator;
    double t, h;
    printf("\nEnter Temperature and Humidity to predict shelf life: ");
    scanf("%lf %lf", &t, &h);
    double predicted = a + b * t + c * h;
    if (predicted < 0) {
        predicted = 0;
    }
    printf("Predicted Shelf Life: %.2f days\n", predicted);
    return 0;
}


