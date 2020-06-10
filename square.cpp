#include "square.h"

bool Square::isMovePossible(std::vector<Piece> pieces) const {
    for (int i = 0 ; i < (int)pieces.size() - 1; i++){
        if (!pieces[i].type.empty()){
            return false;
        }
    }

    if ((pieces[pieces.size() - 1].isWhite ^ isWhite) || pieces[pieces.size() - 1].type.empty()){
        return true;
    }

    return false;
}; 

bool Square::isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const{
    return true;
};