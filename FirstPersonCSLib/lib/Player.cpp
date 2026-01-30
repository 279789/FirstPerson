#include "FirstPerson.hpp"
#include"Player.hpp"


Player::Player() {

        //Position relative to Tiles
        PlayerPosX = 6;
        PlayerPosY = 5;


        PlayerSize = 10;

        DirectionAngle = 0;   // Important for Mouse Integration
        DirectionLength = 25;

    }

    void Player::changePlayerPosX(float newPlayerPosX) {
        PlayerPosX = newPlayerPosX;
    }


    void Player::changePlayerPosY(float newPlayerPosY) {
        PlayerPosY = newPlayerPosY;
    }

    void Player::increasePlayerAngle(float AngleIncreasement) {

        DirectionAngle += ((AngleIncreasement *2 * M_PI) / 360);

    }

    void Player::movePlayerRelativeToRotationAngle(char Direction,char Slider, float Distance) {
        if(Slider == 'X') {
            if(Direction == 'W') {

                PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle);
            }

            if(Direction == 'A') {

                PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI / 2);
            }

            if(Direction == 'S') {

                PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI);
            }

            if(Direction == 'D') {

                PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI * 3 / 2);
            }
        }



        if(Slider == 'Y') {
            if(Direction == 'W') {

                PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle);
            }

            if(Direction == 'A') {

                PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI / 2);
            }

            if(Direction == 'S') {

                PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI );
            }

            if(Direction == 'D') {

                PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI * 3 / 2 );
            }
        }




    }

    float Player::getPlayerPosX() {
        return PlayerPosX;
    }

    float Player::getPlayerPosY() {
        return PlayerPosY;
    }

    float Player::getDirectionAngle() {
        return DirectionAngle;
    }

    float Player::getDirectionLength() {
        return DirectionLength;
    }

    float Player::getPlayerSize() {
        return PlayerSize;
    }

