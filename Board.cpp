

#include <iostream>
#include <utility>
#include <map>
#include "Terminal.h"
#include "Board.h"
#include "CreatePiece.h"

namespace Chess
{

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  Board::~Board() {
    occ.clear();
  }

  void Board::clear_board() {
    for(char c = 'A'; c <= 'H'; c++) {
      for(char r = '8'; r >= '1'; r--) {
	std::pair<char,char> position;
	position.first = c;
	position.second = r;
	std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position);
	if (it != occ.cend()) {
	  deletePc(position);
	}
      }
    }
    occ.clear();
  }


  void Board::deletePc(std::pair<char, char> position) {
    delete occ[position];
    occ[position] = nullptr;
  }
  
  const Piece* Board::operator()(std::pair<char, char> position) const{
    //Not entirely sure if this will automatically be a nullptr if nothing is there
    std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position);
    const Piece* ref_piece;
    if (it != occ.cend()) {      
      ref_piece = it->second;
    }
    else {
      ref_piece = nullptr;
    }
    return ref_piece;
  }
  bool Board::add_piece(std::pair<char, char> position, char piece_designator) {

    char column = position.first;
    char row = position.second;
    if(column < 'A' || column > 'H' || row < '1' || row > '8') {
      return false;
    }
    if(occ[position] != nullptr) {
      return false;
    }
    occ[position] = create_piece(piece_designator);
    if(occ[position] == nullptr) {
      return false;
    }
    
    return true;
  }

  std::pair<char,char> Board::get_piece(char piece) const {
    //only works every time for king
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        std::pair<char, char> position;
        position.first = c;
        position.second = r;
        std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position);
        const Piece* pc;
	if (it != occ.cend()) {
          pc = it->second;
	  if (pc) {
	    char pcDes = pc->to_ascii();
	    if (pcDes == piece) {
	      return position;
	    }
	  }
	}
	
      }

    }
    return std::pair<char,char>('-', '-'); //signals that piece does not exist (if this is ever returned there is a big problem

  }

  bool Board::has_valid_kings() const {

    int white_king_count = 0;
    int black_king_count = 0;
    //loop through the entire board and if the piece is a king add it to count
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	std::pair<char, char> position;
	position.first = c;
	position.second = r;
	std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(position);
	const Piece* piece;
      	if (it != occ.cend()) {
	  piece = it->second;
	}
	else {
	  piece = nullptr;
	}
	if (piece) {
	  if(piece->to_ascii() == 'k') {
	    black_king_count++;
	  }
	  if(piece->to_ascii() == 'K') {
	    white_king_count++;
	  }
	}
      }
    }
    
    if(black_king_count == 1 && white_king_count == 1) {
      return true;
    }
    return false;
  }

  void Board::display() const {
    //to test <<
    //std::cout << *this << std::endl;
    Terminal::color_fg(true, Terminal::WHITE);
    Terminal::color_bg(Terminal::BLACK);
    std::cout << "    A   B   C   D   E   F   G   H" << std::endl;
    std::cout << "    -   -   -   -   -   -   -   -" << std::endl;
    for(char r = '8'; r >= '1'; r--) {
      std::cout << r << " | ";
      for(char c = 'A'; c <= 'H'; c++) {
	std::pair<char, char> target;
        target.first = c;
        target.second = r;
        std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.find(target);
	const Piece* targetPc;
	if (it != occ.cend()) {
	  targetPc = it->second;
	}
	else {
	  targetPc = nullptr;
	}

	if (targetPc) { //TODO deinferences NULL pointer (need to get this to work for << to work and we cant modify that function)
	  //black pieces = red, white pieces = blue
	  if (targetPc->is_white()) {
	    Terminal::color_fg(true, Terminal::RED); //white piece color
	  }
	  else {
	    Terminal::color_fg(true, Terminal::BLUE);
	  }
	  std::cout << targetPc->to_ascii();
	  Terminal::color_fg(true, Terminal::WHITE); //border color
	  std::cout << " | ";
	}
	else {
	  std::cout << "  | "; //no piece = blank spot
	}
      }
      std::cout << std::endl << "    -   -   -   -   -   -   -   - " << std::endl;
    }
  }


  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
        const Piece* piece = board(std::pair<char, char>(c, r));
        if (piece) {
          os << piece->to_ascii();
        } else {
          os << '-';
        }
      }
      os << std::endl;
    }
    return os;
  }

  void Board::promotion() {
    for(std::map<std::pair<char, char>, Piece*>::iterator it  = occ.begin(); it != occ.end(); it++) {
      if (it->second != nullptr) {
	if (it->first.second == '8' && it->second->to_ascii() == 'P') {
	  deletePc(it->first);
	  add_piece(it->first, 'Q');
	}
	if (it->first.second == '1' && it->second->to_ascii() == 'p') {
	  deletePc(it->first);
	  add_piece(it->first, 'q');
	}
      }
    }
  }
}

