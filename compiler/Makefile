CC = gcc
CFLAGS = -Wall -g
LEX = flex
YACC = bison
YFLAGS = -d -v

TARGET = phpcompiler

all: $(TARGET)

$(TARGET): php.y php.l tabsim.c tabsim.h
	@echo "Compilando analizador sintáctico..."
	$(YACC) $(YFLAGS) php.y
	@echo "Compilando analizador léxico..."
	$(LEX) php.l
	@echo "Enlazando compilador..."
	$(CC) $(CFLAGS) -o $(TARGET) php.tab.c lex.yy.c -lfl
	@echo "Compilación exitosa!"

clean:
	rm -f $(TARGET) *.o php.tab.c php.tab.h y.tab.c y.tab.h lex.yy.c y.output php.output output.c

run: $(TARGET)
	./$(TARGET)

test: $(TARGET)
	./$(TARGET) test.php

.PHONY: all clean run test
