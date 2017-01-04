/* bitmap.h */

#ifndef _BITMAP_H_
#define _BITMAP_H_

/**
 * @class id_bmp
 * @brief id bitmap api
 */

unsigned long *id_bmp_crt(unsigned long size);
void id_bmp_set(unsigned long *bmp, unsigned long id);
void id_bmp_unset(unsigned long *bmp, unsigned long id);
unsigned long find_first_zero_bit(const unsigned long *bmp, unsigned long size);
unsigned long find_next_zero_bit(const unsigned long *bmp, unsigned long size,
                    unsigned long offset);

#endif /* _BITMAP_H_ */
