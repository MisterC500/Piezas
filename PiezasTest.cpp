/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}

//check X's first turn
TEST(PiezasTest, X_first_turn)
{
  Piezas bb = Piezas();
  Piece X_ret = bb.dropPiece(0);
  ASSERT_EQ(X_ret, X);
}

//Turn switched to O, check O's drop
TEST(PiezasTest, O_first_turn)
{
  Piezas bb = Piezas();
  //Need to drop a piece first to switch turns
  bb.dropPiece(0);
  Piece O_ret = bb.dropPiece(0);
  ASSERT_EQ(O_ret, O);
}

//Check to see if Piece will drop when column is full
TEST(PiezasTest, column_full)
{
  Piezas bb = Piezas();
  bb.dropPiece(0);
  bb.dropPiece(0);
  bb.dropPiece(0);
  bb.dropPiece(0);

  Piece too_full = bb.dropPiece(0);
  ASSERT_EQ(too_full, Blank);
}

//Test for column out of bounds
TEST(PiezasTest, column_out_of_bound)
{
  Piezas bb = Piezas();
  Piece out_of_bound = bb.dropPiece(5);
  ASSERT_EQ(out_of_bound, Invalid);
}

//Check to see if reset works
TEST(PiezasTest, resetCheck)
{
  Piezas bb = Piezas();
  bb.dropPiece(0);
  bb.dropPiece(0);
  bb.dropPiece(0);
  bb.dropPiece(0);

  bb.dropPiece(1);
  bb.dropPiece(1);
  bb.dropPiece(1);
  bb.dropPiece(1);

  bb.dropPiece(2);
  bb.dropPiece(2);
  bb.dropPiece(2);
  bb.dropPiece(2);

  bb.dropPiece(3);
  bb.dropPiece(3);
  bb.dropPiece(3);
  bb.dropPiece(3);

  bb.reset();

  ASSERT_EQ(bb.pieceAt(0,0),Blank);
  ASSERT_EQ(bb.pieceAt(0,1),Blank);
  ASSERT_EQ(bb.pieceAt(0,2),Blank);

}

//check for winner, X in this case will be winner
TEST(PiezasTest, X_win)
{
  Piezas bb = Piezas();

  bb.dropPiece(0); //X
  bb.dropPiece(1); //O
  bb.dropPiece(0); //X
  bb.dropPiece(2); //O
  bb.dropPiece(0); //X
  bb.dropPiece(3); //O
  bb.dropPiece(1); //X
  bb.dropPiece(1); //O
  bb.dropPiece(2); //X
  bb.dropPiece(2); //O
  bb.dropPiece(3); //X
  bb.dropPiece(3); //O

  Piece state = bb.gameState();
  ASSERT_EQ(state,X);


}
