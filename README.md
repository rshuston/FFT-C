# FFT - The Fast Fourier Transform

This project illustrates how to successfully test-drive an algorithm-based software solution that employs techniques from electrical engineering and signal processing.

The objective is to implement an FFT library in C that performs a radix-2 decimation-in-time FFT of a signal. The bit-reversal operations need to be lean, and the FFT evaluation loops need to be efficient for general use.

The baseline development environment is as follows:
* The code is written in ANSI C.
* The code builds and runs on Unix, Linux, or MinGW.
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

## Project Building and Running

To build the `runner.exe` program and use it to analyze data vectors:

```
make
./runner.exe unit-pulse.txt
```

## Key Makefile Targets

The following are the key makefile targets. Run `make help` for a full list.

### default

The `default` target builds the `runner.exe` command-line application that allows the user to analyze data vectors.

### alltests

The `tests` target builds all of the unit tests.

### runalltests

The `runtests` runs all of the unit tests, building them if necessary.

### clean

The `clean` target removes intermediate files (e.g., object files) but preserves the executable build files.

### clobber

The `clobber` target removes all build files and intermediate files.

### help

The `help` target lists all of the makefile targets.

## Using Docker

This project contains a `Dockerfile` that can be used to generate a Debian 12 Docker image suitable for building and running the project.
The image installs the necessary tech stack and sets up a `frodo` user. For more information about Docker, consult the Docker website:

https://www.docker.com

### Building a Docker Image

To generate a Docker image using the specifications and commands from the `Dockerfile`, use the `docker build` command. The following command will build a Docker image named `bag-end`:
```
docker build -t bag-end .
```

Note the `.` at the end of the command; this designates Docker's `build` PATH to be the current working directory.

### Using a Docker Image

To create and then run a container based on an existing Docker image, use the `docker run` command. The following command creates and runs a new container using the `bag-end` image, mounts the current working directory as `host_share` in the `frodo` home directory, and then allocates an interactive TTY session:
```
docker run -it -v "$(pwd)":/home/frodo/host_share bag-end
```
__Note:__ For a "__Git for Windows__" Bash shell session (i.e., the MinGW environment), add a preceding slash `/` to the `"$(pwd")` command:
```
docker run -it -v /"$(pwd)":/home/frodo/host_share bag-end
```

Within the container TTY session, you can run any of the build and test commands, e.g.:
```
cd host_share
make
./runner.exe unit-pulse.txt
make alltests
make runalltests
```

By default, Docker will automatically create a name for the container. However, you can give it a name of your choosing using the `--name` option. The following command creates and runs a new container named `quest` using the `bag-end` image, mounts the current working directory as `host_share` in the `frodo` home directory, and then allocates an interactive TTY session:
```
docker run --name quest -it -v "$(pwd)":/home/frodo/host_share bag-end
```
__Note:__ For a "__Git for Windows__" Bash shell session (i.e., the MinGW environment), add a preceding slash `/` to the `"$(pwd")` command:
```
docker run --name quest -it -v /"$(pwd)":/home/frodo/host_share bag-end
```

Typing `exit` in a running Docker container session will exit the session and stop the container.

To resume running an existing container (e.g., you exited a previous `docker run` session and want to re-use the same container), use the `docker start` command. The following command starts and attaches to an existing container named `quest`, along with an interactive TTY session:
```
docker start -ai quest
```

### Managing Docker Containers and Images

Use the `docker ps -a` command to list all your containers, both running and stopped.

Use the `docker images` command to list all your images.

To remove (purge) an existing container whose session has been exited (stopped), use the `docker rm` command. The following command removes the container named `quest`:
```
docker rm quest
```

To remove (purge) a Docker image, use the `docker rmi` command. The following command removes the image named `bag-end`:
```
docker rmi bag-end
```
