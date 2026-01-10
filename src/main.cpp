#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <memory>
#include <CLI/CLI.hpp>
#include <nlohmann/json.hpp>
#include <SFML/Graphics.hpp>
#include <filesystem>

class MapTile {
	private:
		int Xcoordinate;
		int Ycoordinate;
		int Tilesize;
		int Type;
	public:
		
		
		MapTile(int x, int y, int size, int type) : Xcoordinate(x), Ycoordinate(y), Tilesize(size), Type(type) {}
		int getX() const {return Xcoordinate;}
		int getY() const {return Ycoordinate;}
		int getTilesize() const {return Tilesize;}
		int getType() const {return Type;}

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
			map.push_back(std::make_unique<MapTile>(x, y, 50, Grid[y][x]));	
			}
		}

	std::vector<sf::RectangleShape> mapConstruct;
	for(auto& TilePtr : map) {
		const MapTile& Tile = *TilePtr; //dereferenzierung, da nur pointer
		sf::RectangleShape quadrat(sf::Vector2f(static_cast<float>(Tile.getTilesize()), static_cast<float>(Tile.getTilesize())));
		if(Tile.getType()) quadrat.setFillColor(sf::Color::Red);
		else quadrat.setFillColor(sf::Color::Blue);
		quadrat.setPosition(sf::Vector2f(Tile.getX() * Tile.getTilesize(), Tile.getY() * Tile.getTilesize()));
		mapConstruct.push_back(quadrat);
	}



	//run as long as the window is open
	while (window.isOpen()){ 
		
		// check all the windows events that were triggered since the last iteration
		while (const std::optional event = window.pollEvent()) {
			if(event->is<sf::Event::Closed>())
				window.close();
		}

		//clear the window black
		window.clear(sf::Color::Black);

		//draw here
	
		for(auto& quadrat : mapConstruct) {
		window.draw(quadrat);
		}
		//end of frame
		window.display();
	}


return 0;

}
