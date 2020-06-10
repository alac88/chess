#include"ChessBoard.h"

#include<iostream>
#include<vector>
#include<assert.h>

using namespace std;

std::string ChessBoard::printPiece(Square* s){
    if (s->type.empty()){
        return " ";
    } else if (s->type=="King"){
        return "K";
    } else if (s->type=="Queen"){
        return "Q";
    } else if (s->type=="Rook"){
        return "R";
    } else if (s->type=="Bishop"){
        return "B";
    } else if (s->type=="Knight"){
        return "k";
    } else if (s->type=="Pawn"){
        return "P";
    } else {
        return "P";
    }
}

Square* ChessBoard::getSquare(std::string position){
    std::vector<int> pos = parsePosition(position);
    return board[pos[0]][pos[1]];
}

void ChessBoard::printBoard(){
    cout << '\n' << "                Black's" << '\n';
    cout << '\n' << "    ";
    for (int letter = ASCII_LETTER_A ; letter < ASCII_LETTER_I ; letter++){
        cout << "  " << (char)letter << " ";
    }
    cout << '\n' << "    +---+---+---+---+---+---+---+---+" << '\n';
    for (int line = BOARD_HEIGHT - 1 ; line >= 0 ; line--){
        cout << "  " << line+1 << " |" ;
        for (int column = 0 ; column < BOARD_WIDTH ; column++){
            cout << " " << printPiece(board[line][column]) << " " << "|";
        }   
        cout << " " << line+1;
        cout << '\n' << "    +---+---+---+---+---+---+---+---+" << '\n';
    }
    cout << '\n' << "    ";
    for (int letter = ASCII_LETTER_A ; letter < ASCII_LETTER_I ; letter++){
        cout << "  " << (char)letter << " ";
    }

    cout << '\n' << '\n' << "                White's" << '\n';
}

std::vector<int> ChessBoard::parsePosition(std::string position){
    std::vector<int> pos;
    if (position.length() != 2){ // if position is different than 2 characters
        pos.push_back(-1);
    } else {
        pos.push_back((int)(position.substr(1,1).at(0)) - ASCII_NUMBER_1);
        pos.push_back((int)(position.substr(0,1).at(0)) - ASCII_LETTER_A);
    }
    return pos;
}

bool ChessBoard::isPositionValid(std::string pos){
    std::vector<int> position = parsePosition(pos);
    if (position[0] == -1){
        return false;
    }
    if ((position[0] < 0) || (position[0] > BOARD_HEIGHT - 1) || (position[1] < 0) || (position[1] > BOARD_WIDTH - 1)){
        cerr << "Error: invalid position" << endl;
        return false;
    }
    return true;
}

bool ChessBoard::isCorrectTurn(Square* piece){
    return piece->isWhite ^ whiteTurn ? false : true;
}

std::vector<Piece> ChessBoard::getSquaresBetween(std::vector<int> pos_from, std::vector<int> pos_to){
    std::vector<Piece> pieces;
    if (pos_from[0] == pos_to[0]){ // row move
        int dir = (pos_from[1] - pos_to[1] < 0) ? 1 : -1;
        for (int i = pos_from[1] + (1 * dir) ; i != pos_to[1] ; i = i + (1 * dir)){
            pieces.push_back({board[pos_from[0]][i]->isWhite, board[pos_from[0]][i]->type});
        }
        pieces.push_back({board[pos_to[0]][pos_to[1]]->isWhite, board[pos_to[0]][pos_to[1]]->type});
    } else if (pos_from[1] == pos_to[1]){ // column move
        int dir = (pos_from[0] - pos_to[0] < 0) ? 1 : -1;
        for (int i = pos_from[0] + (1 * dir) ; i != pos_to[0] ; i = i + (1 * dir)){
            pieces.push_back({board[i][pos_from[1]]->isWhite, board[i][pos_from[1]]->type});
        }
        pieces.push_back({board[pos_to[0]][pos_to[1]]->isWhite, board[pos_to[0]][pos_to[1]]->type});
    } else if (abs(pos_from[0] - pos_to[0]) == abs(pos_from[1] - pos_to[1])){ // diagonal move
        int dir_row = (pos_from[0] - pos_to[0] < 0) ? 1 : -1;
        int dir_column = (pos_from[1] - pos_to[1] < 0) ? 1 : -1;
        for (int i = 1 ; i <= abs(pos_from[0] - pos_to[0]) ; i++){
            pieces.push_back({board[pos_from[0] + (i * dir_row)][pos_from[1] + (i * dir_column)]->isWhite, board[pos_from[0] + (i * dir_row)][pos_from[1] + (i * dir_column)]->type});
        }
    } else { // knight move
        pieces.push_back({board[pos_to[0]][pos_to[1]]->isWhite, board[pos_to[0]][pos_to[1]]->type});
    }

    return pieces;

}

