#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <fcntl.h>
int main() {
    char inp[100];
    char address[] = "Desktop";
	char lsaddress[100];
	strcat(lsaddress,"Desktop");
    while (1) {
        printf("Please enter a command:\n");
        fgets(inp, sizeof(inp), stdin);
        inp[strcspn(inp, "\n")] = 0;

        if (strcmp(inp, "exit") == 0) {
            printf("bye bye\n");
            break;
        } 
        
        else if (strcmp(inp, "cd") == 0) {
            char substrs[100];
            printf("Please enter directory name:\n");
            fgets(substrs, sizeof(substrs), stdin);
            substrs[strcspn(substrs, "\n")] = 0;
            
            ssize_t i = 0;
    ssize_t j = 0;
    ssize_t k = 0;

    while (address[i] != '\0') {
        if (address[i] == substrs[j]) {
            k = i;
            while (substrs[j] != '\0') {
                if (address[k] == substrs[j]) {
                    k++;
                    j++;
                } else {
                    break;
                }
            }
            if (substrs[j] == '\0') {
                break; 
            }
        }
        i++;
    }

    if (substrs[j] == '\0') {
        while (address[k] != '\0') {
            printf("%c", address[k]);
            k++;
        }
        printf("\n");
    } else {
        printf("file not found.\n");
    }
        } else if (strcmp(inp, "ls") == 0) {
            printf("%s\n", lsaddress);
        } else if (strcmp(inp, "cp") == 0) {
        char src[100];
char dest[100];
  printf("enter source file:\n");
            fgets(src, sizeof(src), stdin);
            src[strcspn(src, "\n")] = 0;

  printf("Please enter dest file:\n");
            fgets(dest, sizeof(dest), stdin);
            dest[strcspn(dest, "\n")] = 0;

        
         
    char arr[100];
    ssize_t chread, chwrite;
int sfile, dfile;
    sfile = open(src, O_RDONLY);
    if (sfile == -1) {
        printf("file nahi open");
       
    }
	dfile = open(dest, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dfile == -1) {
        printf("dest nahi bani");
        close(sfile);
    }

    chread = read(sfile, arr, 100);
        chwrite = write(dfile, arr, chread);
        if (chwrite != chread) {
            printf("Write error");
            close(dfile);
            close(sfile);
        }
    

    if (chread == -1) {
        perror("Read error");
        close(sfile);
        close(dfile);
    }

    close(sfile);
    close(dfile);
        
            //printf("cp\n");
        } else if (strcmp(inp, "pwd") == 0) {
        
    printf("%s\n", lsaddress);

        } else if (strcmp(inp, "mv") == 0) {

char temp5[100];
char temp6[100];
  printf("Please enter file name to rename:\n");
            fgets(temp5, sizeof(temp5), stdin);
            temp5[strcspn(temp5, "\n")] = 0;

  printf("Please enter name for rename:\n");
            fgets(temp6, sizeof(temp6), stdin);
            temp6[strcspn(temp6, "\n")] = 0;



           int t = rename(temp5, temp6);
    if (t != 0) {
        printf("error in mv\n");
    }
    else
    {
    printf("File renamed or mv.\n");
           
            }//printf("mv\n");
        } else if (strcmp(inp, "mkdir") == 0) 
        
        {
        
            char temp1[100];
            printf("Please enter file name:\n");
            fgets(temp1, sizeof(temp1), stdin);
            temp1[strcspn(temp1, "\n")] = 0;
            
            strcat(lsaddress, "/");
            strcat(lsaddress, temp1);
            
            
            
            
        } else if (strcmp(inp, "rmdir") == 0) {
		char substrs[100];
            printf("Please enter directory name:\n");
            fgets(substrs, sizeof(substrs), stdin);
            substrs[strcspn(substrs, "\n")] = 0;
            
                ssize_t i = 0;
    ssize_t j = 0;
    ssize_t k = 0;

    while (lsaddress[i] != '\0') {
        if (lsaddress[i] == substrs[j]) {
            k = i;
            while (substrs[j] != '\0') {
                if (lsaddress[k] == substrs[j]) {
                    k++;
                    j++;
                } else {
                    break;
                }
            }
            if (substrs[j] == '\0') {
                break;
            }
        }
        i++;
    }

    if (substrs[j] == '\0') {
        ssize_t len = strlen(substrs);
        while (len >= 0) {
            lsaddress[k - len] = ' ';
            len--;
        }

    } else {
        printf("Substring not found.\n");
    }

            //removestarr(address, temp);        
            //printf("rmdir\n");
        } else if (strcmp(inp, "rm") == 0) {
            
            char temp3[100];
 printf("please enter file name to del: ");
             fgets(temp3, sizeof(temp3), stdin);
            temp3[strcspn(temp3, "\n")] = 0;

        
    int concl = remove(temp3);

    if (concl == 0) {
        printf("File '%s'del ho gayi.\n", temp3);
    } else {
        perror("Error del file");
    }

            //printf("rm\n");
        } else if (strcmp(inp, "touch") == 0) {
              int fd;
char temp2[100];
 printf("please enter file name : ");
             fgets(temp2, sizeof(temp2), stdin);
            temp2[strcspn(temp2, "\n")] = 0;
            
    fd = open(temp2, O_WRONLY | O_CREAT, 0644);

    if (fd == -1) {
        printf("file nahi bani.\n");
        return 1;
    }

    close(fd);

    printf("yahoo! File ban gayi.\n");
            
            
            //printf("touch\n");
        } else if (strcmp(inp, "grep") == 0) {
        char tosearchstring[100];
            //printf("please enter string to search : ");
             //fgets(tosearchstring, sizeof(tosearchstring), stdin);
            //tosearchstring[strcspn(tosearchstring, "\n")] = 0;

char filename[100];
    char buffer[100];
    int count = 0;
    printf("Enter the filename: ");
    scanf("%s", filename);
    printf("Enter the string to search: ");
    scanf("%s", tosearchstring);

    int file = open(filename, O_RDONLY);
    if (file == -1) {
        perror("Error opening file");
        return 1;
    }

    ssize_t bytes_read;
    bytes_read = read(file, buffer, sizeof(buffer));
        char *ptr = strstr(buffer, tosearchstring);
        while (ptr != NULL) 
        {
            count++;
            ptr = strstr(ptr + 1, tosearchstring);
        }
    
    if (bytes_read == -1) {
        perror("Error reading file");
        close(file);
        return 1;
    }

    if (close(file) == -1) {
        perror("Error closing file");
        return 1;
    }

    int output_file = open("opt.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (output_file == -1) {
        perror("Error creating output file");
        return 1;
    }
    
    dprintf(output_file, "Total occurrences of '%s': %d\n", tosearchstring, count);
    
    if (close(output_file) == -1) {
        perror("Error closing output file");
        return 1;
    }

    printf("Total occurrences of '%s': %d\n", tosearchstring, count);

 
        } else {
            printf("Invalid command. Please enter a valid command.\n");
        }
    }
    return 0;
}
	

