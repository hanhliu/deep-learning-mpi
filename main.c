#include <stdio.h>
#include <stdlib.h>

void read_mnist_images(const char *filename, float **images, int *num_images, int *rows, int *cols) {
    FILE *file = fopen(filename, "rb");  // file name here
    if (!file) {
        perror("Cannot open file");
        exit(1);
    }

    int magic_number, n_images, n_rows, n_cols;
    fread(&magic_number, sizeof(int), 1, file);
    fread(&n_images, sizeof(int), 1, file);
    fread(&n_rows, sizeof(int), 1, file);
    fread(&n_cols, sizeof(int), 1, file);

    *num_images = __builtin_bswap32(n_images);
    *rows = __builtin_bswap32(n_rows);
    *cols = __builtin_bswap32(n_cols);

    *images = (float *)malloc((*num_images) * (*rows) * (*cols) * sizeof(float));
    unsigned char pixel;
    for (int i = 0; i < (*num_images) * (*rows) * (*cols); i++) {
        fread(&pixel, sizeof(unsigned char), 1, file);
        (*images)[i] = pixel / 255.0f;
    }
    fclose(file);
}
