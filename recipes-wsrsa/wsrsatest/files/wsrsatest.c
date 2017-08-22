/**
 * @file   testwssha256kern.c
 * @author Brett Nicholas
 * @date   7 April 2015
 * @version 0.1
 * @brief  A Linux user space program that communicates with the wssha256kern.c LKM. It passes a
 * string to the LKM and reads the response from the LKM. For this example to work the device
 * must be called /dev/wssha256char.
 * @see http://www.derekmolloy.ie/ for a full description and follow-up descriptions.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>

#include "wsrsakern.h" // IOCTL MACROS AND MODE TYPE

#define TESTNUM 0

#ifndef RSA_SIZE_BYTES
#define RSA_SIZE_BYTES 128
#endif

#if TESTNUM==0
// test data
const uint8_t privexp_arr[] = {0xA1,0x11,0xAD,0xAD,0x48,0x88,0xF5,0x2D,0x35,0xF5,0x42,0x8E,0x39,0x39,0x68,0x06,0xBE,0x32,0x52,0x5C,0xDA,0x2B,0xF2,0x2A,0x27,0x58,0x1B,0xDE,0xEE,0x18,0x63,0x92,0xD8,0x9F,0x02,0x2C,0xFB,0xDF,0x77,0xE6,0x1F,0xDB,0xDC,0x84,0x6C,0x90,0x38,0xA0,0x8D,0x8A,0xEB,0x5C,0x2A,0xF7,0xCC,0x25,0x9D,0x62,0xBA,0xB5,0xB2,0xB8,0x7B,0xCD,0x66,0xD6,0x77,0xD5,0x32,0x9D,0xF1,0x98,0x9C,0xB1,0xAC,0x50,0x23,0x7C,0xCF,0x28,0x69,0x32,0xD9,0x3A,0x21,0x82,0x9D,0xE0,0xE1,0xBA,0x12,0x3C,0x79,0x95,0x10,0x7A,0x50,0x6E,0xA2,0x91,0x87,0x04,0x2B,0x6F,0xE4,0x8C,0x05,0x51,0x31,0x81,0x50,0xE9,0x52,0x69,0x09,0xCF,0x68,0x1D,0x74,0x88,0x6B,0x17,0x43,0xE8,0xFD,0x9C,0x7B,0x04};
const uint32_t publexp_arr [] = {0x10001,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint8_t modulus_arr[] = {0x49,0xF5,0xEB,0x73,0x5B,0x82,0x9C,0xEB,0x4B,0xC2,0xAF,0x74,0x64,0x29,0x38,0xA8,0xAF,0x7E,0xA4,0x77,0xBA,0x9C,0x79,0xB6,0x9B,0x5E,0x65,0xBC,0xBA,0x74,0x84,0x3E,0x84,0xBF,0x5C,0xD4,0xD1,0xF4,0xEC,0xD4,0x83,0x3D,0xC6,0x9B,0x7B,0x52,0x5C,0x2F,0x25,0x79,0x6D,0x21,0x79,0xB3,0x31,0x7A,0x0D,0xAD,0xB1,0xB9,0xDC,0x5F,0xE5,0x3D,0x13,0x21,0xF6,0xFB,0x97,0x1A,0xFB,0xB9,0x7F,0x4D,0x26,0x0F,0x10,0x37,0xEA,0xEA,0xEC,0x97,0xA4,0x79,0x37,0xFB,0x62,0x33,0x9E,0xB3,0x28,0xC4,0x30,0x8A,0xA6,0x94,0x9A,0x9F,0x0D,0xDF,0xE2,0xF5,0xB4,0x1F,0x25,0x4F,0xE1,0x6F,0x35,0xBF,0x82,0xBF,0xE6,0xA2,0xA0,0x15,0x80,0xA1,0x69,0x97,0xD8,0x3D,0x85,0x88,0x9E,0x88,0x4D,0xD9};
const uint8_t ciphertext_golden_ans[] = {0xF0,0xCA,0x37,0xC7,0xFA,0x38,0xB3,0xDF,0x00,0xA6,0xFA,0x10,0x14,0xEA,0xD7,0x36,0x83,0x61,0x5F,0x12,0x29,0x6C,0x19,0xC3,0x3A,0xC6,0x03,0xC9,0x74,0xF2,0x9E,0x57,0x68,0x2C,0xA8,0xAD,0xE6,0xAF,0x27,0x35,0xEF,0xD6,0x33,0x34,0xA8,0x0F,0x8E,0x2D,0x84,0xA5,0xA9,0xF3,0xC6,0x9A,0xF7,0xC9,0xB6,0x9B,0x12,0x0E,0xF3,0x40,0x6E,0x8E,0x2A,0x40,0x4B,0x6C,0x63,0x6B,0x42,0xEC,0xE6,0xB5,0x2E,0x1D,0x5A,0x95,0xFF,0x8E,0xAF,0xB3,0x24,0x8D,0x88,0x01,0x61,0x42,0x1D,0xA9,0x80,0x93,0xD2,0xE9,0x04,0x30,0x63,0x43,0x16,0xC1,0xD0,0xCC,0xFD,0xD1,0xA0,0xA8,0xC3,0xD0,0x73,0xF6,0x66,0x38,0x95,0x42,0xA1,0x75,0x77,0xD1,0xE2,0xBB,0xB8,0x49,0x7B,0x78,0x6F,0x66,0x44,0x93};
const uint32_t plaintext_golden_ans[] = {0x726C6421,0x2C20576F,0x656C6C6F,0x00000048,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#else

const uint8_t privexp_arr[] = {0x71,0x36,0xB3,0x46,0x0F,0x44,0xFB,0xAB,0x4B,0xF6,0x94,0xD6,0xAC,0xAF,0x94,0x10,0x0C,0x97,0xE4,0xA6,0x71,0x6B,0x68,0xA2,0xD1,0x52,0x33,0x03,0x01,0xC1,0x9A,0xD3,0xC7,0xFA,0x1F,0x27,0xFD,0x6C,0x61,0x83,0xD2,0xF2,0x97,0x56,0xC6,0x89,0xAD,0xF8,0x97,0x2C,0x34,0x4C,0x0D,0x4F,0x44,0x4A,0xD1,0xDD,0x6A,0xA4,0x23,0x3F,0x84,0x56,0x9F,0x49,0x12,0x78,0x7E,0x76,0x20,0x67,0x79,0xCD,0x74,0xDA,0x0C,0x22,0x9D,0x72,0xEA,0x49,0x71,0xF1,0xF9,0x3F,0x38,0x57,0xA2,0x2C,0xF1,0x07,0x6F,0xB5,0x6F,0x6E,0x64,0x42,0xDC,0xB9,0x11,0x03,0x62,0x29,0x60,0xDA,0x8F,0x63,0x28,0x82,0xAD,0xC2,0x04,0xBC,0xB6,0x94,0x7F,0x1F,0x32,0x50,0x07,0x7C,0xD8,0x9D,0xF1,0x0C,0x02,0x10};
const uint32_t publexp_arr [] = {0x10001,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
const uint8_t modulus_arr[] = {0x61,0xB7,0x07,0x3E,0x44,0xC5,0xF9,0x93,0x3C,0x1E,0x25,0x47,0x94,0x8F,0x1C,0x1A,0x0E,0xEB,0x91,0x36,0x27,0x56,0x00,0x84,0xB8,0x96,0xDC,0x66,0xB1,0x4D,0x9E,0x83,0xC1,0x73,0x81,0x74,0x4D,0x94,0x56,0x40,0xE4,0x4F,0x54,0x4A,0x6E,0xFB,0xDF,0x64,0x26,0x78,0x44,0x5F,0x86,0xDC,0xFB,0x5C,0x85,0x0C,0x01,0x2B,0x38,0x2A,0xB4,0x32,0xA2,0x5F,0x24,0x1A,0xEC,0x2E,0xB3,0xFC,0x2C,0x51,0x5A,0x97,0xBD,0x49,0xB2,0x6A,0xED,0x06,0x48,0x68,0x49,0x2B,0x43,0x81,0x9F,0x8F,0xE4,0x62,0xBC,0xEA,0x79,0xD3,0x4B,0x86,0xA9,0xBC,0xE6,0xB6,0xF4,0xE4,0x2D,0x11,0x2D,0x39,0x29,0x81,0xC8,0xD3,0x60,0x99,0x75,0x94,0x2E,0x42,0xE0,0xB9,0xB8,0x86,0xE1,0x1A,0x85,0xEF,0x4A,0xF5};
const uint8_t ciphertext_golden_ans[] = {0xE0,0x0C,0x0A,0x0A,0x64,0x52,0xC3,0x48,0x55,0x7B,0x94,0xD1,0xB5,0xF8,0x69,0x34,0x5B,0xB7,0x1B,0xF7,0x74,0xFE,0x29,0x65,0x14,0xD7,0x1E,0x85,0xE2,0x2E,0x32,0xDC,0x0A,0xFA,0xCD,0x55,0x16,0x8B,0x89,0xF8,0x85,0xC5,0xD9,0xF5,0x97,0x1A,0x6E,0x01,0x90,0xD4,0x52,0x7D,0xAC,0x1A,0x47,0xCC,0x47,0xBF,0x8D,0x2E,0x22,0x70,0xC0,0xBD,0x4F,0x1E,0x57,0x5F,0xC2,0x5A,0xC4,0xEB,0x84,0x23,0x84,0x05,0x77,0x85,0x05,0xB9,0xC4,0x7E,0x92,0x86,0xAD,0xB7,0xDE,0xA4,0x32,0x4D,0x5F,0xCD,0x8C,0x5D,0xC2,0x9E,0xDD,0x99,0x1C,0xD9,0xE5,0x25,0x75,0x24,0xD1,0x79,0x62,0x30,0x30,0xEB,0x94,0xEF,0xA2,0xF0,0xBB,0xA9,0xFC,0xC6,0x91,0x27,0xD1,0xFF,0xAC,0xFC,0x29,0xC7,0xED,0x99};
const uint32_t plaintext_golden_ans[] = {0x1D,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

#endif


const char* devstr = "/dev/wsrsachar";

static void dumpmsg( uint8_t *pbuf ) {
    int index;
    printf("0x%X",pbuf[0]);
    for( index = 1; index < RSA_SIZE_BYTES; index++ ) {
        printf(",0x%X", pbuf[index]);
    }
    printf("\n");
}

int main (void)
{
    int ret, fd, errcnt;

    // This is the structure we pass to kmem when we write to it
    RSAPublic_t pubdata;
    memcpy(pubdata.base, plaintext_golden_ans, RSA_SIZE_BYTES);
    memcpy(pubdata.exponent, publexp_arr, RSA_SIZE_BYTES);
    memcpy(pubdata.modulus, modulus_arr, RSA_SIZE_BYTES);

    printf("RSA VALS: \n");
    printf("base = ");dumpmsg(pubdata.base);
    printf("exp  = ");dumpmsg(pubdata.exponent);
    printf("mod  = ");dumpmsg(pubdata.modulus);
    printf("sizeof(RSAPublic_t) = %d\n",sizeof(RSAPublic_t));
    //for (int i=0; i<RSA_SIZE_BYTES; i++)
    //    printf(",0x%02X",pubdata.base[i]);
    //printf("\n");


    // Open the device with read/write access
    printf("Beginning RSA test...\n");
    printf("Looking for <%s>\n",devstr);
    fd = open(devstr, O_RDWR);             
    if (fd < 0){
        perror("Failed to open the device, ERROR: ");
        return errno;
    }
    errcnt=0;
    
    // initialize result buffer
    uint8_t buf[RSA_SIZE_BYTES];
    memset(buf,0,RSA_SIZE_BYTES);

    // Display text to encrypt/decrypt
    printf(">>>TEST: PLAINTEXT = \n");
    dumpmsg((uint8_t*)plaintext_golden_ans);

    // Set mode to encrypt
    printf(">>>TEST: (IOCTL) SET MODE TO ENCRYPT\n");
    ret = ioctl(fd, IOCTL_SET_MODE, ENCRYPT); // switch mode 
    if (ret < 0) {
        perror(">>>TEST: Failed to set mode to encrypt.");
        return errno;
    }
 
    // Encrypt using public key by Writing base,exponent,modulus to module
    printf(">>>TEST: WRITE \n");
    ret = write(fd, &pubdata, sizeof(RSAPublic_t)); // write key 
    if (ret < 0) {
        perror(">>>TEST: Failed to write public data to the device.");
        return errno;
    }
    
    // Read back encrypted data
    printf(">>>TEST: READ \n");
    ret = read(fd, buf, RSA_SIZE_BYTES);        
    if (ret < 0){
        perror("Failed to read encrypted data from the device.");
        return errno;
    }
    
    // display encrypted data
    printf(">>>TEST: Received ciphertext:\n");
    dumpmsg(buf);

    // Check encrypted data against ground truth
    printf(">>>TEST: CHECKING ENCRYPTED DATA\n");
    if (memcmp(buf, ciphertext_golden_ans, RSA_SIZE_BYTES))
    {
        printf(">>>TEST: ERROR, ENCRYPTED DATA NOT CORRECT\n");
        return -1;
    }

    // Set mode to SET_PRIVKEY to load private exponent from BRAM 
    printf(">>>TEST: IOCTL SET PRIVATE KEY\n");
    ret = ioctl(fd, IOCTL_SET_MODE, SET_PRIVKEY);
    if (ret < 0) {
        perror(">>>TEST: Failed to set mode to SET_PRIVKEY\n");
        return errno;
    }

    // Set mode to Decrypt
    printf(">>>TEST: IOCTL SET MODE DECRYPT\n");
    ret = ioctl(fd, IOCTL_SET_MODE, DECRYPT); 
    if (ret < 0) {
        perror(">>>TEST: Failed to set mode to DECRYPT\n");
        return errno;
    }

    // load ciphertext into structure as new base
    // NOTE: exponent will be ignored in this case
    memcpy(pubdata.base, buf, RSA_SIZE_BYTES);

    // Clear ciphertext out of result buffer
    memset(buf,0,RSA_SIZE_BYTES);

    // Write ciphertext back to hardware
    printf(">>>TEST: DECRYPT WRITE \n");
    ret = write(fd, &pubdata, sizeof(RSAPublic_t)); 
    if (ret < 0) {
        perror(">>>TEST: Failed to write encrypted data to the device.");
        return errno;
    }

    // read back plaintext into buffer
    printf(">>>TEST: DECRYPT READ \n");
    ret = read(fd, buf, RSA_SIZE_BYTES);        
    if (ret < 0){
        perror(">>>TEST: Failed to read decrypted data back from the device.");
        return errno;
    }

    // Display decrypted data
    printf(">>>TEST: DECRYPTED DATA:\n");
    dumpmsg(buf);

    // check decrypted data against original message
    if (memcmp(buf, plaintext_golden_ans, RSA_SIZE_BYTES))
    {
        printf("ERROR: DECRYPTED DATA NOT CORRECT\n");
        return -1;
    }

    //// test get mode IOCTL for each mode
    //printf(">>>TEST: IOCTL_GET_MODE\n");
    //char mode;
    //for (int i=0; i<4; i++)
    //{
    //    ret = ioctl(fd, IOCTL_SET_MODE, i);
    //    if (ret < 0){
    //        perror("\tIOCTL_SET_MODE failed: ");
    //        return errno;
    //    }
    //    ret = ioctl(fd, IOCTL_GET_MODE, (ciphermode_t*)&mode); 
    //    printf("\t mode = %d\n",mode);
    //    if (ret < 0){
    //        perror("IOCTL_GET_MODE failed: ");
    //        return errno;
    //    }
    //    if ((char)mode != i)
    //    {
    //        printf(">>>TEST: GET MODE DOESN'T MATCH\n");
    //        return -1;
    //    }
    //}
    
    // close and exit
    if(close(fd)<0)
        perror(">>>TEST: Error closing file");


    printf(">>>TEST: Success!\n");
    return 0;
}


