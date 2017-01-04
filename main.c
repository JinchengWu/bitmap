/*
 * main.c
 * Original Author: hxyjxxx@163.com , 2016年11月25日-下午5:07:38
 *
 * bitmap main.c
 *
 * History
 */

#include <bitmap.h>
#include <stdio.h>

int main(int argc, const char * argv[])
{
    unsigned long *bmp, *p;
    unsigned long id;
    unsigned long i;


    bmp = id_bmp_crt(8096);
    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id_bmp_unset(bmp, 0);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id_bmp_unset(bmp, 5);

    id_bmp_unset(bmp, 6);

    id_bmp_unset(bmp, 2);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    id = find_first_zero_bit(bmp, 8096);
    printf("first zero bit: %lu\r\n", id);
    id_bmp_set(bmp, id);

    for (i = 0; i < 8000; i++) {
        id = find_first_zero_bit(bmp, 8096);
        printf("first zero bit: %lu\r\n", id);
        id_bmp_set(bmp, id);
    }

    id_bmp_unset(bmp, 100);
    id_bmp_set(bmp, 200);


    p = bmp;
    for (i = 0; i < (8096 / 32); i++) {
        printf("%016lx\r\n", *p);
        p++;
    }

    return 0;
}
