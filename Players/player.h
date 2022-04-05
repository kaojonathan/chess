#ifndef PLAYER_H_
#define PLAYER_H_
#include <vector>
#include <utility>
#include <string>
#include <memory>

class Piece; // the pieces
class Board; // game board
class Player
{
protected:
    int side;                    // 0 for white and 1 for black
    Board *gameBoard;            // the game board
    std::shared_ptr<Piece> king; // the player's king piece
    // the player's pieces (EXCLUDING KING)
    std::vector<std::shared_ptr<Piece>> pieces;
    // the pieces not on the board
    std::vector<std::shared_ptr<Piece>> inactivePieces;
    // the opponent
    Player *opponent;
    // the piece that checks the opponent
    Piece *opponentCheck;
    int type; // 0 for human, 1 for computer
    // moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
    // returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
    virtual std::pair<int, std::string> playerMove(int &oldCol, int &oldRow, int &newCol, int &newRow) = 0;

public:
    Player(int side, int type);         // constructor
    virtual ~Player();                  // destructor
    void init(Board *, Player *player); // initalize the player's game state
    void claimPieces();                 // claim its pieces
    // moves a piece from (oldCol, oldRow) to (newCol, newRow), and updates them if computer moves (since random).
    // returns a pair (int, string) where int is type of move and string is piece captured (if necessary)
    std::pair<int, std::string> move(int &oldCol, int &oldRow, int &newCol, int &newRow)
    {
        return playerMove(oldCol, oldRow, newCol, newRow);
    }
    void print(); // print players fields DEBUG
    int getType()
    { // returns the type of the player
        return type;
    }
    std::vector<std::shared_ptr<Piece>> const &getPieces()
    { // gets the pieces of the player
        return pieces;
    }
    void addToPieces(std::shared_ptr<Piece>); // adds a piece to the player's pieces
    void removePiece(std::pair<int, int>);    // removes the piece in position (x, y) and places it in inactivePieces.
    void deletePiece(std::pair<int, int>);    // deletes the piece in position (x, y)
    // list all the Pieces that can attack the given position
    std::vector<Piece *> canAttack(std::pair<int, int>);
    // set opponentCheck to the Piece
    void kingCheckedBy(Piece *);
    // update status of all pieces of the player, return 0 if there is avaliable move for player, 1 if it is a checkmate, 2 if it is a draw.
    int checkStatus();
    // unset the status fields of each piece
    void unsetStatus();
    // true if the player still has valid move
    bool canMove();
};

#endif