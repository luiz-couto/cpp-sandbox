#include <iostream>
#include <random>

#define TOTAL_STICKERS 682
#define STICKERS_PER_PACK 5
#define PACK_PRICE 0.8
#define NUMBER_OF_PLAYERS 10

int generateRandomSticker(int seedHelper) {
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist(0, TOTAL_STICKERS);

    return dist(mt);
}

int* openPack() {
    static int pack[STICKERS_PER_PACK] = {};
    for (int i=0; i<STICKERS_PER_PACK; i++) {
        pack[i] = generateRandomSticker(i);
    }
    return pack;
}

bool isAlbumComplete(int album[TOTAL_STICKERS]) {
    for (int i=0; i<TOTAL_STICKERS; i++) {
        if (album[i] == 0) {
            return false;
        }
    }
    return true;
}

bool isAnyAlbumComplete(int albums[NUMBER_OF_PLAYERS][TOTAL_STICKERS]) {
    for (int p=0; p<NUMBER_OF_PLAYERS; p++) {
        if (isAlbumComplete(albums[p])) {
            return true;
        }
    }
    return false;
}

void giveRepeatedStickerToAnotherPlayer(int currPlayer, int stickerNum, int albums[NUMBER_OF_PLAYERS][TOTAL_STICKERS]) {
    bool matchFound = false;
    for (int p=0; p<NUMBER_OF_PLAYERS; p++) {
        if (p == currPlayer) continue;
        int* albumPlayer = albums[p];
        
        for (int i=0; i<TOTAL_STICKERS; i++) {
            if (albumPlayer[stickerNum] == 0) {
                albumPlayer[stickerNum] = 1;
                matchFound = true;
                break;
            }
        }

        if (matchFound) break;
    }
}

int main() {
    int albums[NUMBER_OF_PLAYERS][TOTAL_STICKERS] = {};
    int numberOfOpenedPacksPerPlayer = 0;
    bool completed = false;

    while(!completed) {
        numberOfOpenedPacksPerPlayer++;
        for (int p=0; p<NUMBER_OF_PLAYERS; p++) {
            int* album = albums[p];
            int* pack = openPack();

            for (int i=0; i<STICKERS_PER_PACK; i++) {
                if (album[pack[i]] == 1) {
                   giveRepeatedStickerToAnotherPlayer(p, pack[i], albums);
                }
                album[pack[i]] = 1;
            }

            if (isAnyAlbumComplete(albums)) {
                completed = true;
                break;
            }
        }
    }

    float totalCost = numberOfOpenedPacksPerPlayer * PACK_PRICE;
    
    std::cout << numberOfOpenedPacksPerPlayer << " packs were open\n";
    std::cout << "The total cost was " << totalCost << " pounds\n";
}
