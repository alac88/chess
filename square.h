#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string>
#include <vector>

struct Piece {
    bool isWhite = false;
    std::string type;
};

class Square {
    public:
        bool hasAlreadyMoved = false;
        std::string type;
        bool isWhite;

        Square(bool isWhite = false): isWhite(isWhite){};

        /*  Checks if the move is possible (if the is any piece between the source position and the destination, or if the colour of the piece at the destination is the same as the piece at the source position)
            @parameters: - pieces: vector containing all the squares between
            @return: - false if the move is not possible
                     - true otherwise */
        bool isMovePossible(std::vector<Piece> pieces) const;
        
        /*  Checks if the move is valid (according to the rule of each piece)
            @parameters: - pieces: vector containing all the squares between
                         - pos_from: source position
                         - pos_to: destination
            @return: - false if the move is not possible
                     - true otherwise  */
        virtual bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const;

        virtual ~Square() {};

};

#endif