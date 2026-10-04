CC = gcc
CFLAGS = -std=c11 -02 -Wall -Wextra
LDLIBS = -lm
TARGET = gauss_row
OBJS = main.o matr.o form.o Gau.o
.PHONY: all clean
all: $(TARGET)
$(TARGET): $(OBJS)
$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
main.o: main.c matr.h Gau.h
$(CC) $(CFLAGS) -c $< -o $@
matr.o: matr.c matr.h form.h
$(CC) $(CFLAGS) -c $< -o $@
form.o: form.c form.h
$(CC) $(CFLAGS) -c $< -o $@
Gau.o: Gau.c Gau.h
$(CC) $(CFLAGS) -c $< -o $@
clean:
rm -f *.o $(TARGET)