bool ChessBoard::tryMove(std::vector<int> from, std::vector<int> to, Square* piece){
    Square* tmp = board[to[0]][to[1]];
    board[to[0]][to[1]] = piece; //move to a new position
    board[from[0]][from[1]] = new Square(); 
    whiteTurn = !whiteTurn; //change turn
    if (isInCheck()){ // if it leads to a check state
        delete board[from[0]][from[1]];
        board[from[0]][from[1]] = piece; // cancel move
        board[to[0]][to[1]] = tmp; // cancel move
        whiteTurn = !whiteTurn; //change turn
        return false;
    }
    delete board[from[0]][from[1]];
    board[from[0]][from[1]] = piece; // cancel move
    board[to[0]][to[1]] = tmp; // cancel move
    whiteTurn = !whiteTurn; //change turn
    return true;
}


bool ChessBoard::isInCheckMate(){

    Square* king;
    std::vector<int> pos_king(2);
    std::vector<int> pos_from_attacker(2);
    std::vector<int> pos_to(2);
    std::vector<int> pos_from_piece(2);
    std::vector<int> pos_to_piece(2);
    std::vector<std::vector<int>> checkPieces;

    //find the king
    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
        for (int column = 0 ; column < BOARD_WIDTH ; column++){
            if ((board[line][column]->type == "King") && (!isCorrectTurn(board[line][column]) ^ checkState )){
                pos_king[0] = line;
                pos_king[1] = column;
                king = board[line][column];
            }
        }   
    }

    if (king->type == "King"){ //if the king has been found (extra security)
        // for all pieces
        for (int line = 0 ; line < BOARD_HEIGHT ; line++){
            for (int column = 0 ; column < BOARD_WIDTH ; column++){

                if (!board[line][column]->type.empty() && (board[line][column]->type != "King")){ //if the square contains a piece which is not the king
                    pos_from_attacker[0] = line;
                    pos_from_attacker[1] = column;

                    if ((board[line][column]->isMoveValid(getSquaresBetween(pos_from_attacker, pos_king), pos_from_attacker, pos_king)) && (board[line][column]->isWhite ^ king->isWhite)){ //if the piece can take the king

                        checkPieces.push_back(pos_from_attacker);
                    }
                }
            }   
        }
    }
    
    if (checkPieces.size() > 0){
        
        // king move
        for (int line = -1 ; line < 2 ; line++){
            for (int column = -1 ; column < 2 ; column++){
                if ((line != 0) || (column != 0)){ // if not moving to its own position
                    pos_to[0] = pos_king[0] + line;
                    pos_to[1] = pos_king[1] + column;
                    if ((pos_to[0] >= 0) && (pos_to[0] < BOARD_HEIGHT) && (pos_to[1] >= 0) && (pos_to[1] < BOARD_WIDTH)){
                        if (king->isMoveValid(getSquaresBetween(pos_king, pos_to), pos_king, pos_to)){
                            if (tryMove(pos_king, pos_to, king)){
                                return false;
                            }
                        }
                    }
                }
            }   
        }

        if (checkPieces.size() == 1){


            // if a piece can kill the attacker
            for (int line = 0 ; line < BOARD_HEIGHT ; line++){
                for (int column = 0 ; column < BOARD_WIDTH ; column++){
                    pos_from_piece[0] = line;
                    pos_from_piece[1] = column;
                    if ((line != checkPieces[0][0]) && (column != checkPieces[0][1])){ // if the piece is not the attacker itself
                        if (!board[line][column]->type.empty() && board[line][column]->isMoveValid(getSquaresBetween(pos_from_piece, checkPieces[0]), pos_from_piece, checkPieces[0]) ){
                            if (tryMove(pos_from_piece, checkPieces[0], board[line][column])){
                                return false;
                            }
                        }
                    }
                }
            }

            // if a piece can protect him (row or diagonal interception)

            if (checkPieces[0][0] == pos_king[0]){ //same row
                for (int rank = (checkPieces[0][1] < pos_king[1] ? checkPieces[0][1] : pos_king[1]) ; rank < (checkPieces[0][1] < pos_king[1] ? pos_king[1] : checkPieces[0][1]) ; rank++){
                    pos_to_piece[0] = pos_king[0];
                    pos_to_piece[1] = rank;
                    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
                        for (int column = 0 ; column < BOARD_WIDTH ; column++){
                            pos_from_piece[0] = line;
                            pos_from_piece[1] = column;
                            if ((line != pos_to_piece[0]) && (column != pos_to_piece[1]) && !((line == pos_king[0]) && (column == pos_king[1]))){
                                if (!board[line][column]->type.empty() && board[line][column]->isMoveValid(getSquaresBetween(pos_from_piece, pos_to_piece), pos_from_piece, pos_to_piece) && isCorrectTurn(board[line][column])){
                                    if (tryMove(pos_from_piece, pos_to_piece, board[line][column])){
                                        return false;
                                    }
                                }
                            }
                        }
                    }

                }
            } else if (checkPieces[0][1] == pos_king[1]){ //same column
                for (int row =(checkPieces[0][0] < pos_king[0] ? checkPieces[0][0] : pos_king[0]) ; row < (checkPieces[0][0] < pos_king[0] ? pos_king[0] : checkPieces[0][0]) ; row++){
                    pos_to_piece[0] = row;
                    pos_to_piece[1] = pos_king[1];
                    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
                        for (int column = 0 ; column < BOARD_WIDTH ; column++){
                            pos_from_piece[0] = line;
                            pos_from_piece[1] = column;
                            if ((line != pos_to_piece[0]) && (column != pos_to_piece[1]) && !((line == pos_king[0]) && (column == pos_king[1]))){
                                if (!board[line][column]->type.empty() && board[line][column]->isMoveValid(getSquaresBetween(pos_from_piece, pos_to_piece), pos_from_piece, pos_to_piece) && isCorrectTurn(board[line][column])){
                                    if (tryMove(pos_from_piece, pos_to_piece, board[line][column])){
                                        return false;
                                    }
                                }
                            }
                        }
                    }

                }
            } else { //same diagonal
                int dir_row = (checkPieces[0][0] - pos_king[0] < 0) ? 1 : -1;
                int dir_column = (checkPieces[0][1] - pos_king[1] < 0) ? 1 : -1;
                for (int i = 1 ; i < abs(checkPieces[0][0] - pos_king[0]) ; i++){
                    pos_to_piece[0] = checkPieces[0][0] + (i * dir_row);
                    pos_to_piece[1] = checkPieces[0][1] + (i * dir_column);
                    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
                        for (int column = 0 ; column < BOARD_WIDTH ; column++){
                            pos_from_piece[0] = line;
                            pos_from_piece[1] = column;
                            if ((line != pos_to_piece[0]) && (column != pos_to_piece[1]) && !((line == pos_king[0]) && (column == pos_king[1]))){
                                if (!board[line][column]->type.empty() && board[line][column]->isMoveValid(getSquaresBetween(pos_from_piece, pos_to_piece), pos_from_piece, pos_to_piece) && isCorrectTurn(board[line][column])){
                                    if (tryMove(pos_from_piece, pos_to_piece, board[line][column])){
                                        return false;
                                    }
                                }
                            }
                        }
                    }

                }
            }
        }

    }   

    return true;
}

