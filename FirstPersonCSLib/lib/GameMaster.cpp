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

    dda GameMaster::calculateWallHit(float RayAngel) {

        dda Ray;

        Ray.RayAngel = RayAngel; // (RayAngel *2 *M_PI / 360);

        //Middle of the Player
        Ray.RayStartX = player.getPlayerPosX() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;
        Ray.RayStartY = player.getPlayerPosY() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;

        //Direction Vector of the Player (Verhältnis)
        float rayDirectionX = std::sin(player.getDirectionAngle()+Ray.RayAngel);
        float rayDirectionY = std::cos(player.getDirectionAngle()+Ray.RayAngel);

        //In which Tile the Player is.
        int TileX = static_cast<int>(Ray.RayStartX);
        int TileY = static_cast<int>(Ray.RayStartY);

        // Calculation of the hypothenuses for movement of 1 in x/y direction. (Betrag) cause distance is not negative if angel is.
        float edgeDistanceX = std::abs(1 / rayDirectionX);
        float edgeDistanceY = std::abs(1 / rayDirectionY);

        //Was to the next grid line
        float sideDistanceX;
        float sideDistanceY;

        //indicator if the ray should move further
        int walkX;
        int walkY;

        int wall = 0;

        //Go Left if Direction of x is Negative
        if(rayDirectionX < 0) {
            walkX = -1;
            //Calculate Length for 1 Tile in -X direction
            sideDistanceX = (Ray.RayStartX - TileX) * edgeDistanceX;
        }

        else {
            walkX = 1;
            sideDistanceX = (TileX + 1 - Ray.RayStartX) * edgeDistanceX;

        }

        if (rayDirectionY < 0) {
            walkY = -1;
            sideDistanceY = (Ray.RayStartY - TileY) * edgeDistanceY;
        }
        else {
            walkY = 1;
            sideDistanceY =  (TileY +1 - Ray.RayStartY) *edgeDistanceY;
        }

        bool hit = false;
        while(!hit) {

            if(sideDistanceX < sideDistanceY) {
                sideDistanceX += edgeDistanceX;

                TileX += walkX;

                Ray.VerticalHit = true;
                Ray.HorizontalHit = false;
            }
            else {
                sideDistanceY += edgeDistanceY;
                TileY += walkY;

                Ray.HorizontalHit = true;
                Ray.VerticalHit = false;
            }

            if(worldMap[TileY * mapWidth + TileX]) {
                hit = true;
            }
        }

        if(Ray.VerticalHit) {

            sideDistanceX -= edgeDistanceX;
            Ray.Raylength = sideDistanceX;
        }


        if(Ray.HorizontalHit) {

            sideDistanceY -= edgeDistanceY;
            Ray.Raylength= sideDistanceY;	//describes the Eeudelican Raylength
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


    if(wPressed) {
        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle());
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle());


        //check x (using old y)
        if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>(NextPlayerX)]
                && !worldMap[static_cast<int>(player.getPlayerPosY())*mapWidth + static_cast<int>(NextPlayerX + hitBoxLength)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength) * mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'W', 'X', travelDistance);

        }

        //check y (using old x)
        if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
                && !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'W', 'Y', travelDistance);

        }


    }


    if(aPressed) {
        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle() + M_PI/2 );
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle()+ M_PI/2 );


        //check x (using old y)
        if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>(NextPlayerX)]
                && !worldMap[static_cast<int>(player.getPlayerPosY())*mapWidth + static_cast<int>(NextPlayerX + hitBoxLength)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength) * mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'A', 'X', travelDistance);

        }

        //check y (using old x)
        if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
                && !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'A', 'Y', travelDistance);

        }


    }

    if(sPressed) {
        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle() + M_PI);
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle() + M_PI);


        //check x (using old y)
        if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>(NextPlayerX)]
                && !worldMap[static_cast<int>(player.getPlayerPosY())*mapWidth + static_cast<int>(NextPlayerX + hitBoxLength)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength) * mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'S', 'X', travelDistance);

        }

        //check y (using old x)
        if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
                && !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'S', 'Y', travelDistance);

        }


    }


    if(dPressed) {
        NextPlayerY = player.getPlayerPosY() + travelDistance * std::cos(player.getDirectionAngle()+ M_PI * 3/2);
        NextPlayerX = player.getPlayerPosX() + travelDistance * std::sin(player.getDirectionAngle()+ M_PI * 3/2);


        //check x (using old y)
        if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>(NextPlayerX)]
                && !worldMap[static_cast<int>(player.getPlayerPosY())*mapWidth + static_cast<int>(NextPlayerX + hitBoxLength)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength) * mapWidth + static_cast<int>(NextPlayerX)]

                && !worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
                && !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'D', 'X', travelDistance);

        }

        //check y (using old x)
        if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
                && !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]

                && !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
                && !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {

            player.movePlayerRelativeToRotationAngle( 'D', 'Y', travelDistance);

        }


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





