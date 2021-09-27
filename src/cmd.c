#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <errno.h>

int main(int argc, char **argv){
  int c;
  static int dryrun_flag = 0;

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

        case 'h':
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
          break;

        case 'v':
          puts("NixPM version 0.1.0\n"
               "Copyright © 2021 NixPM contributors\n"
               "Licensed under the MIT license, which you can find here:\n"
               "https://opensource.org/licenses/MIT");
          break;

        default:
          exit(EINVAL);
        }
  }
  return 0;
}