bool ChessBoard::isInCheck(){
    
    std::vector<Square*> kings(2);
    std::vector<int> pos_from(2);
    std::vector<int> pos_king_white(2);
    std::vector<int> pos_king_black(2);

    //find the king
    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
        for (int column = 0 ; column < BOARD_WIDTH ; column++){
            if (board[line][column]->type == "King"){
                if (board[line][column]->isWhite){
                    kings[0] = board[line][column];
                    pos_king_white[0] = line;
                    pos_king_white[1] = column;
                } else {
                    kings[1] = board[line][column];
                    pos_king_black[0] = line;
                    pos_king_black[1] = column;
                }
            }
        }   
    }

    if ((kings[0]->type == "King") && (kings[1]->type == "King")){ //if the kings have been found (extra security)
        // for all pieces
        for (int line = 0 ; line < BOARD_HEIGHT ; line++){
            for (int column = 0 ; column < BOARD_WIDTH ; column++){
                if (!board[line][column]->type.empty() && (board[line][column]->type != "King")){ //if the square contains a piece which is not the king
                    pos_from[0] = line;
                    pos_from[1] = column;

                    if (board[line][column]->isMoveValid(getSquaresBetween(pos_from, pos_king_white), pos_from, pos_king_white)){ //if the piece can take the white king
                        if (!whiteTurn){ //if our move leads to a check of our own king
                            checkState = true;
                        }
                        return true;
                    } else if (board[line][column]->isMoveValid(getSquaresBetween(pos_from, pos_king_black), pos_from, pos_king_black)){ //if the piece can take the black king
                        if (whiteTurn){ //if our move leads to a check of our own king
                            checkState = true;
                        }
                        return true;
                    }
                }
            }   
        }
    }


    return false;
}

