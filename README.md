# Palindrome

`pal` is a program that outputs whether input strings are palindromes; there are options to ignore case sensitivity, punctuation, and whitespace.

## Build

Use [`make`](https://www.gnu.org/software/make/) to build, clean, and delete the program.

### Usage

```
make [targets]
```

### Targets

| Target   | Description                          |
|----------|--------------------------------------|
| `all`    | Build the program.                   |
| `clean`  | Remove object files.                 |
| `delete` | Remove object files and the program. |
| `help`   | Display the usage message.           |

## Run

### Usage

```
usage: pal [options] string...
```

### Options

| Short Flag | Long Flag       | Description                  |
|------------|-----------------|------------------------------|
| `-h`       | `--help`        | Display the usage message.   |
| `-l`       | `--lower`       | Ignore case sensitivity.     |
| `-p`       | `--punctuation` | Ignore punctuation.          |
| `-s`       | `--space`       | Ignore whitespace.           |
| `-v`       | `--version`     | Display the program version. |