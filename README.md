# SSH0Day2023
0 DAY in SSH FIXED CODE. The author of this discovery is Twitter.com/Clumsylulz, i only fixed his version following his recomendations to ensure its stability and security:

-Increase the size of the buffer allocation to 29 bytes to avoid buffer overflow issues. 

-Correct the return address calculation by using the buffer size instead of the packet length. 

-Correct the format string in the printf statement for the return address. 

-Check the return values of the "open" and "write" functions, and handle errors appropriately. 

-Free the memory allocated for the "buffer" and "ssh" pointers. Replace the "system" function with a safer alternative, such as "execvp".
