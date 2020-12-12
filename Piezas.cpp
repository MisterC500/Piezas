#include "Piezas.h"
#include <vector>
#include <iostream>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/

Piezas::Piezas()
{
  board = std::vector<std::vector<Piece>>(BOARD_ROWS, std::vector<Piece>(BOARD_COLS,Blank));
  turn = X;
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
  for(int i = 0; i < BOARD_ROWS; i++)
  {
    for(int j = 0; j < BOARD_COLS; j++)
      board[i][j] = Blank;
  }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
  //First check if given column is out of bounds
  if(column >= BOARD_COLS)
  {
    //change turns if placed out of bounds
    if(turn == X)
      turn = O;
    else
      turn = X;
    return Invalid; 
  }

  //Switch on turns X and O
  switch(turn)
  {
    //if turn is X
    case X:
      {
        for(int i = 0; i < BOARD_ROWS; i++)
        {
          for(int j = 0; j < BOARD_COLS; j++)
          {
            //check to see we have right column, and is not already taken up by X or O
            if( (j == column) && (board[i][j] != X) && (board[i][j] != O) )
            {
              board[i][j] = X;
              turn = O;
              return X;
            }
          }
        }//for
        break;
      }
    //if turn is O
    case O:
      {
        for(int i = 0; i < BOARD_ROWS; i++)
        {
          for(int j = 0; j < BOARD_COLS; j++)
          {
            if( j == column && (board[i][j] != X) && (board[i][j] != O) )
            {
              board[i][j] = O;
              turn = X;
              return O;
            }
          }
        }//for
        break;
      }
  }//switch
    return Blank;
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
  //if row or column is out of bounds
  if(row >= BOARD_ROWS || column >= BOARD_COLS)
    return Invalid;

  //create temp piece and check if blank/X/O
  Piece temp = board[row][column];

  if(temp == X)
    return X;
  else if(temp == O)
    return O;
  else
    return Blank;
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
  //temporarily keep track of X and O totals
  int xTot = 0;
  int oTot = 0;

  //tmp track count of X/O horizontally
  int xHor = 0;
  int oHor = 0;

  //tmp track count of X/O vertically
  int xVer = 0;
  int oVer = 0;

  //if board is empty, game not over
  if(board.empty())
    return Invalid;


  //check the columns first for counts
  for(int i = 0; i < BOARD_ROWS; i++)
  {
    for(int j = 0; j < BOARD_COLS; j++)
    {
      //check if any spaces have blanks or invalids, if so game can't be over
      if( (board[i][j] == Blank)  )
        return Invalid;

      if(board[i][j] == X)
        xVer++;
      else if(board[i][j] == O)
        oVer++;

    }

    if(xTot < xVer)
      xTot = xVer;
    if(oTot < oVer)
      oTot = oVer;
  }

  for(int i = 0; i < BOARD_COLS; i++)
  {
    for(int j = 0; j < BOARD_ROWS; j++)
    {
      //No need to check for blank space here, already checked in above loop

      if(board[j][i] == X)
        xHor++;
      else if(board[j][i] == O)
        oHor++;

    }

    if(xTot < xHor)
      xTot = xHor;
    if(oTot < oHor)
      oTot = oVer;
  }

  if(xTot > oTot)
    return X;
  else if(oTot > xTot)
    return O;
  else
    return Blank;

}
