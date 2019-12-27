/**
 * Name:        Blair Muraoka
 * Homework:    7a
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-01-2016
 * File:        main.c
 * 
 * Description: Driver file. Handles manipulation of the file header and calls
 *              readfile, writefile, and printheader to interact with the buffer.
 *              If any values are not zero or ffff, it will be fixed within the function.
 */
#include <stdio.h>
#include <math.h>

unsigned char buffer[20];

int main(int argc, char * argv[])
{
    int pass, i;
    unsigned char swap[2];
    pass = readfile("test.bin");
    unsigned int newSeq = 0;
    
    if (pass != 0)
    {
        printf("Cannot open file\n");
        exit(0);
    }
    printheader();
    
    // The response file will switch the source and destination ports
    memcpy(&swap, &buffer[0], 2);
    memcpy(&buffer[0], &buffer[2], 2);
    memcpy(&buffer[2], &swap, 2);
    
    // The sequence number must be incremented by 1 for the response
    newSeq += (buffer[4] * pow(256, 3)) + (buffer[5] * pow(256, 2));
    newSeq += (buffer[6] * pow(256, 1)) + (buffer[7] * pow(256, 0));
    newSeq++;
    
    buffer[4] = (newSeq >> 24) & 0xFF;
    buffer[5] = (newSeq >> 16) & 0xFF;
    buffer[6] = (newSeq >> 8)  & 0xFF;
    buffer[7] = newSeq & 0xFF;
    
    // The acknowledgment number of the response must be sequence number of the request
    newSeq--;
    buffer[8]  = (newSeq >> 24) & 0xFF;
    buffer[9]  = (newSeq >> 16) & 0xFF;
    buffer[10] = (newSeq >> 8)  & 0xFF;
    buffer[11] = newSeq & 0xFF;
    
    // Make sure reserved is zero in response
    buffer[12] &= 0xF0;
    buffer[13] &= 0x3F;
    
    // Testing different values for flags buffer[13] &= 0x0B;
    
    // If the SYN flag is set in the request, both the SYN and ACK flags must be set in the response
    if (buffer[13] & 0x02)
    {
        buffer[13] |= 0x12;
    }
    
    // Window must be zero
    buffer[14] &= 0x00;
    buffer[15] &= 0x00;
    
    // Make sure checksum is FFFF in the response
    buffer[16] = buffer[16] | 0xFF;
    buffer[17] = buffer[17] | 0xFF;
    
    // Urgent pointer must be zero
    buffer[18] &= 0x00;
    buffer[19] &= 0x00;
    
    writefile("test2.bin");
    readfile("test2.bin");
    printheader();
    return 0;
}
