#ifndef pawn_H
#define pawn_H


class pawn
{
    private:
    	void createBoard();
		void printBoard();

		int XPos;
		int YPos;
		bool HasOrb;

    public:
        pawn();
		virtual ~pawn();

		void setPosition(int x, int y);
		int getXPos(){return XPos;}
		int getYPos(){return YPos;}
		
		bool hasOrb(){return HasOrb;}
		void toggleOrb();
};
#endif
