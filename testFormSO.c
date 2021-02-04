#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 256
#define CPY_BUF_SIZE 64

void get_paths(char *src, char *dest) 
{
    printf("Please enter src path:\n");
    gets(src);
    src[strcspn(src, "\r\n")] = 0;
    printf("\nPlease enter dest path:\n");
    gets(dest);
    dest[strcspn(dest, "\r\n")] = 0;
}

int open_files(char *src, char *dest, FILE **src_file, FILE **dest_file) 
{
    *src_file = fopen(src, "r");
    if(!*src_file) 
	{
        printf("\n%s is not a valid file or permission denied\n", src);
        return EXIT_FAILURE;
    }

    *dest_file = fopen(dest, "w");
    if(!*dest_file) 
	{
        printf("\ncould not open %s for writing, check path exists and you have write permissions\n", dest);
        fclose(*src_file);
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int cpy(char *cpy_buf, FILE *src_file, FILE *dest_file) {
    size_t num_elements;
    while((num_elements = fread(cpy_buf, sizeof(char), sizeof(cpy_buf), src_file)) > 0) 
	{
        if(fwrite(cpy_buf, sizeof(char), num_elements, dest_file) != num_elements) 
		{
            fprintf(stderr, "\nError while writing to destination \nAborting...");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}


int main() 
{
    char src[BUF_SIZE];
    char dest[BUF_SIZE];
    char cpy_buf[CPY_BUF_SIZE];
    FILE *src_file;
    FILE *dest_file;

    get_paths(src, dest);
    fprintf(stdout, "\nAttempting to copy from %s to %s...\n", src, dest);

    if(!open_files(src, dest, &src_file, &dest_file))
        return EXIT_FAILURE;

    fprintf(stdout, "\nStarting copy from %s to %s...\n", src, dest);
    int success = cpy(cpy_buf, src_file, dest_file);
    fclose(src_file);
    fclose(dest_file);

    return success ? EXIT_FAILURE : EXIT_SUCCESS;
}
