#include"Display3D.hpp"
#include"Map.hpp"
#include"FirstPerson.hpp"
#include"GameMaster.hpp"


void GameMaster::keyPressEvent(QKeyEvent *event)  {



    if(event->key() == Qt::Key_W) wPressed = true;
    if(event->key() == Qt::Key_A) aPressed = true;
    if(event->key() == Qt::Key_S) sPressed = true;
    if(event->key() == Qt::Key_D) dPressed = true;
    if(event->key() == Qt::Key_Left) leftPressed = true;
    if(event->key() == Qt::Key_Right) rightPressed = true;
}
void GameMaster::keyReleaseEvent(QKeyEvent *event) {

    if(event->key() == Qt::Key_W) wPressed = false;
    if(event->key() == Qt::Key_A) aPressed = false;
    if(event->key() == Qt::Key_S) sPressed = false;
    if(event->key() == Qt::Key_D) dPressed = false;
    if(event->key() == Qt::Key_Left) leftPressed = false;
    if(event->key() == Qt::Key_Right) rightPressed = false;


}

char GameMaster::CheckHitBox(float NextPlayerX, float NextPlayerY, float HitboxLength) {

    bool HitX = false;
    bool HitY = false;

    //check x (using old y)
    if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>(NextPlayerX)]
            && !worldMap[static_cast<int>(player.getPlayerPosY())*mapWidth + static_cast<int>(NextPlayerX + HitboxLength)]

            && !worldMap[static_cast<int>(player.getPlayerPosY() + HitboxLength)*mapWidth + static_cast<int>(NextPlayerX)]

            && !worldMap[static_cast<int>(player.getPlayerPosY() + HitboxLength) * mapWidth + static_cast<int>(NextPlayerX)]

            && !worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + HitboxLength)]
            && !worldMap[static_cast<int>(player.getPlayerPosY() + HitboxLength)* mapWidth +static_cast<int>(NextPlayerX + HitboxLength)]) {

        HitX = true;
    }

    //check y (using old x)
    if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
            && !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + HitboxLength)]

            && !worldMap[static_cast<int>(NextPlayerY + HitboxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]

            && !worldMap[static_cast<int>(NextPlayerY + HitboxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]

            && !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + HitboxLength)]
            && !worldMap[static_cast<int>(NextPlayerY + HitboxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + HitboxLength)]) {

        HitY = true;

    }

    if(HitX && HitY) return 'B';				//Both Free

    else if(HitX && !HitY) return 'X';			//X Free

    else if(!HitX && HitY) return 'Y';			// Y Free

    else return 'H';					// Hit
}


void GameMaster::MovePlayer(char Direction, char DirectionFree, float travelDistance) {

    switch (DirectionFree) {

    case 'B':	//Both X and Y are Free
        player.movePlayerRelativeToRotationAngle( Direction, 'X', travelDistance);
        player.movePlayerRelativeToRotationAngle( Direction, 'Y', travelDistance);
        break;

    case 'X':	//X is Free

        player.movePlayerRelativeToRotationAngle( Direction, 'X', travelDistance);
        break;

    case 'Y': 	//Y is Free
        player.movePlayerRelativeToRotationAngle( Direction, 'Y', travelDistance);
        break;

    default :

        break;

    }
}

