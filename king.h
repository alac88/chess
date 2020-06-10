#ifndef KING_H
#define KING_H

#include "square.h"
#include<vector>

class King final : public Square {
    public:

        King(bool isWhite = false): Square(isWhite){
            type = "King";
        };

        bool isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const override;

        ~King(){};

};

#endif