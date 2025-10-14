#include <iostream>
#include <random>

#define TOTAL_STICKERS 682
#define STICKERS_PER_PACK 5
#define PACK_PRICE 0.8

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

int main() {
    int album[TOTAL_STICKERS] = {};
    int numberOfOpenedPacks = 0;

    while(!isAlbumComplete(album)) {
        int* pack = openPack();
        numberOfOpenedPacks++;

        for (int i=0; i<STICKERS_PER_PACK; i++) {
            album[pack[i]] = 1;
        }
    }

    float totalCost = numberOfOpenedPacks * PACK_PRICE;
    
    std::cout << numberOfOpenedPacks << " packs were open\n";
    std::cout << "The total cost was " << totalCost << " pounds\n";
}
