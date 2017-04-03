#include "bank.h"

/*
	Author: Benjamin Kaiser
	Description:  This file contains all the 
	function prototypes associated with a customer.  
*/
int request_resources(int customer_num, int request[]);
int release_resources(int customer_num, int release[]);
void* customer_function(void* param);
