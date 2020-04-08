# MARC: Student version #

In this repository you will find all you need to get started modeling and solving combinatorial problems with the MARC framework and its Java interface JMARC. 

This release is thought for students of the Artificial Intelligence course held by Prof. Mancini (Corso di Laurea Triennale in Informatica @ La Sapienza Università di Roma).

## Setting up ##

### Dependencies ###

* CMake (3.14.2 or newer), <https://cmake.org/download/>
* GCC supporting C++ 17 (Clang might also work, MSVC is likely not to as the framework was developed on, and for, Unix systems)
* JDK (9 or newer) - only needed for JMARC

### Install ###

* Clone or download this repository
* Edit environment variables in `build.sh` to fit your machine configuration
* Run `build.sh` (writing permissions for the working directory are required)
* A `build` directory will be created, containing the following artifacts:
    * `build/marc/libMARC.so` - a shared library containing the compiled MARC code
	* `build/jmarc` - a directory containing the compiled JMARC code
	* `build/jmarc_native/libJMARCNative.so` - a shared library allowing to link the JVM and native MARC code
	
### Test ###

* Edit environment variables in `test.sh` to fit your machine configuration
* Run `test.sh` (writing permissions for the working directory are required)
* If everything went smoothly, you should get the output to the execution of `marc/examples/nqueens/Main.cpp` and `jmarc/examples/NQueens/Main.java`
	
## Running ##

To run a JMARC model, pass the following options to the JVM:

* `-classpath <JMARC_BUILD>`, where `<JMARC_BUILD>` is a directory containing the compiled JMARC code
* `-Djava.library.path=<JMARC_NATIVE_BUILD>`, where <JMARC_NATIVE_BUILD> is a directory containing `libJMARCNative.so`

If you're having trouble with this, I advice you to look into the `test.sh` script: it contains a full example of compilation and execution of both MARC and JMARC models.

## Authors contacts ##

* D. Baieri (<baieri.1746117@studenti.uniroma1.it>) - feel free to e-mail me for any MARC-related question
* Prof. T. Mancini (<tmancini@di.uniroma1.it>)
* Dott. M. Esposito (<esposito@di.uniroma1.it>)