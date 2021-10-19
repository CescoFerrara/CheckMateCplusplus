
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Piece.h"
#include "Board.h"
#include "Exceptions.h"

namespace Chess
{

  class Game {

  public:
    // This default constructor initializes a board with the standard
    // piece positions, and sets the state to white's turn
    Game();

    //copy constructor
    Game(const Game& rhs);

    // Returns a constant reference to the board
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    const Board& get_board() const { return board; }

    // Returns true if it is white's turn
    /////////////////////////////////////
    // DO NOT MODIFY THIS FUNCTION!!!! //
    /////////////////////////////////////
    bool turn_white() const { return is_white_turn; }

    // Attemps to make a move. If successful, the move is made and
    // the turn is switched white <-> black. Otherwise, an exception is thrown
    void make_move(std::pair<char, char> start, std::pair<char, char> end);

    // Returns true if the designated player is in check
    bool in_check(bool white) const;

    bool testCheck(bool turn, const Piece* startPc, const Piece* endPc, std::pair<char, char> start, std::pair<char, char> end);

    bool is_clear_path(std::pair<char, char> start, std::pair<char, char> end) const;
    
    // Returns true if the designated player is in mate
    bool in_mate(bool white) const;

    // Returns true if the designated player is in stalemate
    bool in_stalemate(bool white) const;

    //sets is_white_turn to whatever parameter is
    void set_turn(bool white);

    void add_pieceToBoard(std::pair<char, char> pos, char des);

    void delPcBoard(std::pair<char, char> position);

    void clear_GameBoard();


  private:
    // The board
    Board board;

    // Is it white's turn?
    bool is_white_turn;


  };

  // Writes the board out to a stream
  std::ostream& operator<< (std::ostream& os, const Game& game);

  // Reads the board in from a stream
  std::istream& operator>> (std::istream& is, Game& game);

}
#endif // GAME_H
