#ifndef KNIGHT_H
#define KNIGHT_H

#include "square.h"
#include<vector>

class Knight final : public Square {
    public:

        Knight(bool isWhite = false): Square(isWhite){
            type = "Knight";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override;

        ~Knight(){};

};

#endif