# FFT - The Fast Fourier Transform

This project illustrates how to successfully test-drive an algorithm-based software solution that employs techniques from electrical engineering and signal processing.

The objective is to implement an FFT library in C that performs a radix-2 decimation-in-time FFT of a signal. The bit-reversal operations need to be lean, and the FFT evaluation loops need to be efficient for general use.

The baseline development environment is as follows:
* The code is written in ANSI C.
* The code builds and runs on Ubuntu 14.04 LTS or Ubuntu 16.04 LTS.
* The code builds and runs using GCC as the compiler toolchain and GNU make as the project build environment.
* Git is used for version control.
* The libcheck (https://github.com/libcheck/check) testing framework is used for unit testing.
* Valgrind (http://valgrind.org) is used to check for memory leaks.

Other development environments are certainly suitable (e.g., Xcode, Eclipse, etc.) but the project must build and run in the baseline environment specified above.

Currently, there are three FFT approaches implemented:
1. In-place iterative solution
2. Recursive solution with even/odd vector buffers (this is what naturally implements the Cooley-Tukey equations)
3. Recursive solution with user-supplied scratchpad buffer

The in-place iterative solution, `ffti_f()`, involves two fundamental operations: the swapping of elements into their sorted even/odd ordering at the 2-point DFTs of the butterfly trellis, and then the traversal of the butterfly trellis by subordinate DFT levels. Key to implementing the element swapping operations is the observation that the even/odd ordering through the butterfly trellis amounts to a bit-reversal operation of the original indices of the input signal sequence. In addition, if one is familiar with the digital logic operations of a synchronous binary counter, one can replicate the operations using C's bit operators, making the bit-reversal sorting operation as efficient as possible. The subsequent DFT evaluation implementation then simply follows the butterfly trellis operations. Along with the main `ffti_f()` driver function, a set of subordinate functions are offered that separately implement the bit-reversal sorting and the butterfly trellis evaluation operations.

The recursive solution is a direct fallout of implementing the Cooley-Tukey solution and, in particular, the Danielson–Lanczos lemma, which re-expresses the DFT into two half-size DFTs. Two recursive implementations are given. The first recursive implementation, `fftr_f()`, allocates even/odd buffers at each subordinate DFT evaluation. While this most easily follows the algorithm layout, it is rather wasteful of memory, especially for large values of N.

The second recursive implementation, `fftrb_f()`, uses the observation that each subordinate DFT level simply needs to preserve its local inputs while it computes its outputs, and that the computed outputs are subequently used at the superordinate levels. Hence, each recursive call merely needs to swap the order of its input and output buffers, thus implementing a commutating buffer mechanism. While still requiring more memory than the in-place iterative solution, it only involves making a duplicate copy of the input signal sequence before invoking the recursive evaluation sequence.

The application executive, `app_exec()`, performs a simple file read of real-valued data points, each point on a separate line, and then evaluates the set of points. If the number of points does not match a power-of-two size, the next lowest power-of-two size is used.

The same functions are used for both forward FFT and the inverse FFT operations. The functions use a `direction` control variable to set the sign of the kernel. However, it is the responsibility of the caller to divide all the values by N when performing an inverse FFT.
