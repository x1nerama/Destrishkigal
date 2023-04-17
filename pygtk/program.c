#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <sayi>\n", argv[0]);
        return 1;
    }

    int sayi = atoi(argv[1]);
    int toplam = sayi + 10;

    printf("%d\n", toplam);

    return 0;
}
