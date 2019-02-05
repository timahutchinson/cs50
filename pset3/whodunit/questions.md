# Questions

## What's `stdint.h`?

Defines the size of ints (e.g., uint8_t, int32_t, etc.)

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

They allow for exact integer sizes.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1, DWORD = 4, LONG = 4, and WORD = 2

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

BM

## What's the difference between `bfSize` and `biSize`?

biSize is the number of bytes of the header (40), and bfSize is the number of bites of both headers plus the image.

## What does it mean if `biHeight` is negative?

It is "top-down", i.e., the origin is in the top left corner.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in lines 24 and 32 of `copy.c`?

The file couldn't be opened (perhaps it doesn't exist?)

## Why is the third argument to `fread` always `1` in our code? (For example, see lines 40, 44, and 75.)

The file only has a single header, and thus the curser is only advanced by the specified number of bytes once.

## What value does line 63 of `copy.c` assign to `padding` if `bi.biWidth` is `3`?

3

## What does `fseek` do?

Moves the file position indicator some number of bytes within a file being read.

## What is `SEEK_CUR`?

SEEK_CUR tells the fseek to advance the file position indicator the specified number of bytes from the current position.

