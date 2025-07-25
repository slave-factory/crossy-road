
#include <iostream> 
#include <SFML/Graphics.hpp>
#include <random>
#include "map/Block.hpp"
#include "map/Mapping.hpp"

void Mapping::mapping(sf::RenderWindow& window, Block& block, const sf::Vector2f& base) {


    
    float tileW = block.getLen();
    float tileH = block.getLen(); 

    

    for (int z = 0; z <= MAX_Z; ++z) {
        for (int y = 1 + mapFreespace; y < Mapping::MAPLEN - 1 + mapFreespace; ++y) {
            for (int x = 1 + mapFreespace; x < Mapping::MAPLEN - 1 - mapFreespace; ++x) {
                if(mapTile[z][y][x]) {
                    // 등각 투영 변환 + 높이 보정
                    float screenX = base.x + (x - y) * tileW;
                    float screenY = base.y + (x + y) * tileH - z * tileH*0.75; // z 높이만큼 위로 올림

                    sf::Vector2f pos(screenX, screenY);
                    block.draw(window, pos, mapTile[z][y][x]);

                }
                     
                    
                
            }
        }
    }



    
}


void Mapping::initMap() {
    static int temp[Mapping::MAX_Z][Mapping::MAPLEN + 2*mapFreespace][Mapping::MAPLEN + 2*mapFreespace] = {};
    std::random_device rd;                   
    std::mt19937 gen(rd());                    
    std::uniform_int_distribution<> dist(1, 10); 
    for(int i=0; i<= MAPLEN + 2*mapFreespace; i++) {
        int bottomValue = dist(gen);
        for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j)
            temp[0][i][j] = (bottomValue <= 7 ? 1 : 0);

        for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j)
            temp[0][i][j] = (bottomValue <= 5 ? 2 : 1);

        for(int t = 1; t < 5; ++t) {
            for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j) {
                if(t == 0) {
                    if(dist(gen) <= 3) {
                        temp[t][i][j] = 1;
                    }
                }
                else {
                    if(dist(gen) <= 3 && temp[t-1][i][j]) {
                        temp[t][i][j] = 1;
                    }
                }
                
            }
        }

    }
    

    
    for(int t = 0; t < 5; ++t)
        for (int i = 0; i < MAPLEN + mapFreespace * 2; ++i)
            for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j)
                mapTile[t][i][j] = temp[t][i][j];
}

void Mapping::mapMove(int dir) {

    // 뒤
    if(dir == 1) {
        for(int t = 0; t < 5; ++t) {
            for (int i = 0; i < MAPLEN-1 + mapFreespace * 2; ++i) {
                for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j) {
                    mapTile[t][i][j] = mapTile[t][i+1][j];
                }
            }
        }
    }
    // 앞
    if(dir == 2) {
        
        std::random_device rd;                     // 하드웨어 엔트로피
        std::mt19937 gen(rd());                    // Mersenne Twister 엔진
        std::uniform_int_distribution<> dist(1, 10); // 1~10 난수

        int bottomValue = dist(gen);
        for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j)
            mapTile[0][0][j] = (bottomValue <= 7 ? 1 : 0);

        for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j)
            mapTile[0][0][j] = (bottomValue <= 5 ? 2 : 1);

        for (int t = 1; t < 5; ++t) {
            for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j) {
                if (dist(gen) <= 3 && mapTile[t - 1][0][j] == 1) {
                    mapTile[t][0][j] = 1;
                }
            }
        }



        for (int t = 0; t < 5; ++t) {
            for (int i = MAPLEN - 1 + mapFreespace * 2; i >= 0; --i) {
                for (int j = 0; j < MAPLEN + mapFreespace * 2; ++j) {
                    if (i == 0) {
                        mapTile[t][i][j] = 0; // 또는 다른 초기값
                    } else {
                        mapTile[t][i][j] = mapTile[t][i - 1][j];
                    }
                }
            }
        }

                
    }
    //왼
    if(dir == 3) {
        for(int t = 0; t < 5; ++t) {
            for (int i = 0; i < MAPLEN + mapFreespace*2; ++i) {
                for (int j = 0; j < MAPLEN - 1 + mapFreespace*2; ++j) {
                    mapTile[t][i][j] = mapTile[t][i][j+1];
                }
            }
        }
    }
    

    //오른
    if(dir == 4) {
        for(int t = 0; t < 5; ++t) {
            for (int i = 0; i < MAPLEN + mapFreespace*2; ++i) {
                for (int j = MAPLEN - 1 + mapFreespace*2; j >= 0; --j) {
                    mapTile[t][i][j] = mapTile[t][i][j-1];
                }
            }
        }
    }
}