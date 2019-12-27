/**
 * Name:        Blair Muraoka
 * Homework:    7a
 * Class:       ICS 212-001
 * Instructor:  Ravi Narayan
 * Date:        11-01-2016
 * File:        iofunctions.c
 * 
 * Description: Handles reading a binary header provided and writes the corresponding
 *              response header to a separate file. Math header is included for convenience
 *              when working with powers
 */
#include <stdio.h>
#include <math.h>

extern unsigned char buffer[20];

int readfile(char []);
int writefile(char []);
int printheader();

/** 
 * Function name:   readfile
 * Description:     Reads an existing file's data and stores it's data in the
 *					a buffer.
 * Parameters:      filename[] - the name of the file being read
 * Return:			0 if successful read
 *					1 if file does not exist
 */
int readfile(char filename[])
{
    FILE *f = fopen(filename, "rb");;
    int counter = 0;
    int errorcode = 0;
    int n;
    int i = 0;
    char converted[41];
    
    if (!f)
    {
        printf("Cannot open file\n");
        errorcode = 1;
    }
    else
    {
        n = fread(buffer, 1, sizeof(buffer), f);
        
        fclose(f);
    }
    printf("%s\n", converted);
    if (errorcode == 1)
    {
        return 1;
    }
    return 0;
}

/** 
 * Function name:   writefile
 * Description:     Writes data from the buffer to a new file
 * Parameters:      filename[] - the name of the file being written to
 * Return:			0 if successful write
 *					1 if failure (if file is open or something)
 */
int writefile(char filename[])
{
    FILE *bin_file;
    int errorcode = 0;

    bin_file = fopen(filename, "wb");
    
    if (!bin_file)
    {
        printf("Cannot open file\n");
        errorcode = 1;
    }
    else 
    {
        fwrite(buffer, 20, 1, bin_file);
        
        fclose(bin_file);
    }
    
    if (errorcode == 1)
    {
        return 1;
    }
    return 0;
}

/** 
 * Function name:   printheader
 * Description:     Handles the conversions of the data into readable ints/hex/strings
 *                  and prints them.
 * Return:			0
 */
int printheader()
{
    
    int i;
    double j;
    unsigned int sourceport;
    unsigned int destination;
    unsigned int sequence    = 0;
    unsigned int acknowledge = 0;
    unsigned int dataoffset  = 0;
    unsigned int reserved    = 0;
    unsigned int window;
    unsigned int urgent;
    unsigned int mask;
    
    sourceport = (buffer[0] * pow(256, 1)) + (buffer[1] * pow(256, 0));
    
    destination = (buffer[2] * pow(256, 1)) + (buffer[3] * pow(256, 0));
    
    sequence += (buffer[4] * pow(256, 3)) + (buffer[5] * pow(256, 2));
    sequence += (buffer[6] * pow(256, 1)) + (buffer[7] * pow(256, 0));

    acknowledge += (buffer[8] * pow(256, 3)) + (buffer[9] * pow(256, 2));
    acknowledge += (buffer[10] * pow(256, 1)) + (buffer[11] * pow(256, 0));

    // Obtaining data offset value as an int
    j = 3;
    mask = 128; // 1000 0000
    for (i = 0; i < 4; i++)
    {
        if ((buffer[12] & mask) != 0)
        {
            dataoffset += 1 * pow(2, j);
        }
        j--;
        mask = mask >> 1;
    }
    
    // Obtaining reserved
    j = 5;
    for (i = 4; i < 8; i++)
    {
        if ((buffer[12] & mask) != 0)
        {
            reserved += 1 * pow(2, j);
        } 
        j--;
        mask = mask >> 1;
    }
    
    mask = 128; // 1000 0000
    if ((buffer[13] & mask) != 0)
    {
        reserved += pow(2, 1);
    }
    mask = mask >> 1;
    if ((buffer[13] & mask) != 0)
    {
        reserved += pow(2, 0);
    }
    mask = mask >> 1;
    
    window = (buffer[14] * pow(256, 1)) + (buffer[15] * pow(256, 0));
    
    urgent = (buffer[18] * pow(256, 1)) + (buffer[19] * pow(256, 0));
    
    
    //The actual printing now
    printf("Hex Values:\n");
    for (i = 0; i < sizeof(buffer); i++)
    {
       printf("%02X ", buffer[i]);
    }
    printf("\nDetailed print:\n");

    printf("source port: %u\n", sourceport);
    printf("destination port: %u\n", destination);
    printf("sequence number: %u\n", sequence);
    printf("acknowledgment number: %u\n", acknowledge);
    printf("data offset: %u\n", dataoffset);
    printf("reserved: %u\n", reserved);
    printf("flags: ");
    
    //Print the flags as text
	mask = 32; // 0010 0000
    for (i = 2; i < 8; i++)
    {
        if ((buffer[13] & mask) != 0)
        {
            if (i == 2)
            {
                printf("URG ");
            }
            else if (i == 3)
            {
                printf("ACK ");
            }
            else if (i == 4)
            {
                printf("PSH ");
            }
            else if (i == 5)
            {
                printf("RST ");
            }
            else if (i == 6)
            {
                printf("SYN ");
            }
            else if (i == 7)
            {
                printf("FIN ");
            }
        }
        mask = mask >> 1;
    }
    printf("\nwindow: %u\n", window);
    printf("checksum: 0x%02X%02X\n", buffer[16], buffer[17]);
    printf("urgent pointer: %u\n", urgent);
    
    return 0;
}
