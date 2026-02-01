#include"FirstPerson.hpp"
#include"Player.hpp"
class GameMaster : public QWidget {
private:
    Map *Map2D;
    Display3D *Game3D;
    QTimer *timer;

public:
    std::vector<int> worldMap;
    int mapWidth;
    int  mapHeight;

    int TileSizeX = 50;
    int TileSizeY = 50;

    Player player;

    bool wPressed = false;
    bool aPressed = false;
    bool sPressed = false;
    bool dPressed = false;
    bool leftPressed = false;
    bool rightPressed = false;

	char CheckHitBox(float NextPlayerX, float NextPlayerY, float HitboxLength);
	void MovePlayer(char Direction, char DirectionFree, float travelDistance);
    GameMaster();
    void SuperLoop();


    void keyPressEvent(QKeyEvent *event) override;    
	 void keyReleaseEvent(QKeyEvent *event) override; 
     	 dda calculateWallHit(float RayAngel);
};
