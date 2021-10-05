# NixPM

A simple tool to add packages to your Nix config, written in compiler agnostic C!

## Usage: 
```
nixpm <OPTIONS> [ARGUMENTS]...
Easily add packages to your Nix config.

  -d, --dryrun    print generated config to stdout without overwriting any files (not yet implemented)
  -f, --file      set the file to modify
  -g, --generate  generate a new config (not yet implemented)
  -h, --help      display this help and exit
  -p, --packages  set the packages to install
  -v, --version   output version information and exit

Examples:
  nixpm -f packages.nix -p firefox, latte-dock - Add Firefox and Latte Dock to 'packages.nix'.
  nixpm --generate --file packages.nix - Generate a new config and write it to 'packages.nix' (not yet implemented).
```

## Compiling:
You can compile this project with any compiler that supports c99 or newer, using 
```
<compiler name> src/cmd.c src/config.c
```
Or by running `make`, which will use your system's default compiler.

## Contributing:
The code is far from perfect, and if you find anything wrong or would like a feature to be added, please open an issue or a pull request!

## Screenshots:
![Screenshot_20211005_171524](https://user-images.githubusercontent.com/49573906/136103749-efc1f15f-1b9d-455b-aa4f-0d979d7c254a.png)
