#include "map.h"

    Map::Map(sf::String filename, sf::String tilesetFileName, sf::RenderWindow * window){

        this->window = window;

        tilesetImg.loadFromFile("images/"+tilesetFileName);
        tilesetText.loadFromImage(tilesetImg);
        tilesetSprite.setTexture(tilesetText);

        mapfile.open("maps/"+filename+".tmap",std::ifstream::out | std::ifstream::app);

        if(!mapfile.is_open()){
        std::cerr << "Failed to load file!" << std::endl;
        exit(1);
        }




         mapfile.seekg(0,std::iostream::beg);

         std::getline(mapfile,median_string);
         layer = median_string;

         width = layer.getSize();

         height=1;

         while(!mapfile.eof()){
             layer.clear();
             std::getline(mapfile,median_string);
             layer = median_string;
             if(layer.getSize()!=width)
             {
                 std::cerr << "width of map isn't constant!" << std::endl;
                 exit(1);
             }
             width = layer.getSize();
             height++;
         }

         charmap = (char **)malloc(sizeof(char *)*width);

         for(int i = 0; i < width; i++) {
            charmap[i] = (char *)malloc(sizeof(char)*height);
         }
        mapfile.seekg(0,std::iostream::beg);
         for(int j = 0; j < height; j++) {
             std::string buf;
             std::getline(mapfile,buf);
             for(int i = 0; i < width; i++){
                charmap[i][j] = buf[i];
             }
         }


    }

   void Map::update(){
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height;j++){
        if(charmap[i][j]=='_')
            tilesetSprite.setTextureRect(sf::IntRect(TILE_SIZE*0,0,TILE_SIZE,TILE_SIZE));
        if(charmap[i][j]=='h')
            tilesetSprite.setTextureRect(sf::IntRect(TILE_SIZE*1,0,TILE_SIZE,TILE_SIZE));
        if(charmap[i][j]=='v')
            tilesetSprite.setTextureRect(sf::IntRect(TILE_SIZE*2,0,TILE_SIZE,TILE_SIZE));

        tilesetSprite.setPosition(TILE_SIZE*i,TILE_SIZE*j);

        window->draw(tilesetSprite);
    }

   }

    char Map::tileTypeXY(float x, float y) {
        return charmap[(int)(x/TILE_SIZE)][(int)(y/TILE_SIZE)];
    }

