#ifndef QUEEN_H
#define QUEEN_H

#include "square.h"
#include<vector>

class Queen final : public Square {
    public:

        Queen(bool isWhite = false): Square(isWhite){
            type = "Queen";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override; 

        ~Queen(){};
};

#endif