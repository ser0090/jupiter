cmake_minimum_required(VERSION 3.10)
project(jupiter C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS}  -fopenmp")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}  -fopenmp")
# -O3 -mno-avx -march=native
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -fopenmp")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -fopenmp")

include_directories(engine)
include_directories(engine/pieces/include)
# include_directories(tests/cu)
# include_directories(tests/cu/testsuites)
# include_directories(tests/include)

add_executable(jupiter
        engine/pieces/include/pieces.h
        engine/pieces/bishop.c
        engine/pieces/king.c
        engine/pieces/knight.c
        engine/pieces/pawn.c
        engine/pieces/pieces.c
        engine/pieces/queen.c
        engine/pieces/rook.c
        engine/board.h
        engine/config.c
        engine/config.h
        engine/delay.c
        engine/delay.h
        engine/engine.c
        engine/engine.h
        engine/evaluation.c
        engine/evaluation.h
        engine/fen.c
        engine/fen.h
        engine/generation.c
        engine/generation.h
        engine/logging.c
        engine/logging.h
        engine/main.c
        engine/node.c
        engine/node.h
        engine/notation.c
        engine/notation.h
        engine/search.c
        engine/search.h
        engine/uci.c
        engine/uci.h)
