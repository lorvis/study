#ifndef MAP_H
#define MAP_H
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#define tilesize 32

class Map{

    sf::String layer;
    std::string median_string;
    std::ifstream mapfile;
    sf::Image tilesetImg;
    sf::Texture tilesetText;
    sf::Sprite tilesetSprite;
    sf::RenderWindow * window;
    int width;
    int height;
    bool verified = false;
public:
    Map(sf::String filename, sf::String tilesetFileName, sf::RenderWindow &window){

        this->window=&window;

        tilesetImg.loadFromFile("images/"+tilesetFileName);
        tilesetText.loadFromImage(tilesetImg);
        tilesetSprite.setTexture(tilesetText);

        mapfile.open("maps/"+filename+".tmap",std::ifstream::out | std::ifstream::app);
        if(!mapfile.is_open()){
        std::cerr << "Failed to load file!" << std::endl;
        exit(1);
        }

    }

    void update(){
        mapfile.seekg(0,mapfile.beg);
        height=0;
        while(!mapfile.eof()){
        layer.clear();
        std::getline(mapfile,median_string);
        layer = median_string;
        width = layer.getSize();
        if(!verified){
        if(height>0&&width!=(int)layer.getSize()){
        std::cerr << "width of map isn't constant!" << std::endl;

        exit(1);
        }
        verified = true;
        }

        for(int j = 0; j < width;j++){
        if(layer[j]==' ')
            tilesetSprite.setTextureRect(sf::IntRect(tilesize*0,0,tilesize,tilesize));
        if(layer[j]=='h')
            tilesetSprite.setTextureRect(sf::IntRect(tilesize*1,0,tilesize,tilesize));
        if(layer[j]=='v')
            tilesetSprite.setTextureRect(sf::IntRect(tilesize*2,0,tilesize,tilesize));

        tilesetSprite.setPosition(tilesize*j,tilesize*height);

        window->draw(tilesetSprite);



        }
        width = layer.getSize();
        height++;
        }

    bool checkForSolidTile(double x, double y){
    if((y/tilesize)*width)+x/tilesize)
    }


    }
};



#endif // MAP_H
