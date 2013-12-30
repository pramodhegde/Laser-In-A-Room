//
//  Laser-In-A-Room.cpp
//  Laser-In-A-Room
//
//  Created by Pramod Hegde on 12/29/13.
//  Copyright (c) 2013 Pramod Hegde. All rights reserved.
//

#include <iostream>
#include <map>
#include <cstdlib>

#define NUMROWS 5
#define NUMCOLS 5

namespace
{
    enum Directions {
        Nowhere = 0,
        Left = 1,
        Up = 2,
        Right = 3,
        Down = 4
    };
    
    typedef std::pair<int16_t,int16_t> CellCoordinates;
    typedef std::map<Directions,CellCoordinates> TableForDirection;
    
    class Cell {
        CellCoordinates myCoordinates_;
        bool beenVisited_;
        const Directions myDirection_;
        
    public:
        Cell(int16_t x,int16_t y,Directions direction)
        : myCoordinates_(std::make_pair(x,y))
        , beenVisited_(false)
        , myDirection_(direction)
        {}
        
        bool getVisitStatus(void) const;
        Directions getDirection(void) const;
        CellCoordinates getCoordinates(void) const;
        void setVisited(void);
        
    };
    
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
    typedef std::map<CellCoordinates, Cell> Room;
    Room room;
}

namespace {
    
    bool Cell::getVisitStatus(void) const
    {
        return beenVisited_;
    }
    
    Directions Cell::getDirection(void) const
    {
        return myDirection_;
    }
    
    CellCoordinates Cell::getCoordinates(void) const
    {
        std::cout << "Visting cell (" << myCoordinates_.first << "," << myCoordinates_.second << "). ";
        return myCoordinates_;
    }
    
    void Cell::setVisited(void)
    {
        beenVisited_ = true;
    }
}
namespace  {
    
    void Laser::createTable(void)
    {
        table_.emplace(Directions::Left, std::make_pair(-1, 0));
        table_.emplace(Directions::Right, std::make_pair(1, 0));
        table_.emplace(Directions::Up, std::make_pair(0, 1));
        table_.emplace(Directions::Down, std::make_pair(0, -1));
    }
    
    CellCoordinates Laser::getNewCoordinates(Directions const direction)
    {
        TableForDirection::iterator offset = table_.find(direction);
        return std::make_pair(currentCoordinates_.first + offset->second.first,
                              currentCoordinates_.second + offset->second.second);
    }
    
    const CellCoordinates Laser::moveNext(Cell &currentCell)
    {
        if (currentCell.getVisitStatus()) {
            std::cerr << "You are in a loop" << std::endl;
            return std::make_pair(-1, -1);
        }
        currentCell.setVisited();
        currentCoordinates_ = currentCell.getCoordinates();
        directionToGo_ = ((currentCell.getDirection() == Directions::Nowhere) ?
                                                        directionToGo_ : currentCell.getDirection());
        std::cout << "Next Direction: " << directionToGo_ << std::endl;
        return getNewCoordinates(directionToGo_);
    }
}

namespace {
    
    
    void createRoom(uint32_t xMax, uint32_t yMax)
    {
        std::srand((unsigned int)std::time(0));
        for (int32_t x=0; x < xMax; ++x) {
            for (int32_t y=0; y < yMax; ++y) {
                room.emplace(std::make_pair(x, y), Cell(x, y, Directions(std::rand()%5)));
            }
        }
    }
    
    void play(void)
    {
        CellCoordinates startCoordinate(0,0);
        Laser laser(startCoordinate);
        CellCoordinates nextCoordinate = laser.moveNext(room.find(startCoordinate)->second);
        
        do {
            if ((0 > nextCoordinate.first || NUMROWS < nextCoordinate.first) ||
                (0 > nextCoordinate.second || NUMCOLS < nextCoordinate.second))
            {
                std::cerr << "You hit a wall!" << std::endl;
                return;
            }
            
            nextCoordinate = laser.moveNext(room.find(nextCoordinate)->second);
        } while ((-1 != nextCoordinate.first) || (-1 != nextCoordinate.second) );
    }
}

int main(int argc, const char * argv[])
{
    createRoom(NUMROWS, NUMCOLS);
    play();
    return 0;
}


