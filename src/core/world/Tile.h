//
// Created by montgomery anderson on 18/07/17.
//

#ifndef RECLAIMER_TILE_H
#define RECLAIMER_TILE_H


struct Tile {
    int typeId;
    int x;
    int z;
    float y;

    Tile() : typeId(0), x(0), z(0), y(0.0) {}

    Tile(int typeId, int x, int z, float y)
            : typeId(typeId), x(x), z(z), y(y) {}

    bool operator=(Tile other) {
        typeId = other.typeId;
        x = other.x;
        z = other.z;
        y = other.y;
        return true;
    }


    template<class Archive>
    void serialize(Archive &ar, const unsigned int version) {
        ar & typeId;
        ar & x;
        ar & y;
        ar & z;
    }
};

BOOST_CLASS_VERSION(Tile, 0)

#endif //RECLAIMER_TILE_H
