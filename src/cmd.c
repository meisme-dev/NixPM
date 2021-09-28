#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>
#include <string.h>

#include "config.h"

void print_help();
void print_version();

int main(int argc, char **argv){
  int c;
  int filename_set;
  int packages_set;
  static int dryrun_flag = 0;

  struct Fields {
    char file_name[1024];
    char packages[1024];
  };
  
  struct Fields fields;

  while(1){
      static struct option long_options[] = {
          {"dryrun", no_argument, &dryrun_flag, 'd'},
          {"file", required_argument, 0, 'f'},
          {"generate", no_argument, 0, 'g'},
          {"help", no_argument, 0, 'h'},
          {"packages", required_argument, 0, 'p'},
          {"version", no_argument, 0, 'v'},
          {0, 0, 0, 0}
      };

      int option_index = 0;


      c = getopt_long (argc, argv, "df:ghp:v",
                       long_options, &option_index);
      if(c == -1)
        break;
      switch(c){
        case 0:
          if (long_options[option_index].flag != 0){
            break;
          }
          break;

        case 'f':
          strcpy(fields.file_name, optarg);
          filename_set = 1;
          break;

        case 'p':
          strcpy(fields.packages, optarg);
          packages_set = 1;
          break;

        case 'h':
          print_help();
          break;

        case 'v':
          print_version();
          break;

        default:
          exit(EINVAL);
        }
  }

  for(size_t i = 0; i <= strlen(fields.packages); i++){
    if(fields.packages[i] == ','){
      fields.packages[i] = '\n';
    }
    if(fields.packages[i] == ' ' && fields.packages[i-1] != 0){
      fields.packages[i] = fields.packages[i + 1];
      i++;
    }
  }
  if(filename_set && packages_set){
    insert_in_file(fields.file_name, fields.packages);
  }
  return 0;
}

void print_help(){
  puts("Usage: nixpm <OPTIONS> [ARGUMENTS]...\n"
       "Easily add packages to your Nix config.\n"
       "\n"
       "  -d, --dryrun    print generated config to stdout without overwriting any files\n"
       "  -f, --file      set the file to modify\n"
       "  -g, --generate  generate a new config\n"
       "  -h, --help      display this help and exit\n"
       "  -p, --packages  set the packages to install\n"
       "  -v, --version   output version information and exit\n"
       "\n"
       "Examples:\n"
       "  nixpm -f packages.nix -p firefox, latte-dock - Add Firefox and Latte Dock to `packages.nix`.\n"
       "  nixpm --generate --file packages.nix - Generate a new config and write it to `packages.nix`.");
}

void print_version(){
  puts("NixPM version 0.1.0\n"
     "Copyright © 2021 NixPM contributors\n"
     "Licensed under the MIT license, which you can find here:\n"
     "https://opensource.org/licenses/MIT");
}