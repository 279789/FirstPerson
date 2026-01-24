#include<QtCore>
#include<QtGui>
#include<vector>
#include<cmath>

struct dda {
	float RayStartX = 0;
	float RayStartY = 0;
	float RayEndX = 0;
	float RayEndY = 0 ;
	float Raylength = 0;
	bool HorizontalHit = false;
	bool VerticalHit = false;
};


class Player {

	private:
		
		float PlayerPosX;
		float PlayerPosY;
		float PlayerSize;
		float DirectionAngle;
		float DirectionLength;
	public:
	
	Player() {
	
	//Position relative to Tiles	
		PlayerPosX = 6;
		PlayerPosY = 5;
	
	
		PlayerSize = 10;
		
		DirectionAngle = 0;   // Important for Mouse Integration
		DirectionLength = 25;
 
	}

	void changePlayerPosX(float newPlayerPosX){
	       PlayerPosX = newPlayerPosX;
	}


	void changePlayerPosY(float newPlayerPosY){
	       PlayerPosY = newPlayerPosY;
	}

	void increasePlayerAngle(float AngleIncreasement){
		
			DirectionAngle += ((AngleIncreasement *2 * M_PI) / 360);		
	
	}	
	
void movePlayerRelativeToRotationAngle(char Direction,char Slider , float Distance) {
if(Slider == 'X') {
		if(Direction == 'W'){
				
			PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle);
		}

		if(Direction == 'A'){
		
			PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI / 2);
		}
		
		if(Direction == 'S'){
		
			PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI);
		}
		
		if(Direction == 'D'){
		
			PlayerPosX = PlayerPosX + Distance * std::sin(DirectionAngle + M_PI * 3 / 2);
		}
}



if(Slider == 'Y') {
		if(Direction == 'W'){
				
			PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle);
		}

		if(Direction == 'A'){
		
			PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI / 2);
		}
		
		if(Direction == 'S'){
		
			PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI );
		}
		
		if(Direction == 'D'){
		
			PlayerPosY = PlayerPosY + Distance * std::cos(DirectionAngle + M_PI * 3 / 2 );
		}
}




}
		
	float getPlayerPosX(){
	       return PlayerPosX;
	}

	float getPlayerPosY(){
	       return PlayerPosY;
	}

	float getDirectionAngle(){
	       return DirectionAngle;
	}

	float getDirectionLength(){
	       return DirectionLength;
	}

	float getPlayerSize(){
	       return PlayerSize;
	}

};
class MapWidget : public QWidget {
	
	private:
		std::vector<int> worldMap;
		int mapWidth;
		int  mapHeight;	

		int TileSizeX;
		int TileSizeY;
		
		Player player;
	
		bool wPressed;
		bool aPressed;
		bool sPressed;
		bool dPressed;
		bool leftPressed;
		bool rightPressed;
	
	public:
		MapWidget(){

			resize(600, 600);
			setWindowTitle("MapTest");
			
			mapWidth = 10;
			mapHeight = 10;
			worldMap = {
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
				1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
				1, 0, 0, 0, 0, 0, 1, 1, 0, 1,
				1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
				1, 1, 1, 1, 1, 1, 1, 1, 1, 1
			        };


		wPressed = false;
		aPressed = false;
		sPressed = false;
		dPressed = false;
		leftPressed = false;
		rightPressed = false;

		QTimer *timer = new QTimer(this);			//declareing a timer
		timer->start(16);					//16ms for 60Hz
		connect(timer, &QTimer::timeout, this, &MapWidget::SuperLoop); 	//when timer run down, call SuperLoop
	
		}	


	int getTileSizeX(){
	       return TileSizeX;
	}

	int getTileSizeY(){
	       return TileSizeY;
	}



		void SuperLoop() {
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
	
		player.movePlayerRelativeToRotationAngle( 'W', 'X' , travelDistance);
		
		}