int ChessBoard::isCastling(std::vector<int> from, std::vector<int> to){
    std::vector<int> pos_to(2);
    if ((board[from[0]][from[1]]->type == "King") && (board[to[0]][to[1]]->type.empty())){

        int row = board[from[0]][from[1]]->isWhite ? 0 : BOARD_HEIGHT - 1;

        if ((from[0] == row) && (from[1] == 4) && (to[0] == row)){ // white castling
            if (to[1] == 2){ // left
                if (!board[from[0]][from[1]]->hasAlreadyMoved && !board[from[0]][to[1]]->hasAlreadyMoved){ // for castling
                    for (int i = 1 ; i < 4 ; i++){
                        if (!board[row][i]->type.empty()){
                            return 0;
                        }
                        pos_to[0] = row;
                        pos_to[1] = i;
                        if (!tryMove(from, pos_to, board[from[0]][from[1]])){
                            return 0;
                        }
                    }
                    cout << (row ? "Black's" : "White's") << " left castling" << endl;
                    return 1;
                } else {
                    cout << "Impossible castling: pieces have already been moved previously" << endl;
                    return 0;
                }
            } else if (to[1] == 6){ // right
                if (!board[from[0]][from[1]]->hasAlreadyMoved && !board[from[0]][to[1]]->hasAlreadyMoved){ // for castling
                    for (int i = 5 ; i < BOARD_WIDTH - 1 ; i++){
                        if (!board[row][i]->type.empty()){
                            return 0;
                        }
                        pos_to[0] = row;
                        pos_to[1] = i;
                        if (!tryMove(from, pos_to, board[from[0]][from[1]])){
                            return 0;
                        }
                    }
                    cout << (row ? "Black's" : "White's") << " right castling" << endl;
                    return 2;
                } else {
                    cout << "Impossible castling: pieces have already been moved previously" << endl;
                    return 0;
                }
            }
        } 
    }
    
    return 0;
}

bool ChessBoard::isStalemate(){
    if (isInCheck()){
        return false;
    } else {
        std::vector<int> pos_from(2);
        std::vector<int> pos_to(2);
        for (int line_piece = 0 ; line_piece < BOARD_HEIGHT ; line_piece++){
            for (int column_piece = 0 ; column_piece < BOARD_WIDTH ; column_piece++){
                if (!board[line_piece][column_piece]->type.empty()){
                    pos_from[0] = line_piece;
                    pos_from[1] = column_piece;
                    for (int line_to = 0 ; line_to < BOARD_HEIGHT ; line_to++){
                        for (int column_to = 0 ; column_to < BOARD_WIDTH ; column_to++){
                            if (!((line_piece == line_to) && (column_piece == column_to))){ // if not moving to its own position
                                pos_to[0] = line_to;
                                pos_to[1] = column_to;
                                if (!board[line_piece][column_piece]->type.empty() && isCorrectTurn(board[line_piece][column_piece]) && board[line_piece][column_piece]->isMoveValid(getSquaresBetween(pos_from, pos_to), pos_from, pos_to)){
                                    if (tryMove(pos_from, pos_to, board[line_piece][column_piece])){ // if moving the piece does not lead to a check
                                        return false;
                                    }
                                }
                            }
                        }   
                    }
                }
            }   
        }

    }
    return true;
}

