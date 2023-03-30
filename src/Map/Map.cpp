#include "Map.h"

void Map::GenerateMapGraphics() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for(int j = 0; j < MAP_WIDTH; ++j) {
            //map.backLayerComponent.SetTileIndex(j, i, 5);
            switch(mapLayer.mapCollision.GetCollisionByCell(j, i)) {
                case MapCollisionType::ROOM_INTERIOR:
                    mapLayer.backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, 0);
                    break;
                case MapCollisionType::COLLISION:
                    mapLayer.backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, 4);
                    break;
                case MapCollisionType::ROOM_EXTERIOR:
                    mapLayer.backLayerComponent.SetTileIndex(j + MAP_X_OFFSET, i + MAP_Y_OFFSET, 14);
                    break;
                case MapCollisionType::PLATFORM:
                    break;
            }
        }
    }
    mapLayer.backLayerComponent.ReloadMap();
}