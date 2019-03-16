EXEC    = jupiter
GPFLAG = -pg
#OPTFLAG = -O3 -mno-avx -march=native
CFLAGS  = $(OPTFLAG) $(GPFLAG) -c -std=c99 -Wall -fopenmp
#DBCFLAGS  = $(OPTFLAG) $(GPFLAG) -c -g -fPIC -std=c99 -Wall -lgcov --coverage -fopenmp
LDFLAGS = $(OPTFLAG) $(GPFLAG) -fopenmp
#DBLDFLAGS = $(OPTFLAG) $(GPFLAG) -lgcov --coverage -fopenmp

CSOURCES = $(wildcard *.c) $(wildcard pieces/*.c)

VPATH = pieces

COBJECTS = $(CSOURCES:.c=.o)               

INCLUDES = -I ./ -I pieces/include

LIBS = 

all: $(CSOURCES) $(EXEC) 

#debug:
#	@$(MAKE) CFLAGS="$(DBCFLAGS)" LDFLAGS="$(DBLDFLAGS)"


$(EXEC): $(COBJECTS)
	$(CC) $(COBJECTS) $(LDFLAGS) -o $@
	rm -rf *.o
	@echo ''
	@echo 'Finished building target $@'

%.o: %.c
		$(CC) $(INCLUDES) $(CFLAGS) $< -o $@

clean:
		rm -rf *.o
		rm -rf pieces/*.o
		rm -rf $(EXEC)
