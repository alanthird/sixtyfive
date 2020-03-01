/* the main set of chops, oh yes it is */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include "mem.h"
#include "opcodes.h"
#include "registers.h"

#undef DEBUG

int filesize(char *fn)
{
    struct stat *buf = malloc(sizeof(struct stat));
    if (stat(fn, buf) == 0) {
        return (buf->st_size);
    }
    return (-1);
}

int main(int argc, char* argv[])
{
    HEX_PAIR saddr;     /* start address for execution */
    FILE* fh;           /* input filehandle */
    void* input;        /* the code being read in */
    int fsize;          /* the size of the file of code */
    
    if (argc != 2) {
        fprintf(stderr, "Syntax: %s <file>\n", argv[0]);
        exit(1);
    }
    
    /* filename to load is argv[1] */

    allocateram();

    fh = fopen(argv[1], "rb");  /* open in binary mode in case we port to DOS */
    
    if (fh == NULL) {
        perror("main: Could not open input file");
        exit(1);
    }

#ifdef DEBUG
    printf("Opened file\n");
    fflush(stdout);
#endif
    
    /* find the size of the file, allocate a buffer, slurp it in */
    
    fsize = filesize(argv[1]); 

#ifdef DEBUG
    printf("Size of file: %d bytes\n", fsize);
    fflush(stdout);
#endif

    if (fsize <= 0) {
        fprintf(stderr, "main: Input file too small\n");
        exit(1);
    }
    
    if((input = malloc(fsize)) == NULL) {
        perror("main: Could not allocate RAM");
        exit(1);
    }

#ifdef DEBUG
    printf("Allocated RAM\n");
    fflush(stdout);
#endif
    
    if (fread(input, 1, fsize, fh) < fsize) {
        /* failed to read the whole file */
        perror("main: Could not read input file");
    }

#ifdef DEBUG
    printf("Read in file\n");
    fflush(stdout);
#endif
    
    fclose(fh);
    
    printf("%x\n", *(unsigned int*)input);

    blockwrite(input, 0x8000, fsize);

#ifdef DEBUG
    printf("Copy stuff to 6502 RAM\n");
    fflush(stdout);
#endif
    free(input);
    
    memwrite(0x00, 0xfffc);
    memwrite(0x80, 0xfffd);

    writepc(saddr.w);

    while (readpc()<0xfffa)
      {
	execute();                          /* :-> */
	printf("%c%c%c%c\r", memread(0x2000), memread(0x2001), memread(0x2002), memread(0x2003));
      }

    printf("\nA register: %x, X register: %x, Y register: %x\n", readareg(), readxreg(), readyreg());

    return 0;
}
