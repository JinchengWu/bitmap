/*
 * bitmap.c
 * Original Author: hxyjxxx@163.com , 2016年11月25日-下午4:25:07
 *
 * bitmap bitmap.c
 *
 * History
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define BITS_PER_LONG        (sizeof(unsigned long) * 8)
#define BITOP_WORD(nr)      ((nr) / BITS_PER_LONG)

static unsigned long __ffs(unsigned long word)
{
    int num = 0;

    if (BITS_PER_LONG == 64) {
        if ((word & 0xffffffff) == 0) {
            num += 32;
            word >>= 32;
        }
    }
    if ((word & 0xffff) == 0) {
        num += 16;
        word >>= 16;
    }
    if ((word & 0xff) == 0) {
        num += 8;
        word >>= 8;
    }
    if ((word & 0xf) == 0) {
        num += 4;
        word >>= 4;
    }
    if ((word & 0x3) == 0) {
        num += 2;
        word >>= 2;
    }
    if ((word & 0x1) == 0) {
        num += 1;
    }

    return num;
}

#define ffz(x)  __ffs(~(x))

/**
 * find the bitmap next zero bit
 * @param [in] bmp : bitmap pointer
 * @param [in] size : bitmap size
 * @param [in] offset: find the zero bit offset
 * @return the unoccupy bit
 */
unsigned long find_next_zero_bit(const unsigned long *bmp, unsigned long size,
                    unsigned long offset)
{
    const unsigned long *p = bmp + BITOP_WORD(offset);
    unsigned long result = offset & ~(BITS_PER_LONG-1);
    unsigned long tmp;

    if (offset >= size)
        return size;
    size -= result;
    offset %= BITS_PER_LONG;
    if (offset) {
        tmp = *(p++);
        tmp |= ~0UL >> (BITS_PER_LONG - offset);
        if (size < BITS_PER_LONG) {
            goto found_first;
        }
        if (~tmp) {
            goto found_middle;
        }
        size -= BITS_PER_LONG;
        result += BITS_PER_LONG;
    }
    while (size & ~(BITS_PER_LONG-1)) {
        if (~(tmp = *(p++))) {
            goto found_middle;
        }
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size) {
        return result;
    }
    tmp = *p;

found_first:
    tmp |= ~0UL << size;
    if (tmp == ~0UL) {
        /* Are any bits zero? */
        return result + size;   /* Nope. */
    }
found_middle:

    return result + ffz(tmp);
}

/**
 * find the bitmap first zero bit
 * @param [in] bmp : bitmap pointer
 * @param [in] size : bitmap size
 * @return the unoccupy bit
 */
unsigned long find_first_zero_bit(const unsigned long *bmp, unsigned long size)
{
    const unsigned long *p = bmp;
    unsigned long result = 0;
    unsigned long tmp;

    while (size & ~(BITS_PER_LONG-1)) {
        if (~(tmp = *(p++))) {
            goto found;
        }
        result += BITS_PER_LONG;
        size -= BITS_PER_LONG;
    }
    if (!size) {
        return result;
    }

    tmp = (*p) | (~0UL << size);
    if (tmp == ~0UL) {    /* Are any bits zero? */
        return result + size;   /* Nope. */
    }
found:
    return result + ffz(tmp);
}

/**
 * occupy the id.
 * @param [in] bmp :the bitmap pointer which create by user
 * @param [in] id :occupy the id
 */
void id_bmp_set(unsigned long *bmp, unsigned long id)
{
    unsigned long index, bit;

    index = (id / BITS_PER_LONG);
    bit = (id % BITS_PER_LONG);
    bmp += index;

    *bmp |= (1UL << bit);
}

/**
 * release the id.
 * @param [in] bmp :the bitmap pointer which created by user
 * @param [in] id : release the id.
 */
void id_bmp_unset(unsigned long *bmp, unsigned long id)
{
    unsigned long index, bit;

    index = (id / BITS_PER_LONG);
    bit = (id % BITS_PER_LONG);
    bmp += index;

    *bmp &= (~(1UL << bit));
}

/**
 * index bitmap create
 * @param [in] size :bitmap range size
 * @return index bitmap pointer, the caller should free pointer.
 */
unsigned long *id_bmp_crt(unsigned long size)
{
    int len;
    unsigned long *bmp;

    if ((size % BITS_PER_LONG) != 0) {
        len = (int)((size / BITS_PER_LONG) + 1);
    } else {
        len = (int)(size / BITS_PER_LONG);
    }
    bmp = calloc(len, sizeof(unsigned long));
    assert(bmp != NULL && "calloc fail");

    return bmp;
}