dda GameMaster::calculateWallHit(float RayAngel) {

    dda Ray;

    Ray.RayAngel = RayAngel; 
    
    //Middle of the Player
    Ray.RayStartX = player.getPlayerPosX() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;
    Ray.RayStartY = player.getPlayerPosY() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;

    //Direction Vector of the Ray (For Unit Circle)
    float rayDirectionX = std::sin(player.getDirectionAngle() + Ray.RayAngel);
    float rayDirectionY = std::cos(player.getDirectionAngle() + Ray.RayAngel);

    //In which Tile the Ray is.
    int TileX = static_cast<int>(Ray.RayStartX);
    int TileY = static_cast<int>(Ray.RayStartY);

    // Calculation of the hypothenuses for movement of 1 Tile in x/y direction. (Betrag) cause distance is not negative if angel is.
    float XMovementHypothenuses = std::abs(1 / rayDirectionX);
    float YMovementHypothenuses = std::abs(1 / rayDirectionY);

    //Length of the current Ray
    float CurrentRayLengthXMovement;
    float CurrentRayLengthYMovement;

    //indicator if the ray should move further
    int RayXMovement;
    int RayYMovement;

    //Go Left if the Direction of the Ray is Negative
    if(rayDirectionX < 0) {
        RayXMovement = -1;
        
	//Calculate Ray Length from Start Position to first GridLine in -X direction
        CurrentRayLengthXMovement = (Ray.RayStartX - TileX) * XMovementHypothenuses;
    }

    else {
        RayXMovement = 1;
       
	//Calculate Ray Length from Start Position to first GridLine in +X direction
       	CurrentRayLengthXMovement = (TileX + 1 - Ray.RayStartX) * XMovementHypothenuses;

    }

    if (rayDirectionY < 0) {
        RayYMovement = -1;
        
	//Calculate Ray Length from Start Position to first GridLine in -Y direction (up)
	CurrentRayLengthYMovement = (Ray.RayStartY - TileY) * YMovementHypothenuses;
    }
    else {
        RayYMovement = 1;
       
	//Calculate Ray Length from Start Position to first GridLine in Y direction (down)
	CurrentRayLengthYMovement =  (TileY +1 - Ray.RayStartY) * YMovementHypothenuses;
    }

    bool hit = false;
    while(!hit) {

        if(CurrentRayLengthXMovement < CurrentRayLengthYMovement) {
            CurrentRayLengthXMovement += XMovementHypothenuses;

            TileX += RayXMovement;

            Ray.VerticalHit = true;
            Ray.HorizontalHit = false;
        }
        else {
            CurrentRayLengthYMovement += YMovementHypothenuses;
            TileY += RayYMovement;

            Ray.HorizontalHit = true;
            Ray.VerticalHit = false;
        }

        if(worldMap[TileY * mapWidth + TileX]) {
            hit = true;
        }
    }

    if(Ray.VerticalHit) {

        CurrentRayLengthXMovement -= XMovementHypothenuses;
        Ray.Raylength = CurrentRayLengthXMovement;
    }


    if(Ray.HorizontalHit) {

        CurrentRayLengthYMovement -= YMovementHypothenuses;
        Ray.Raylength = CurrentRayLengthYMovement;	//describes the Eeudelican Raylength
    }
    hit = false;
//Does change the sideDistanceX (length of actual Ray) into only X with the Hyp/X ratio rayDirection.

    Ray.Raylength3D = Ray.Raylength * std::cos(Ray.RayAngel);
    Ray.RayEndX = Ray.RayStartX  + rayDirectionX * Ray.Raylength;
    Ray.RayEndY = Ray.RayStartY  + rayDirectionY * Ray.Raylength;
    return Ray;

}


GameMaster::GameMaster() {

    resize(1200, 600);
    setWindowTitle("MainWindow");

    mapWidth = 10;
    mapHeight = 10;
    worldMap = {
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 2, 2, 0, 0, 0, 0, 1,
        1, 0, 0, 2, 2, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 0, 0, 0, 0, 0, 3, 3, 0, 1,
        1, 0, 4, 0, 0, 0, 3, 3, 0, 1,
        1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    };

    Map2D = new Map(this);
    Game3D = new Display3D(this);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(Map2D);
    layout->addWidget(Game3D);


    QTimer *timer = new QTimer(this);			//declareing a timer
    timer->start(16);					//16ms for 60Hz
    connect(timer, &QTimer::timeout, this, &GameMaster::SuperLoop); 	//when timer run down, call SuperLoop

}

void GameMaster::SuperLoop() {
    float travelDistance = 0.05f;
    float NextPlayerX;
    float NextPlayerY;
    float hitBoxLength = (player.getPlayerSize() / TileSizeX) -0.001 ;
    char Direction;
    char DirectionFree;

    if(wPressed) {

        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle());
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle());
        DirectionFree = GameMaster::CheckHitBox(NextPlayerX, NextPlayerY, hitBoxLength);
        Direction = 'W';
        GameMaster::MovePlayer(Direction, DirectionFree, travelDistance);
    }

    if(aPressed) {

        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle() + M_PI/2  );
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle() + M_PI/2 );
        DirectionFree = GameMaster::CheckHitBox(NextPlayerX, NextPlayerY, hitBoxLength);
        Direction = 'A';
        GameMaster::MovePlayer(Direction, DirectionFree, travelDistance);
    }

    if(sPressed) {

        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle() + M_PI );
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle() + M_PI );
        DirectionFree = GameMaster::CheckHitBox(NextPlayerX, NextPlayerY, hitBoxLength);
        Direction = 'S';
        GameMaster::MovePlayer(Direction, DirectionFree, travelDistance);
    }

    if(dPressed) {

        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle() + M_PI * 3/2 );
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle() + M_PI * 3/2 );
        DirectionFree = GameMaster::CheckHitBox(NextPlayerX, NextPlayerY, hitBoxLength);
        Direction = 'D';
        GameMaster::MovePlayer(Direction, DirectionFree, travelDistance);
    }

    if(leftPressed) {

        player.increasePlayerAngle(2);
    }

    if(rightPressed) {

        player.increasePlayerAngle(-2);

    }

    Map2D->update();
    Game3D->update();

}

