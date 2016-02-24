
#ifndef __CRC_H
#define __CRC_H

#ifdef __cplusplus
extern "C" {
#endif

extern unsigned int DTV_crc_init(void);
extern unsigned int DTV_crc_luma_update(unsigned int crc, unsigned char* Buffer, unsigned int Length);
extern unsigned int DTV_crc_chroma_update(unsigned int crc, unsigned char* BufferCb, unsigned char* BufferCr, unsigned int Length);

#ifdef __cplusplus
}
#endif

#endif /* #ifndef __CRC_H */

