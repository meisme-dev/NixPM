#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

long unsigned int get_file_size(const char *filename);
int parse_file(char *path);
void write_at_location(int location, const char *path, char *current_line);

int main(){
    int ret_val = parse_file("template.nix");
    return ret_val;
}

int parse_file(char *path){
    FILE *file = fopen(path, "r+");
    int file_size = get_file_size(path);
    char s[file_size], s_line[file_size], s_until_line[file_size], tmp_path[strlen(path) + 4];
    char env_path[] = "/usr/bin/env", cp_path[] = "cp", file_extension[] = ".tmp";
    strcpy(tmp_path, path);
    strcat(tmp_path, file_extension);
    pid_t pid = fork();
    if(pid){
        execl(env_path, cp_path, path, tmp_path, NULL);
    }
    else if(pid < 0){
        perror("Error");
    }
    else{
        wait(NULL);
        puts("Done!");
    }
    if(!file){
        perror("Error");
        return 1;
    }
    while(fgets(s_line, file_size, file) != NULL){
        strcat(s, s_line);
        char *s_loc = strstr(s_line, "environment.systemPackages");
        if(s_loc){
            printf("Found %s at %p\n", s_line, s_loc);
            printf("%s", s_until_line);
        }
    }
    printf("%s\n", s);
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