		//check y (using old x)
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] 
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {
	
		player.movePlayerRelativeToRotationAngle( 'W', 'Y' , travelDistance);
		
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
	
		player.movePlayerRelativeToRotationAngle( 'A', 'X' , travelDistance);
		
		}

		//check y (using old x)
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] 
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {
	
		player.movePlayerRelativeToRotationAngle( 'A', 'Y' , travelDistance);
		
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
	
		player.movePlayerRelativeToRotationAngle( 'S', 'X' , travelDistance);
		
		}

		//check y (using old x)
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] 
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {
	
		player.movePlayerRelativeToRotationAngle( 'S', 'Y' , travelDistance);
		
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
	
		player.movePlayerRelativeToRotationAngle( 'D', 'X' , travelDistance);
		
		}

		//check y (using old x)
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] 
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		
		&& !worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX()  + hitBoxLength)]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)* mapWidth +static_cast<int>(player.getPlayerPosX() + hitBoxLength)]) {
	
		player.movePlayerRelativeToRotationAngle( 'D', 'Y' , travelDistance);
		
		}


	}
	
	
	
	
	if(leftPressed) {
			
		player.increasePlayerAngle(2);
	}

	if(rightPressed) {

		player.increasePlayerAngle(-2);

		}


		update();
		}

		
	
		
	
	protected:
		void paintEvent(QPaintEvent *event) override {
			QPainter painter(this);

			//Tilesize
			TileSizeX = 50;
			TileSizeY = 50;

			//drawing the map
			for (int y = 0; y < mapHeight; ++y) {
				for(int x = 0; x < mapWidth; ++x) {
					//Finding the right tile
					int Tile = worldMap[y * mapWidth +x];

					if (Tile == 1) {
						painter.setBrush(Qt::red);
					}
					else {
						painter.setBrush(Qt::green); 
						}

					painter.drawRect(x * TileSizeX, y * TileSizeY, TileSizeX, TileSizeY); // (xpos, ypos, 
						}				// xlength, ylength)
			}

			//drawing the Player 
			painter.setBrush(Qt::yellow);
			painter.drawRect
			(player.getPlayerPosX() * TileSizeX, player.getPlayerPosY() * TileSizeY, 
			 player.getPlayerSize() , player.getPlayerSize());

		
		
		float PlayerCenterPosX = player.getPlayerPosX() * TileSizeX + player.getPlayerSize()/2;
		float PlayerCenterPosY = player.getPlayerPosY() * TileSizeY + player.getPlayerSize()/2;
		
		//Attention! The PlayerCernterPos needs to be added to the Direction Pointer !!! 
		//Other wise the Direction Pointer Points from 

		float DirectionEndX = player.getDirectionLength() *  std::sin(player.getDirectionAngle()) + PlayerCenterPosX ; 
		float DirectionEndY = player.getDirectionLength() *  std::cos(player.getDirectionAngle()) + PlayerCenterPosY ;
			//std::sqrt(player.getDirectionLength() * player.getDirectionLength()
			//	- DirectionEndY * DirectionEndY);



		//drawing Direction Vektor
			painter.drawLine(PlayerCenterPosX,
			PlayerCenterPosY,
			DirectionEndX,
		       	DirectionEndY);
		
		// Does calculate several data sets of the Wallcolision for later drawing the wall
		for(float RayAngel = -60; RayAngel <= 60; RayAngel= RayAngel + 0.1) {
		dda Ray = calculateWallHit(RayAngel);
			
			painter.drawLine(Ray.RayStartX *TileSizeX,
			Ray.RayStartY*TileSizeY,
			Ray.RayEndX*TileSizeX,
		       	Ray.RayEndY*TileSizeY );
		}




	}

	void keyPressEvent(QKeyEvent *event) override {

		
		
	if(event->key() == Qt::Key_W) wPressed = true; 
	if(event->key() == Qt::Key_A) aPressed = true;
	if(event->key() == Qt::Key_S) sPressed = true;
	if(event->key() == Qt::Key_D) dPressed = true;
	if(event->key() == Qt::Key_Left) leftPressed = true;
	if(event->key() == Qt::Key_Right) rightPressed = true;
}
	void keyReleaseEvent(QKeyEvent *event) override {
	
	if(event->key() == Qt::Key_W) wPressed = false; 
	if(event->key() == Qt::Key_A) aPressed = false;
	if(event->key() == Qt::Key_S) sPressed = false;
	if(event->key() == Qt::Key_D) dPressed = false;
	if(event->key() == Qt::Key_Left) leftPressed = false;
	if(event->key() == Qt::Key_Right) rightPressed = false;
	
	
	}
	
	dda calculateWallHit(float RayAngel) {
		
		dda Ray; 
		
		RayAngel =  (RayAngel *2 *M_PI / 360);

		//Middle of the Player
		Ray.RayStartX = player.getPlayerPosX() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;
		Ray.RayStartY = player.getPlayerPosY() + player.getPlayerSize()/(2*static_cast<float>(TileSizeX)) ;
		
		//Direction Vector of the Player (Verhältnis)
		float rayDirectionX = std::sin(player.getDirectionAngle()+RayAngel);
		float rayDirectionY = std::cos(player.getDirectionAngle()+RayAngel);

		//In which Tile the Player is.
		int TileX = static_cast<int>(Ray.RayStartX);
		int TileY = static_cast<int>(Ray.RayStartY);

		// Calculation of the x distance for movement of 1 in y direction. (Betrag) cause distance is not negative if angel is.
		float edgeDistanceX = std::abs(1 / rayDirectionX);
		float edgeDistanceY = std::abs(1 / rayDirectionY);

		//Actual length of the Ray (but not final length
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
			else{
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
					Ray.Raylength= sideDistanceY;
				}
		hit = false;
//Does change the sideDistanceX (length of actual Ray) into only X with the Hyp/X ratio rayDirection.

		Ray.RayEndX = Ray.RayStartX  + rayDirectionX * Ray.Raylength; 
		Ray.RayEndY = Ray.RayStartY  + rayDirectionY * Ray.Raylength; 
return Ray;	
	
	
	
	
	
	}

};



int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MapWidget window;
	window.show();

	return app.exec();
}
