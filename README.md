# FFT - The Fast Fourier Transform

This project illustrates how to successfully test-drive an algorithm-based software solution that employs techniques from electrical engineering and signal processing.

The objective is to implement an FFT library in C that performs a radix-2 decimation-in-time FFT of a signal. The bit-reversal operations need to be lean, and the FFT evaluation loops need to be efficient for general use.

The baseline development environment is as follows:
* The code is written in ANSI C.
* The code builds and runs on Ubuntu 14.04 LTS or Ubuntu 16.04 LTS.
* The code builds and runs using GCC as the compiler toolchain and GNU make as the project build environment.
* Git is used for version control.
* The libcheck (https://github.com/libcheck/check) testing framework is used for unit testing.

Other development environments are certainly suitable (e.g., Xcode, Eclipse, etc.) but the project must build and run in the baseline environment specified above.

Currently, there are three FFT approaches implemented:
1. In-place iterative solution
2. Recursive solution with even/odd vector buffers (this is what naturally implements the Cooley-Tukey equations)
3. Recursive solution with user-supplied scratchpad buffer
