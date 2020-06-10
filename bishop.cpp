#include "bishop.h"
#include <cstdlib>

bool Bishop::isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const{

    if ((pos_from[0] == pos_to[0]) && (pos_from[1] == pos_to[1])){
        return false;
    }

    if (abs(pos_from[0] - pos_to[0]) == abs(pos_from[1] - pos_to[1]) ){ //diagonal move
        return isMovePossible(pieces);
    }
    return false;
}