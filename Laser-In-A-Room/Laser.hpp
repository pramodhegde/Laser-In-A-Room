//
//  Laser.hpp
//  Laser-In-A-Room
//
//  Created by Pramod Hegde on 12/29/13.
//  Copyright (c) 2013 Pramod Hegde. All rights reserved.
//

#ifndef Laser_In_A_Room_Laser_hpp
#define Laser_In_A_Room_Laser_hpp
#include "Cell.hpp"

typedef std::map<Directions,CellCoordinates> TableForDirection;
class Laser {
    TableForDirection table_;
    CellCoordinates currentCoordinates_;
    Directions directionToGo_;
    
    void createTable(void);
    CellCoordinates getNewCoordinates(Directions const direction);
    
public:
    Laser(CellCoordinates startCoordinate)
    : currentCoordinates_(startCoordinate)
    , directionToGo_(Directions::Right)
    {
        createTable();
    }
    
    const CellCoordinates moveNext(Cell& currentCell);
    
};


#endif
