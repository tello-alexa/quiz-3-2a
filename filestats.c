#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    // open directory
    DIR *dir_stream;
    struct dirent *directory;
    dir_stream = opendir(argv[1]);
    if(dir_stream) {
        // get stats from each file in directory
        while((directory = readdir(dir_stream)) != NULL) {
            struct stat file_stats;
            if(stat(directory->d_name, &file_stats) == -1) {
                perror("stat");
                return 1;
            }

            // print stats for current file
            printf("File name: %s\n", directory->d_name);
            printf("inode number: %ld\n", file_stats.st_ino);
            printf("number of links: %ld\n", file_stats.st_nlink);
            printf("User ID of owner: %d\n", file_stats.st_uid);
            printf("Group ID of owner: %d\n", file_stats.st_gid);
            printf("Size in bytes: %ld\n", file_stats.st_size);
            printf("Last access: %ld : %s", file_stats.st_atime, ctime(&file_stats.st_atime));
            printf("Last modification: %ld : %s", file_stats.st_mtime, ctime(&file_stats.st_mtime));
            printf("Last status change: %ld : %s", file_stats.st_ctime, ctime(&file_stats.st_ctime));
            printf("Number of disk blocks allocated: %ld\n", file_stats.st_blocks);    
 
            // format file permissions to flags and octal
            int octal = 0;
            char flags[10] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
            if(file_stats.st_mode & S_IRUSR) {
                flags[0] = 'r';
                octal += 400;
            }
            if(file_stats.st_mode & S_IWUSR) {
                flags[1] = 'w';
                octal += 200;
            }
            if(file_stats.st_mode & S_IXUSR) {
                flags[2] = 'x';
                octal += 100;
            }
            if(file_stats.st_mode & S_IRGRP) {
                flags[3] = 'r';
                octal += 40;
            }
            if(file_stats.st_mode & S_IWGRP) {
                flags[4] = 'w';
                octal += 20;
            }
            if(file_stats.st_mode & S_IXGRP) {
                flags[5] = 'x';
                octal += 10;
            }
            if(file_stats.st_mode & S_IROTH) {
                flags[6] = 'r';
                octal += 4;
            }
            if(file_stats.st_mode & S_IWOTH) {
                flags[7] = 'w';
                octal += 2;
            }
            if(file_stats.st_mode & S_IXOTH) {
                flags[8] = 'x';
                octal += 1;
            }
            printf("Access mode in octal: %d\n", octal);
            printf("Access mode flags: %s\n\n", flags);      
        }
        closedir(dir_stream);
    }

    return 0;
}