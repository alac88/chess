#ifndef BISHOP_H
#define BISHOP_H

#include "square.h"
#include<vector>

class Bishop final : public Square {
    public:

        Bishop(bool isWhite = false): Square(isWhite){
            type = "Bishop";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override;

        ~Bishop(){};

};

#endif