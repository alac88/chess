#include "pawn.h"
#include <cstdlib>
#include<iostream>

bool Pawn::isMoveValid(std::vector<Piece> pieces, std::vector<int> pos_from, std::vector<int> pos_to) const{

    if ((pos_from[0] == pos_to[0]) && (pos_from[1] == pos_to[1])){
        return false;
    }

    if ((pieces[pieces.size() - 1].type.empty()) || (pieces[pieces.size() - 1].isWhite ^ isWhite)){ //if the final square is empty or occupied by a piece of a different colour
        if (isWhite){
            if (pos_to[0] - pos_from[0] < 0){

                return false;
            }
            if ((pos_to[0] - pos_from[0] == 1) && ((pos_to[1] - pos_from[1] == 1) || (pos_to[1] - pos_from[1] == -1))){ //diagonal
                if (!pieces[pieces.size() - 1].type.empty() && (pieces[pieces.size() - 1].isWhite ^ isWhite)){
                    return true;
                }
            } else if((pos_to[0] - pos_from[0] <= (((pos_from[0] == 1) || (pos_from[0] == 6)) ? 2 : 1) && (pos_from[1] == pos_to[1]))){
                if (pieces[pieces.size() - 1].type.empty()){
                    return isMovePossible(pieces);
                }
            }
        } else {
            if (pos_from[0] - pos_to[0] < 0){
                return false;
            }
            if ((pos_to[0] - pos_from[0] == -1) && ((pos_to[1] - pos_from[1] == 1) || (pos_to[1] - pos_from[1] == -1))){ // diagonal
                if (!pieces[pieces.size() - 1].type.empty() && (pieces[pieces.size() - 1].isWhite ^ isWhite)){
                    return true;
                }
            } else if((pos_from[0] - pos_to[0] <= (((pos_from[0] == 1) || (pos_from[0] == 6)) ? 2 : 1)) && (pos_from[1] == pos_to[1])){
                if (pieces[pieces.size() - 1].type.empty()){
                    return isMovePossible(pieces);
                }
            }
        }

    } 


    return false;
}