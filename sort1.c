
#include <stdio.h>
#include <stdlib.h>

#define MAX_INTS 1000

void bubbleSort(int arr[], int n) {
    int i, j, temp;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <file_name>\n", argv[0]);
        return 1;
    }

    const char *fileName = argv[1];

    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", fileName);
        return 1;
    }

    int integers[MAX_INTS];
    int count = 0;
    int num;

    while (fscanf(file, "%d", &num) == 1 && count < MAX_INTS) {
        integers[count++] = num;
    }

    fclose(file);

    if (count == 0) {
        printf("No integers found in the file.\n");
        return 0;
    }

    bubbleSort(integers, count);

    printf("Sorted integers:\n");
    for (int i = 0; i < count; i++) {
        printf("%d ", integers[i]);
    }
    printf("\n");

    return 0;
}
