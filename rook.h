#ifndef ROOK_H
#define ROOK_H

#include "square.h"
#include<vector>

class Rook final : public Square {
    public:

        Rook(bool isWhite = false): Square(isWhite){
            type = "Rook";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override;


        ~Rook(){};

};

#endif