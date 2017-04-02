#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int PAGE_SIZE = 4096;

unsigned long calculate_page_number(unsigned long address)
{
	return address / PAGE_SIZE;
}
unsigned long calc_offset(unsigned long address)
{
	return address % PAGE_SIZE;
}

int main(int argc, char *argv[])
{
	unsigned long address = 0;
	unsigned long page_num = 0;
	unsigned long offset = 0;


    if ( argc != 2 ) /* argc should be 2 for correct execution */
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s address\n", argv[0] );
		return 1;
    }

	address = strtoull(argv[1], NULL, 0);
	page_num = calculate_page_number(address);
	offset = calc_offset(address);

	printf("The address %u contains\npage number = %u\noffset = %d\n", address, page_num, offset);

	return 0;
}
