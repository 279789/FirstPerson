#include<QtCore>
#include<QtGui>
#include<vector>
#include<cmath>
class Player {

	private:
		
		float PlayerPosX;
		float PlayerPosY;
		float PlayerSize;
		float DirectionAngle;
		float DirectionLength;
	public:
	
	Player() {
		
		PlayerPosX = 5;
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
	

};


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MapWidget window;
	window.show();

	return app.exec();
}
