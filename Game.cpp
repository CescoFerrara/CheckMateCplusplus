

#include <cassert>
#include "Game.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Game::Game() : is_white_turn(true) {
    // Add the pawns
    for (int i = 0; i < 8; i++) {
      board.add_piece(std::pair<char, char>('A' + i, '1' + 1), 'P');
      board.add_piece(std::pair<char, char>('A' + i, '1' + 6), 'p');
    }

    // Add the rooks
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+0 ) , 'R' );
    board.add_piece(std::pair<char, char>( 'A'+0 , '1'+7 ) , 'r' );
    board.add_piece(std::pair<char, char>( 'A'+7 , '1'+7 ) , 'r' );

    // Add the knights
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+0 ) , 'N' );
    board.add_piece(std::pair<char, char>( 'A'+1 , '1'+7 ) , 'n' );
    board.add_piece(std::pair<char, char>( 'A'+6 , '1'+7 ) , 'n' );

    // Add the bishops
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+0 ) , 'B' );
    board.add_piece(std::pair<char, char>( 'A'+2 , '1'+7 ) , 'b' );
    board.add_piece(std::pair<char, char>( 'A'+5 , '1'+7 ) , 'b' );

    // Add the kings and queens
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+0 ) , 'Q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+0 ) , 'K' );
    board.add_piece(std::pair<char, char>( 'A'+3 , '1'+7 ) , 'q' );
    board.add_piece(std::pair<char, char>( 'A'+4 , '1'+7 ) , 'k' );
  }

  void Game::add_pieceToBoard(std::pair<char, char> pos, char des) {
    board.add_piece(pos, des);
  }

  void Game::delPcBoard(std::pair<char, char> position) {
    board.deletePc(position);
  }
  
  void Game::clear_GameBoard() {
    board.clear_board();
  }

  Game::Game(const Game& rhs) {
    is_white_turn = rhs.is_white_turn;
    Board brd = rhs.get_board();
    //iterate through board and copy pieces
    for(char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
	std::pair<char, char> start;
	start.first = c;
	start.second = r;
	const Piece* targetPc = brd(start); 
	if (targetPc != nullptr) {
	  board.add_piece(start, targetPc->to_ascii());
	}
      }
    }
  }
  
  void Game::make_move(std::pair<char, char> start, std::pair<char, char> end) {
    char startCol = start.first; //column specified before row in format A1 - H8
    char startRow = start.second;
    char endCol = end.first;
    char endRow = end.second;
    //check if either position is out of board
    if (startCol < 'A' || startCol > 'H' || startRow < '1' || startRow > '8') {
      //Throw exception
      throw Exception("start position is not on board");
    }
    if (endCol < 'A' || endCol > 'H' || endRow < '1' || endRow > '8') {
      //Throw exception
      throw Exception("end position is not on board");
    }
    const Piece* startPc = board(start);
    const Piece* endPc = board(end);
    if (startPc == nullptr) { //may need to add * to deinference pointer
      throw Exception("no piece at start position");
    }
    if (turn_white() != startPc->is_white()) {
      throw Exception("piece color and turn do not match");
    }
    if (endPc != nullptr) { //all throws that deal with capturing should be nested in this if statement
      if (turn_white() == endPc->is_white()) {
	throw Exception("cannot capture own piece");
      }
      if (!(startPc->legal_capture_shape(start, end))){
	throw Exception("illegal capture shape");
      }
    }
    else {
      if (!(startPc->legal_move_shape(start, end))){
	throw Exception("illegal move shape");
      }
    }

    if (!(is_clear_path(start, end))) {
      throw Exception("path is not clear");
    }

    char startPcDes = startPc->to_ascii();
    char endPcDes;

    //make move
    if(endPc != nullptr) {
      //delete end piece
      endPcDes = endPc->to_ascii();
      board.deletePc(end);
    }
    board.add_piece(end, startPcDes);
    board.deletePc(start);
    
    if(in_check(is_white_turn)) {
      //reverse move
      board.deletePc(end);
      if (endPc != nullptr) {
	board.add_piece(end, endPcDes);
      }
      board.add_piece(start, startPcDes);
      throw Exception("move exposes check");
    }
    //check for promotion
    board.promotion();
    //if we actually make move, switch turn
    set_turn(!(turn_white()));


  }

  bool Game::in_check(bool white) const {
    std::pair<char, char> targetKing;
    char charMin;
    char charMax;
    if (white) {
      targetKing = board.get_piece('K');
      charMin = 'a';
      charMax = 'z';
    }
    else {
      targetKing = board.get_piece('k');
      charMin = 'A';
      charMax = 'Z';
    }
    for(char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
	std::pair<char, char> start;
        start.first = c;
        start.second = r;
	const Piece* targetPc = board(start);
	if (targetPc != nullptr) {
	  if (targetPc->to_ascii() >= charMin && targetPc->to_ascii() <= charMax) {
	    if (targetPc->legal_capture_shape(start, targetKing) && is_clear_path(start, targetKing)) {
	      return true;
	    }
	  }
	}
      }
    }
    return false;
  }

  bool Game::testCheck(bool turn, const Piece* startPc, const Piece* endPc, std::pair<char, char> start, std::pair<char, char> end) {
    bool output = false;
    char startPcDes = startPc->to_ascii();
    char endPcDes;
    //make move
    if(endPc != nullptr) {
      //delete end piece
      endPcDes = endPc->to_ascii();
      board.deletePc(end);
    }
    board.add_piece(end, startPcDes);
    board.deletePc(start);

    if(in_check(turn)) {
      output = true;
    }
    //reverse move
    board.deletePc(end);
    if (endPc != nullptr) {
      board.add_piece(end, endPcDes);
    }
    board.add_piece(start, startPcDes);
    return output;
  }

  bool Game::is_clear_path(std::pair<char, char> start, std::pair<char, char> end) const{
    char startCol = start.first; //column specified before row in format A1 - H8
    char startRow = start.second;
    //check if its a knight (always a clear path)
    const Piece* startPc = board(start);
    if (startPc->to_ascii() == 'N' || startPc->to_ascii() == 'n') {
      return true;
    }
    char endCol = end.first;
    char endRow = end.second;
    int dCol = endCol - startCol;
    int dRow = endRow - startRow;
    if (dCol < 0) {
      dCol = -1;
    }
    if (dCol > 0) {
      dCol = 1;
    }
    if (dRow < 0) {
      dRow = -1;
    }
    if (dRow > 0) {
      dRow = 1;
    }
    char testCol = startCol + dCol;
    char testRow = startRow + dRow;
    while (!(testCol ==  endCol && testRow == endRow)) {
      //std::cout << "checking space: " << testCol << testRow << std::endl;
      std::pair<char,char> testPair;
      testPair.first = testCol;
      testPair.second = testRow;
      if(board(testPair) != nullptr) { //piece at test position
	return false;
      }
      testCol += dCol;
      testRow += dRow;
    }
    return true;
    
  }
  
  bool Game::in_mate(bool white) const {
    if (!(in_check(white))) {
      return false;
    }
    return in_stalemate(white);
  }
  
   


  bool Game::in_stalemate(bool white) const {
    char charMin;
    char charMax;
    if (white) {
      charMin = 'A';
      charMax = 'Z';
    }
    else {
      charMin = 'a';
      charMax = 'z';
    }
    for(char c = 'A'; c <= 'H'; c++) {
      for (char r = '1'; r <= '8'; r++) {
        std::pair<char, char> start;
        start.first = c;
        start.second = r;
        const Piece* targetPc = board(start);
        if (targetPc != nullptr) {
          if (targetPc->to_ascii() >= charMin && targetPc->to_ascii() <= charMax){
            //iterates through each space on the board
            for(char r1 = '8'; r1 >= '1'; r1--) {
              for(char c1 = 'A'; c1 <= 'H'; c1++) {
                //make a copy of game to try move
                std::pair<char, char> position;
                position.first = c1;
                position.second = r1;
                bool clearPath = is_clear_path(start,position);
                bool legalMove = false;
                bool legalCapture = false;
                if (board(position) != nullptr) {
                  legalCapture = targetPc->legal_capture_shape(start,position) && (targetPc->is_white() != board(position)->is_white());
                }
                else {
                  legalMove = targetPc->legal_move_shape(start,position);
                }
                if (clearPath && (legalMove || legalCapture)) {
                  Game *testGame = new Game(*this);
                  Board brd = testGame->get_board();
                  if(!(testGame->testCheck(is_white_turn, brd(start), brd(position), start, position))){
                    delete testGame;
                    return false;
                  }
                  delete testGame;
                }
              }
            }
          }
        }
      }
    }
    return true;
  }

  void Game::set_turn(bool white) {
    is_white_turn = white;
  }

  std::istream& operator>> (std::istream& is, Game& game) {
    //delete current pieces
    
    game.clear_GameBoard(); //makes an empty board
    //iterate through board to add loaded pieces
    char nxt;
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	std::pair<char, char> position = std::pair<char,char>(c,r);
	is >> nxt; //get next char
	if (nxt != '-') {
	  game.add_pieceToBoard(position,nxt);
	}
      }
    }
    is >> nxt;
    game.set_turn(false);
			      
    if (nxt == 'w') {
      game.set_turn(true);
    }
    
    return is;
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<< (std::ostream& os, const Game& game) {
    // Write the board out and then either the character 'w' or the character 'b',
    // depending on whose turn it is
    return os << game.get_board() << (game.turn_white() ? 'w' : 'b');
  }
}
