#ifndef IPAWN_H
#define IPAWN_H


class iPawn
{
    public:
		virtual ~iPawn(){;}

		virtual bool setPosition(int x, int y) = 0;
		virtual int getXPos() = 0;
		virtual int getYPos() = 0;
		virtual std::vector<std::pair<int,int>> getMoves(unsigned int max) = 0;

		virtual bool hasOrb() = 0;
		virtual void toggleOrb() = 0;
};
#endif
