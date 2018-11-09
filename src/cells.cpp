#include "cells.h"

Cells::Cells(const size_t rows, const size_t columns)
    : rows             {rows},
      columns          {columns},
      size             {rows * columns},
      idealThreadCount {static_cast<unsigned int>(QThread::idealThreadCount())},
      population       (size, 0),
      buffer           (size, 0)
{
    this->initialPopulation();
}

void Cells::update(){
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    vector<std::thread> threadgroup {};
    const size_t        rowPack {this->rows / this->idealThreadCount};
    size_t              startingRow {0};

    for (unsigned int currentThread = 0; currentThread < this->idealThreadCount; currentThread++){
        threadgroup.push_back(std::thread {&Cells::partitionUpdate, this, startingRow, startingRow + rowPack });
        startingRow += rowPack;
    }
    for (auto &thread : threadgroup){
        thread.join();
    }

    qInfo() << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - starttime << " milliseconds for updating the buffer.";
    this->commit();
}

void Cells::partitionUpdate(size_t startingRow, size_t endingRow){
    size_t lastColumn {this->columns - 1};
    size_t lastRow {this->rows - 1};

    for (; startingRow < endingRow; startingRow++){
        for (size_t column = 0; column < this->columns; column++){
            short  neighbours  {0};
            size_t ownPosition {column + startingRow * this->columns};

            size_t northwest (ownPosition - 1 - this->columns);
            size_t north     (ownPosition - this->columns);
            size_t northeast (ownPosition + 1 - this->columns);
            size_t southwest (ownPosition - 1 + this->columns);
            size_t south     (ownPosition + this->columns);
            size_t southeast (ownPosition + 1 + this->columns);

            //Northwest
            if (column > 1 && startingRow > 0 && this->population[northwest] == 1) neighbours++;
            //North
            if (startingRow > 0 && this->population[north] == 1) neighbours++;
            //Northeast
            if (column < lastColumn && startingRow > 0 && this->population[northeast] == 1) neighbours++;

            //West
            if (column > 0 && this->population[ownPosition - 1] == 1) neighbours++;
            //East
            if (column < lastColumn && this->population[ownPosition + 1] == 1) neighbours++;

            //Southwest
            if (column > 0 && startingRow < lastRow && this->population[southwest] == 1) neighbours++;
            //South
            if (startingRow > 0 && startingRow < lastRow && this->population[south] == 1) neighbours++;
            //Southeast
            if (column < lastColumn && startingRow < lastRow && this->population[southeast] == 1) neighbours++;

            if (neighbours == 3){
                this->buffer[ownPosition] = 1;
            } else if (neighbours > 3 || neighbours < 2 ){
                this->buffer[ownPosition] = 0;
            }
        }
    }
}

void Cells::commit(){
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    vector<std::thread> threadgroup  {};
    const size_t        cellPack     {this->size / this->idealThreadCount};
    size_t              startingCell {0};

    for (unsigned int currentThread = 0; currentThread < this->idealThreadCount; currentThread++){
        threadgroup.push_back(std::thread {&Cells::partitionCommit, this, startingCell, startingCell + cellPack });
        startingCell += cellPack;
    }
    for (auto &thread : threadgroup){
        thread.join();
    }

    qInfo() << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - starttime << " milliseconds for commiting changes.";
}

void Cells::partitionCommit(size_t start, size_t end){
    for (; start < end; start++){
        this->population[start] = this->buffer[start];
    }
}

void Cells::initialPopulation(){
    QRandomGenerator *rnd = QRandomGenerator::system();    
    for (auto &cell : this->population){
        if (rnd->generate() % 3 == 0){
            cell = 1;
        }
    }
}
