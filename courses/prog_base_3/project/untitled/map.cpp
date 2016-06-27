#include "map.h"

    Map::Map(sf::String filename, sf::String tilesetFileName, sf::RenderWindow * window, char gStatus){

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

        mapfile.close();

        for(int i = 0; i < width; i++)
            for(int j = 0; j < height; j++)
                if(charmap[i][j] != 'e' && charmap[i][j] != 'h' && charmap[i][j] != 'v' && charmap[i][j] != '_')
                {
                    std::cerr << "illegal symbol in mapfile" << std::endl;
                    exit(1);
                }

        if(gStatus != GS_NEWGAME)
            for(int i = 0; i < width; i++)
                for(int j = 0; j < height; j++)
                    if(charmap[i][j] == 'e')
                        charmap[i][j] = '_';
    }

   void Map::update(){
    for(int i = 0; i < width; i++)
        for(int j = 0; j < height;j++){
        if(charmap[i][j]=='_' || charmap[i][j]=='e')
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
        char result = charmap[(int)(x/TILE_SIZE)][(int)(y/TILE_SIZE)];
        if(result == 'e')
            result = '_';
        return result;
    }

    int Map::getW(){
        return width;
    }

    int Map::getH(){
        return height;
    }
