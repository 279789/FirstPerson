#include"Map.hpp"
#include"GameMaster.hpp"


Map::Map(QWidget *parent) : QWidget(parent) {
    game = (GameMaster*)parent;

    setMinimumWidth(300); //optional

}

void Map::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    int TileType;


    //This Double Loop goes through the hole MapVector. (Row per Row)
    //And to Paint the Map
    for (int y = 0; y < game->mapHeight; ++y) {
        for(int x = 0; x < game->mapWidth; ++x) {



            TileType = game->worldMap[y * game->mapWidth +x];

            if (TileType == 1) {
                painter.setBrush(Qt::red);
            }

            else if (TileType == 2) {

                painter.setBrush(Qt::yellow);
            }
            else if (TileType == 3) {

                painter.setBrush(Qt::green);
            }
            else if (TileType == 4) {

                painter.setBrush(QColor(128, 0, 128));		//Purple
            }
            else if (TileType == 0) {
                painter.setBrush(QColor(102, 51, 0));		//bROWN
            }

            painter.drawRect(x * game->TileSizeX, y * game->TileSizeY, game->TileSizeX, game->TileSizeY); // (xpos, ypos,
        }				// xlength, ylength)
    }


    //drawing the Player
    painter.setBrush(Qt::yellow);
    painter.drawRect
    (game->player.getPlayerPosX() * game->TileSizeX, game->player.getPlayerPosY() * game->TileSizeY,
     game->player.getPlayerSize(), game->player.getPlayerSize());


    // Visiulizing the Viewfield of the Player.
    for(float RayAngel = -30; RayAngel <= 30; RayAngel= RayAngel + 0.1) {
        dda Ray = game->calculateWallHit(RayAngel *2 *M_PI / 360);		//Changing deg in Rad for dda Algorithm!

        //Drawing the Ray
        painter.drawLine(Ray.RayStartX *game->TileSizeX,
                         Ray.RayStartY*game->TileSizeY,
                         Ray.RayEndX*game->TileSizeX,
                         Ray.RayEndY*game->TileSizeY );
    }
}

