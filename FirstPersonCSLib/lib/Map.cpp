#include"Map.hpp"
#include"GameMaster.hpp"


	Map:: Map(QWidget *parent) : QWidget(parent) {
        game = (GameMaster*)parent;

        setMinimumWidth(300); //optional

    }

	void Map::paintEvent(QPaintEvent *event){
        QPainter painter(this);

        //drawing the map
        for (int y = 0; y < game->mapHeight; ++y) {
            for(int x = 0; x < game->mapWidth; ++x) {
                //Finding the right tile
                int Tile = game->worldMap[y * game->mapWidth +x];

                if (Tile == 1) {
                    painter.setBrush(Qt::red);
                }
                
		else if (Tile == 2) {

                    painter.setBrush(Qt::yellow);
				}
		else if (Tile == 3) {
		
                    painter.setBrush(Qt::green);
			}
		else if (Tile == 4) {

                    painter.setBrush(QColor(128, 0, 128));		//Purple
			}
		else if (Tile == 0) {
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



        float PlayerCenterPosX = game->player.getPlayerPosX() * game->TileSizeX + game->player.getPlayerSize()/2;
        float PlayerCenterPosY = game->player.getPlayerPosY() * game->TileSizeY + game->player.getPlayerSize()/2;

        //Attention! The PlayerCernterPos needs to be added to the Direction Pointer !!!
        //Other wise the Direction Pointer Points from

        float DirectionEndX = game->player.getDirectionLength() *  std::sin(game->player.getDirectionAngle()) + PlayerCenterPosX ;
        float DirectionEndY = game->player.getDirectionLength() *  std::cos(game->player.getDirectionAngle()) + PlayerCenterPosY ;
        //std::sqrt(player.getDirectionLength() * player.getDirectionLength()
        //	- DirectionEndY * DirectionEndY);



        //drawing Direction Vektor
        painter.drawLine(PlayerCenterPosX,
                         PlayerCenterPosY,
                         DirectionEndX,
                         DirectionEndY);


        // Does calculate several data sets of the Wallcolision for later drawing the wall
        for(float RayAngel = -30; RayAngel <= 30; RayAngel= RayAngel + 0.1) {
            dda Ray = game->calculateWallHit(RayAngel *2 *M_PI / 360);

            //imlementing Tilesize into function!!!
            painter.drawLine(Ray.RayStartX *game->TileSizeX,
                             Ray.RayStartY*game->TileSizeY,
                             Ray.RayEndX*game->TileSizeX,
                             Ray.RayEndY*game->TileSizeY );
        }




    }

