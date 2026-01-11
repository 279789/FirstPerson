#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>
#include<chrono> // For Time
#include<thread> // for using the other cpu cores


class MapTile {
	private:
		sf::Vector2f TilePosition;
		int Xcoordinate;
		int Ycoordinate;
		float Tilesize;
		int Type;
	public:
		
		
		MapTile(int x, int y, int size, int type, sf::Vector2f tileposition) :
		       	Xcoordinate(x), Ycoordinate(y), Tilesize(size), Type(type), TilePosition(tileposition) {}
		int getX() const {return Xcoordinate;}
		int getY() const {return Ycoordinate;}
		float getTilesize() const {return Tilesize;}
		int getType() const {return Type;}
		sf::Vector2f getTilePosition() const {return TilePosition;}

};
/*
class Map {
	private:
		std::vector<std::unique_ptr<MapTile>> map;
	
	public:
	
	Map() {	
	
		int Grid[10][10] = {
    			{1,1,1,1,1,1,1,1,1,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,1,1,1,1,1,1,1,1,1}
			};
		for(int x = 0; x < 10; x++) {
			for(int y = 0; y < 10; y++) {
			map.push_back(std::make_unique<MapTile>(x, y, 10, Grid[x][y]));	
			}
		}


	}
};
*/
int main () {

	// create the window
	sf::RenderWindow window(sf::VideoMode({800, 600}), "FirstPerson");
	const std::chrono::milliseconds minframeTime(16); //frameTime for 60Hz
	float TileSize = 50; //Size of one Tile
	std::vector<MapTile> walls;


	sf::Vector2f PlayerPos{2*TileSize, 2*TileSize};
	sf::RectangleShape Player ({TileSize, TileSize});
	Player.setFillColor(sf::Color::Green);
	Player.setPosition(PlayerPos); 
	int StopMovement = 0;
	
	
	//TEst quadrat
	//sf::RectangleShape quadrat({100.f, 100.f});
	//quadrat.setFillColor(sf::Color::Red);
	//quadrat.setPosition(sf::Vector2f{200.f, 150.f});

		std::vector<std::unique_ptr<MapTile>> map;
		int Grid[10][10] = {
    			{1,1,1,1,1,1,1,1,1,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,0,1,0,0,0,0,0,0,1},
    			{1,0,0,0,0,0,0,0,0,1},
    			{1,1,1,1,1,1,1,1,1,1}
			};
		for(int x = 0; x < 10; x++) {
			for(int y = 0; y < 10; y++) {
			map.push_back(std::make_unique<MapTile>(x, y, TileSize, Grid[y][x], 
					sf::Vector2f{TileSize * static_cast<float>(x) , TileSize * static_cast<float>(y)}));	
			}
		}
	
	std::vector<sf::RectangleShape> mapConstruct;
	for(auto& TilePtr : map) {
		const MapTile& Tile = *TilePtr; //dereferenzierung, da nur pointer
		if(Tile.getType()) walls.push_back(Tile);
		sf::RectangleShape quadrat(sf::Vector2f(Tile.getTilesize(), Tile.getTilesize()));
		if(Tile.getType()) quadrat.setFillColor(sf::Color::Red);
		else quadrat.setFillColor(sf::Color::Blue);
		quadrat.setPosition(Tile.getTilePosition());
		mapConstruct.push_back(quadrat);
	}



	//run as long as the window is open
	while (window.isOpen()){ 
		//Takes Time before calculating the frame
		auto startframeTime = std::chrono::high_resolution_clock::now();
			
		while (const std::optional event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>())
				window.close();
		}

		window.clear(sf::Color::Black);

		//draw here
	
		for(auto& quadrat : mapConstruct) {
		window.draw(quadrat);
		}
		
		//Player Movement
		for(auto Wall : walls){					//Das muss gefixt werden (über Hitboxes)
			if(PlayerPos == Wall.getTilePosition()) {
			StopMovement = 1;
			}
		//	else if (PlayerPos.y == Wall.getTilePosition().y){
		//	StopMovement = 1;
		//	}	
			}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && !StopMovement){
		PlayerPos.y -= 1.0f;
		}
		
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)){
		PlayerPos.x -= 1.0f;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)){
		PlayerPos.y += 1.0f;
		}

		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)){
		PlayerPos.x += 1.0f;
		}

		Player.setPosition(PlayerPos); 
		window.draw(Player);

		//Takes Time at the end of the frame
		auto endframeTime = std::chrono::high_resolution_clock::now();
		auto frameTime = endframeTime - startframeTime;
		if (frameTime < minframeTime) {
			std::this_thread::sleep_for(minframeTime - frameTime);
		}

			//end of frame

		window.display();
	}


return 0;

}
