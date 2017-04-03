/*
	CSC 456 Operating Systems
	Spring 207
	Dr. Christer Karlsson
	Author:	Benjamin Kaiser

	Description:  This program is a simple program to help students understand virtual memory better.  
	it takes one command line argument which is a 32 bit memory address in decimal form.  It then prints
	to standard out the page number and the offset into that page of the number.  
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// constant to easily change the size in bytes of the page.  
const int PAGE_SIZE = 4096;

/*
	Author: Benjamin Kaiser
	Description:  This function takes in a 32 bit address and divides by the page size to discover which 
	page number the address is on.  This is returned.
*/
unsigned long calculate_page_number(unsigned long address)
{
	return address / PAGE_SIZE;
}
/*
	Author: Benjamin Kaiser
	Description:  This function takes in a 32 bit address and mods by the page size to
	discover where in the specified page it is in.  This is returned.  
*/
unsigned long calc_offset(unsigned long address)
{
	return address % PAGE_SIZE;
}

/*
	Author: Benjamin Kaiser
	Description:  This is the main function for the memory management 
*/
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

	address = strtoul(argv[1], NULL, 0);
	page_num = calculate_page_number(address);
	offset = calc_offset(address);

	printf("The address %lu contains\npage number = %u\noffset = %u\n", address, page_num, offset);

	return 0;
}
