#ifndef pawn_H
#define pawn_H


class pawn
{
    private:
    	void createBoard();
		void printBoard();

    public:
        pawn();
		virtual ~pawn();

		void setPosition(int x, int y);
		int getXPos(){return -1;}
		int getYPos(){return -1;}
		
		bool hasOrb(){return false;}
		void toggleOrb();
};
#endif
