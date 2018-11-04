Target =  OurToma

#source file
SRCS = TomasuloSimulator.c ./Global/Utils/PrintUtility.c ./CacheEmulator/EmulateCache.c ./CPU/CPU.c YDai1015.c GetParm1014.c JLiu1015.c

# *.o file (compile file)
#OBJS = TomasuloSimulator.o ./Global/Utils/PrintUtility.o ./CacheEmulator/EmulateCache.o ./CPU/CPU.o
OBJS = $(SRCS:.c=.o)
OBJSToma = TomasuloSimulator.o
#OBJSPrint = ./Global/Utils/PrintUtility.o
#OBJSCache = ./CacheEmulator/EmulateCache.o
#OBJSCPU = ./CPU/CPU.o

#partial *.h (partial head file besides Toma.h)
HEAD = ./Global/ADT/Dictionary.h ./Global/ADT/CircularQueue.h ./Global/DataTypes.h ./Global/ADT/DictionaryRSRow.h ./Global/ADT/DictionaryRegsRow.h ./Global/ADT/DictionaryBTB.h ././Global/ADT/CircularQueueROB.h ./Global/ADT/OtherRelated.h

$(Target): $(OBJS)
	@echo "transfer" $(OBJS) "into" $(Target)
	gcc -g -o $@ $^

TomasuloSimulator.o: TomasuloSimulator.c ./Global/TomasuloSimulator.h
	@echo "transfer TomasuloSimulator.c1 into" $(OBJSToma)
	gcc -g -c $<
	gcc -g -c -o Global/Utils/PrintUtility.o Global/Utils/PrintUtility.c
	gcc -g -c -o CacheEmulator/EmulateCache.o CacheEmulator/EmulateCache.c
	gcc -g -c -o CPU/CPU.o CPU/CPU.c
	gcc -g -c -o YDai1015.o YDai1015.c
	gcc -g -c -o GetParm1014.o GetParm1014.c
	gcc -g -c -o JLiu1015.o JLiu1015.c

#PrintUtility.o: ./Global/Utils/PrintUtility.c $(HEAD)
#	@echo "transfer PrintUtility.c" into $(OBJSPrint)
#	gcc -c $<

#EmulateCache.o: ./CacheEmulator/EmulateCache.c $(HEAD)
#	@echo "transfer EmulateCache.c into" $(OBJSCache)
#	gcc -c $<

#CPU.o: ./CPU/CPU.c $(HEAD)
#	@echo "transfer CPU.c into" $(OBJSCPU)
#	gcc -c $<

clean:
	rm -rf $(Target) 
	find . -name "*.o"  | xargs rm -f
