#ifndef CHESS_MAIN_H
#define CHESS_MAIN_H

#include <string>
#include <vector>
#include <iostream>

#include "const.h"
#include "square.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "queen.h"
#include "knight.h"
#include "pawn.h"

class ChessBoard{
    private:
        bool errorHasOccurred = false;
        bool whiteTurn = true;
        bool checkState = false;
        Square* board[BOARD_HEIGHT][BOARD_WIDTH];

        /*************************************/
        /* Graphic interface (not necessary) */
        /*************************************/

        /*  Prints the piece according the its type
            @parameters: - s: square
            @return: output letter or " " if square is empty */
        std::string printPiece(Square* s);

        /*  Prints the board */
        void printBoard();

        /***************/
        /* Check Rules */
        /***************/

        /*  Checks if the player submits a castling
            @parameters: - from: source position
                         - to: destination
            @return: - 0 if no castling
                     - 1 if left casting
                     - 2 if right castling */
        int isCastling(std::vector<int> from, std::vector<int> to);

        /*  Checks if there is a stalemate */
        bool isStalemate();

        /*  Checks if there is a check */
        bool isInCheck();
        
        /*  Checks if there is a checkmate */
        bool isInCheckMate();


        /***********/
        /* Helpers */
        /***********/

        /*  Gets the square at the following position
            @parameters: - position: source position
            @return: Square object corresponding to the square at this position */
        Square* getSquare(std::string position);

        /*  Gets all squares between the source position and the destination
            @parameters: - pos_from: source position
                         - pos_to: destination
            @return: vector containing all the squares between */
        std::vector<Piece> getSquaresBetween(std::vector<int> pos_from, std::vector<int> pos_to);

        /*  Converts a std::string position to a std::vector<int> position
            @parameters: - position: string position
            @return: vector position */
        std::vector<int> parsePosition(std::string position);

        /*  Checks if the following position is valid
            @parameters: - pos: source position
            @return: - false if the possible is not valid
                     - true otherwise */
        bool isPositionValid(std::string pos);

        /*  Checks if the colour of the piece corresponds to the colour of the player who should play
            @parameters: - piece: piece to evaluate
            @return: - false if the colour is not correct
                     - true otherwise */
        bool isCorrectTurn(Square* piece);

        /*  Moves a piece to check whether it leads to a check state, and then cancel the move
            @parameters: - from: source position
                         - to: destination
                         - piece: the piece to evaluate
            @return: - false if the move is not possible
                     - true otherwise */
        bool tryMove(std::vector<int> from, std::vector<int> to, Square* piece);


        /*******************/
        /* Board functions */
        /*******************/
        
        /*  Initializes the board */
        void initBoard();

        /*  Deletes the board */
        void deleteBoard();


    public:

        /* Constructor */
        ChessBoard(){
            initBoard();
            std::cout << "A new chess game is started!" << std::endl;
        };

        /*  Submits a move from position "from" to position "to"
            @parameters: - from: source position
                         - to: destination */
        void submitMove(std::string from, std::string to);
        
        /* Resets the board */
        void resetBoard();

        /* Destructor */
        ~ChessBoard(){
            deleteBoard();
        };
};


#endif