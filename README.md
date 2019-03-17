# Jupiter 

[![Build Status](https://travis-ci.org/maralonso/jupiter.svg?branch=master)](https://travis-ci.org/maralonso/jupiter)  
[![codecov](https://codecov.io/gh/maralonso/jupiter/branch/master/graph/badge.svg)](https://codecov.io/gh/maralonso/jupiter)  


                            = =
               ........  =    =
             ............   =
            ..............=
            .......... =..
          = ........=.....
        =    ...=........
       =     = ........
       =  =     \..../
                ------
                 |  |
                 |  |
                 |  |
                 |  |
                /    \
              (________)        JUPITER CHESS
   ----------------------------------------------
   
Jupiter is an UCI-compatible chess engine for Linux.

You can use it with any User Interface that support UCI protocol, like:   
    - pychess (http://www.pychess.org/)     
    - scid    (http://scid.sourceforge.net/) 

## Files
    * **engine**: Engine source files
    * **tests**: Engine tests source files
    * config: Engine configuration file.    

## Build and run engine

* make -C engine/
* engine/jupiter

## Build and run tests

* make -C tests/
* tests/jupitests

## Configuration File
You can edit this file to change some options.

### Logging Level
Log level can be DEBUG, INFO or ERROR. It's set to INFO by default.

`LOG_LEVEL = INFO`

### Logging File
By default the engine will log to `./jupiter.log`

`LOG_FILE = jupiter.log`

## Parallel version
### Prerequisites
  * [gcc-7.3+](https://ftp.gnu.org/gnu/gcc/gcc-7.3.0/)

#### Configuration GCC 7.3
```
 export PATH="</path>/gcc/bin:$PATH"
 export LD_LIBRARY_PATH="</path>/gcc/lib64:$LD_LIBRARY_PATH"
 export LD_RUN_PATH="</path>/gcc/lib64:$LD_RUN_PATH"
 cd </path>gcc/bin/
 ln -s ./gcc cc 
 export CC="</path>/gcc/bin/gcc"
```
### Built
#### Debug
```
cd </path>jupiter/
cmake -DCMAKE_BUILD_TYPE=Debug .
make
```

#### Release
```
cd </path>jupiter/
cmake -DCMAKE_BUILD_TYPE=Release .
make
```