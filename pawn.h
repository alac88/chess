#ifndef PAWN_H
#define PAWN_H

#include "square.h"
#include<vector>

class Pawn final : public Square {
    public:

        Pawn(bool isWhite = false): Square(isWhite){
            type = "Pawn";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override;

        ~Pawn(){};
};

#endif