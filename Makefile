OBJS = ChessMain.o ChessBoard.o square.o bishop.o king.o knight.o pawn.o queen.o rook.o

chess: $(OBJS)
		g++ -Wall -g $(OBJS) -o chess

%.o: %.cpp %.h
		g++ -Wall -g -c $< 

clean:
	rm -f *.o chess

.PHONY: clean