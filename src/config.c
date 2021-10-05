#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include "config.h"

long unsigned int get_file_size(const char *filename);

int insert_in_file(char *path, char *packages, int dryrun_flag){
    int file_size = get_file_size(path);
    char current_line[file_size], content[file_size], content_until_line[file_size], content_after_line[file_size];
    char tmp_path[strlen(path) + 5], packages_formatted[strlen(packages) + 6];
    char file_extension[] = ".tmp";
    int line_found = 0;

    memset(current_line, 0, sizeof current_line);
    memset(content, 0, sizeof content);
    memset(content_until_line, 0, sizeof content_until_line);
    memset(content_after_line, 0, sizeof content_until_line);
    memset(tmp_path, 0, sizeof tmp_path);
    memset(packages_formatted, 0, sizeof packages_formatted);
    
    strcpy(tmp_path, path);
    strcat(tmp_path, file_extension);
    sprintf(packages_formatted, "%s\n", packages);

    FILE *file = fopen(path, "r+");
    FILE *tmp_file = fopen(tmp_path, "wb");

    if(!file || !tmp_file){
        perror("Error");
        return 1;
    }

    while(fgets(current_line, file_size, file) != NULL){
        strcat(content, current_line);
        char *s_loc = strstr(current_line, "environment.systemPackages");
        if(line_found){
            strcat(content_after_line, current_line);
        }
        if(s_loc){
            strcpy(content_until_line, content);
            fprintf(tmp_file, "%s", content_until_line);
            fprintf(tmp_file, "%s", packages_formatted);
            line_found = 1;
        }
    }

    if(dryrun_flag){   
        printf("%s%s%s\n", content_until_line, packages_formatted, content_after_line);
        remove(tmp_path);
    }
    else{
        fprintf(tmp_file, "%s", content_after_line);
        fclose(tmp_file);
        rename(tmp_path, path);
    } 
    fclose(file);
    return 0;
}

long unsigned int get_file_size(const char *filename){
    struct stat stats;
    if (stat(filename, &stats) == 0)
        return (stats.st_size);
    else
        return 1;
}
