#include"FirstPerson.hpp"

class Player {

private:

    float PlayerPosX;
    float PlayerPosY;
    float PlayerSize;
    float DirectionAngle;
    float DirectionLength;

public:

    Player();
    void changePlayerPosX(float newPlayerPosX);
    void changePlayerPosY(float newPlayerPosY);
    void increasePlayerAngle(float AngleIncreasement);
    void movePlayerRelativeToRotationAngle(char Direction,char Slider, float Distance);
    float getPlayerPosX();
    float getPlayerPosY();
    float getDirectionAngle();
    float getDirectionLength();
    float getPlayerSize();	 
};
