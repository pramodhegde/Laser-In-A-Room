//
//  Cell.hpp
//  Laser-In-A-Room
//
//  Created by Pramod Hegde on 12/29/13.
//  Copyright (c) 2013 Pramod Hegde. All rights reserved.
//

#ifndef Laser_In_A_Room_Cell_hpp
#define Laser_In_A_Room_Cell_hpp

#include <cstdint>
#include <utility>

enum Directions {
    Nowhere = 0,
    Left = 1,
    Up = 2,
    Right = 3,
    Down = 4
};

using CellCoordinates = std::pair<int16_t,int16_t>;

class Cell {
    CellCoordinates myCoordinates_;
    bool beenVisited_;
    const Directions myDirection_;
    
public:
    Cell(int16_t x,int16_t y,Directions direction)
    : myCoordinates_(std::make_pair(x,y))
    , beenVisited_(std::move(false))
    , myDirection_(std::move(direction))
    {}
    
    bool getVisitStatus(void) const;
    Directions getDirection(void) const;
    CellCoordinates getCoordinates(void) const;
    void setVisited(void);
    
};



#endif
