TARGET = mazeGenerator
OBJS =  mazeGenerator.o TList.o utils.o


$(TARGET) : $(OBJS)
	@gcc $(OBJS) -o $(TARGET)

mazeGenerator.o : mazeGenerator.c TList.h utils.h 
	@gcc -c mazeGenerator.c

TList.o : TList.c TList.h
	@gcc -c TList.c

utils.o : utils.c utils.h
	@gcc -c utils.c

clean :
	@rm -f *.o