void ChessBoard::submitMove(std::string from, std::string to){

    int isCastlingCase = 0;

    if (isPositionValid(from) && isPositionValid(to)){
        Square* square = getSquare(from);
        if (!square->type.empty()){
                if (isCorrectTurn(square)){
                std::vector<int> pos_from = parsePosition(from);
                std::vector<int> pos_to = parsePosition(to);
                isCastlingCase = isCastling(pos_from, pos_to);

                if (isCastlingCase){
                    delete board[pos_to[0]][pos_to[1]];
                    board[pos_to[0]][pos_to[1]] = square; // move king
                    board[pos_from[0]][pos_from[1]] = new Square(); // delete previous king position
                    switch(isCastlingCase){
                        case 1: // left castling
                            delete board[pos_from[0]][3];
                            board[pos_from[0]][3] = board[pos_from[0]][0];
                            delete board[pos_from[0]][0];
                            board[pos_from[0]][0] = new Square();
                            break;
                        case 2: // right castling
                            delete board[pos_from[0]][5];
                            board[pos_from[0]][5] = board[pos_from[0]][BOARD_WIDTH - 1];
                            board[pos_from[0]][BOARD_WIDTH - 1] = new Square();
                            break;
                    }
                    whiteTurn = !whiteTurn; //change turn

                    cout << (square->isWhite ? "White's " : "Black's ") << square->type << " moves from " << from << " to " << to;

                } else if (square->isMoveValid(getSquaresBetween(pos_from, pos_to), pos_from, pos_to)){ //if the move is valid
                    
                        Square tmp = *board[pos_to[0]][pos_to[1]];
                        if ((square->type == "King") || (square->type == "Rook")){ // for castling
                            square->hasAlreadyMoved = true;
                        }

                        cout << (square->isWhite ? "White's " : "Black's ") << square->type << " moves from " << from << " to " << to;
                        if (!(tmp.type.empty()) && (tmp.isWhite ^ square->isWhite)){
                            cout << " taking " << (tmp.isWhite ? "White's " : "Black's ") << tmp.type;
                        }
                        delete board[pos_to[0]][pos_to[1]];
                        board[pos_to[0]][pos_to[1]] = square; //move to a new position
                        board[pos_from[0]][pos_from[1]] = new Square(); 
                        whiteTurn = !whiteTurn; //change turn

                        cout << endl;

                        if (isInCheck()){
                            if (checkState){
                                cout << "Error: impossible move, " << (square->isWhite ? "White" : "Black") << " is in check: previous move cancelled" << endl;
                                *board[pos_to[0]][pos_to[1]] = tmp; // cancel move
                                delete board[pos_from[0]][pos_from[1]];
                                board[pos_from[0]][pos_from[1]] = square; // cancel move
                                whiteTurn = !whiteTurn; //change turn
                                if ((square->type == "King") || (square->type == "Rook")){ // for castling
                                    square->hasAlreadyMoved = false;
                                }
                            } else {
                                checkState = true;
                                cout << (square->isWhite ? "Black" : "White") << " is in check" << (isInCheckMate() ? "mate" : "") << endl;
                            }
                        } else {
                            checkState = false;
                        }

                } else { //if the move is not valid
                    cerr << (square->isWhite ? "White's " : "Black's ") << square->type << " cannot move to " << to << "!" << endl;                
                }
            } else {
                cerr << "It is not " << (whiteTurn ? "Black's" : "White's") << " turn to move!" << endl;
                return;
            }
        } else {
            cerr << "There is no piece at position " << from << "!" << endl;
            return;
        }
    } else {
        return;
    }
    if (isStalemate()){
        cout << "Stalemate!" << endl;
        return;
    }
}

void ChessBoard::initBoard(){

    for (int line = 2 ; line < BOARD_HEIGHT - 2 ; line++){
        for (int column = 0 ; column < BOARD_WIDTH ; column++){
            board[line][column] = new Square();
        }   
    }

    board[0][0] = new Rook(true);
    board[0][1] = new Knight(true);
    board[0][2] = new Bishop(true);
    board[0][3] = new Queen(true);
    board[0][4] = new King(true);
    board[0][5] = new Bishop(true);
    board[0][6] = new Knight(true);
    board[0][BOARD_WIDTH - 1] = new Rook(true);

    for (int i = 0 ; i < BOARD_HEIGHT ; i++){
        board[1][i] = new Pawn(true);
        board[6][i] = new Pawn();
    }

    board[BOARD_HEIGHT - 1][0] = new Rook();
    board[BOARD_HEIGHT - 1][1] = new Knight();
    board[BOARD_HEIGHT - 1][2] = new Bishop();
    board[BOARD_HEIGHT - 1][3] = new Queen();
    board[BOARD_HEIGHT - 1][4] = new King();
    board[BOARD_HEIGHT - 1][5] = new Bishop();
    board[BOARD_HEIGHT - 1][6] = new Knight();
    board[BOARD_HEIGHT - 1][BOARD_WIDTH - 1] = new Rook();

    whiteTurn = true;

}

void ChessBoard::deleteBoard(){
    for (int line = 0 ; line < BOARD_HEIGHT ; line++){
        for (int column = 0 ; column < BOARD_WIDTH ; column++){
            delete board[line][column];
            board[line][column] = nullptr;
        }
    }
}

void ChessBoard::resetBoard(){
    deleteBoard();
    initBoard();
}