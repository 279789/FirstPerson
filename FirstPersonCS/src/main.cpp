#include<QtCore>
#include<QtGui>
#include<vector>
class Player {

	private:
		
		float PlayerPosX;
		float PlayerPosY;
		float PlayerSize;

	public:
	
	Player() {
		
		PlayerPosX = 5;
		PlayerPosY = 5;
		PlayerSize = 10;
	}

	void changePlayerPosX(float newPlayerPosX){
	       PlayerPosX = newPlayerPosX;
	}


	void changePlayerPosY(float newPlayerPosY){
	       PlayerPosY = newPlayerPosY;
	}

	float getPlayerPosX(){
	       return PlayerPosX;
	}

	float getPlayerPosY(){
	       return PlayerPosY;
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
		QTimer *timer = new QTimer(this);			//declareing a timer
		timer->start(16);					//16ms for 60Hz
		connect(timer, &QTimer::timeout, this, &MapWidget::SuperLoop); 	//when timer run down, call SuperLoop
	
		}	
		void SuperLoop() {
		float Speed = 0.05f;
		float NextPlayerX;
		float NextPlayerY;
		float hitBoxLength = (player.getPlayerSize() / TileSizeX) -0.001 ; 


	if(wPressed) {
	 	NextPlayerY = player.getPlayerPosY() - 0.05f;

	
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] ) {
			player.changePlayerPosY(player.getPlayerPosY()-Speed);
		}
	
	}


	if(aPressed) {
	 	NextPlayerX = player.getPlayerPosX() - 0.05f;

	
		if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth + static_cast<int>(NextPlayerX)]
		&& !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)] ) {
			player.changePlayerPosX(player.getPlayerPosX()-Speed);
		}
	
	}


	if(sPressed) {
		NextPlayerY = player.getPlayerPosY() + 0.05f;

	
		if(!worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] ) {
		
			player.changePlayerPosY(player.getPlayerPosY()+Speed);
		}
	
	}



	if(dPressed) {
		NextPlayerX = player.getPlayerPosX() + 0.05f;

	
		if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
		&& !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)] ) {
		
			player.changePlayerPosX(player.getPlayerPosX()+Speed);
		}
	
	}


		update();
		}

		
	
		
	ssdsda
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
			(player.getPlayerPosX() * TileSizeX, player.getPlayerPosY() * TileSizeY ,player.getPlayerSize() , player.getPlayerSize());
	}

	void keyReleaseEvent(QKeyEvent *event) override {
	
	if(event->key() == Qt::Key_W) wPressed = false; 
	if(event->key() == Qt::Key_A) aPressed = false;
	if(event->key() == Qt::Key_S) sPressed = false;
	if(event->key() == Qt::Key_D) dPressed = false;
	
	
	}
	
	void keyPressEvent(QKeyEvent *event) override {

		
		
	if(event->key() == Qt::Key_W) wPressed = true; 
	if(event->key() == Qt::Key_A) aPressed = true;
	if(event->key() == Qt::Key_S) sPressed = true;
	if(event->key() == Qt::Key_D) dPressed = true;
		
		/*
		float NextPlayerX;
		float NextPlayerY;
		float hitBoxLength = (player.getPlayerSize() / TileSizeX) -0.001 ; 


	if(event->key() == Qt::Key_W) {
	 	/uNextPlayerY = player.getPlayerPosY() - 0.05f;

	
		if(!worldMap[static_cast<int>(NextPlayerY) * mapWidth +static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] ) {
			player.changePlayerPosY(player.getPlayerPosY()-0.1);
		}
	
	}


	if(event->key() == Qt::Key_A) {
	 	NextPlayerX = player.getPlayerPosX() - 0.05f;

	
		if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth + static_cast<int>(NextPlayerX)]
		&& !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)*mapWidth + static_cast<int>(NextPlayerX)] ) {
			player.changePlayerPosX(player.getPlayerPosX()-0.1);
		}
	
	}


	if(event->key() == Qt::Key_S) {
		NextPlayerY = player.getPlayerPosY() + 0.05f;

	
		if(!worldMap[static_cast<int>(NextPlayerY + hitBoxLength) * mapWidth + static_cast<int>(player.getPlayerPosX())]
		&& !worldMap[static_cast<int>(NextPlayerY + hitBoxLength)*mapWidth + static_cast<int>(player.getPlayerPosX() + hitBoxLength)] ) {
		
			player.changePlayerPosY(player.getPlayerPosY()+0.1);
		}
	
	}



	if(event->key() == Qt::Key_D) {
		NextPlayerX = player.getPlayerPosX() + 0.05f;

	
		if(!worldMap[static_cast<int>(player.getPlayerPosY()) * mapWidth +static_cast<int>( NextPlayerX + hitBoxLength)]
		&& !worldMap[static_cast<int>(player.getPlayerPosY() + hitBoxLength)* mapWidth +static_cast<int>(NextPlayerX + hitBoxLength)] ) {
		
			player.changePlayerPosX(player.getPlayerPosX()+0.1);
		}
	
	}
*/
}

};


int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	MapWidget window;
	window.show();

	return app.exec();
}
