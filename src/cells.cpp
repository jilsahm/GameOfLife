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
    size_t last {this->columns - 1};
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    /*
    for (size_t row = 0; row < this->rows; row++){
        for (size_t column = 0; column < this->columns; column++){
            short        neighbours {0};

            int_fast64_t northwest  {static_cast<int_fast64_t>(column - 1 + (row - 1) * this->columns)};
            int_fast64_t north      {static_cast<int_fast64_t>(column + (row - 1) * this->columns)};
            int_fast64_t northeast  {static_cast<int_fast64_t>(column + 1 + (row - 1) * this->columns)};
            int_fast64_t southwest  {static_cast<int_fast64_t>(column - 1 + (row + 1) * this->columns)};
            int_fast64_t south      {static_cast<int_fast64_t>(column + (row + 1) * this->columns)};
            int_fast64_t southeast  {static_cast<int_fast64_t>(column + 1 + (row + 1) * this->columns)};

            if (column > 0 && this->population[column + row * this->columns - 1] == 1)       neighbours++;
            if (column < last && this->population[column + row * this->columns + 1] == 1)    neighbours++;
            if (column > 1 && northwest >= 0 && this->population[northwest] == 1)            neighbours++;
            if (row > 0 && north >= 0 && this->population[north] == 1)                       neighbours++;
            if (column < last && northeast >= 0 && this->population[northeast] == 1)         neighbours++;
            if (column > 0 && southwest < this->rows && this->population[southwest] == 1)    neighbours++;
            if (row > 0 && south < this->rows && this->population[south] == 1)               neighbours++;
            if (column < last && southeast < this->rows && this->population[southeast] == 1) neighbours++;

            if (neighbours == 3){
                this->buffer[column + row * this->columns] = 1;
            } else if (neighbours > 3 || neighbours < 2 ){
                this->buffer[column + row * this->columns] = 0;
            }
        }
    }*/

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
    size_t last {this->columns - 1};

    for (; startingRow < endingRow; startingRow++){
        for (size_t column = 0; column < this->columns; column++){
            short        neighbours {0};

            int_fast64_t northwest  {static_cast<int_fast64_t>(column - 1 + (startingRow - 1) * this->columns)};
            int_fast64_t north      {static_cast<int_fast64_t>(column + (startingRow - 1) * this->columns)};
            int_fast64_t northeast  {static_cast<int_fast64_t>(column + 1 + (startingRow - 1) * this->columns)};
            int_fast64_t southwest  {static_cast<int_fast64_t>(column - 1 + (startingRow + 1) * this->columns)};
            int_fast64_t south      {static_cast<int_fast64_t>(column + (startingRow + 1) * this->columns)};
            int_fast64_t southeast  {static_cast<int_fast64_t>(column + 1 + (startingRow + 1) * this->columns)};

            if (column > 0 && this->population[column + startingRow * this->columns - 1] == 1)       neighbours++;
            if (column < last && this->population[column + startingRow * this->columns + 1] == 1)    neighbours++;
            if (column > 1 && northwest >= 0 && this->population[northwest] == 1)            neighbours++;
            if (startingRow > 0 && north >= 0 && this->population[north] == 1)                       neighbours++;
            if (column < last && northeast >= 0 && this->population[northeast] == 1)         neighbours++;
            if (column > 0 && southwest < this->rows && this->population[southwest] == 1)    neighbours++;
            if (startingRow > 0 && south < this->rows && this->population[south] == 1)               neighbours++;
            if (column < last && southeast < this->rows && this->population[southeast] == 1) neighbours++;

            if (neighbours == 3){
                this->buffer[column + startingRow * this->columns] = 1;
            } else if (neighbours > 3 || neighbours < 2 ){
                this->buffer[column + startingRow * this->columns] = 0;
            }
        }
    }
}

void Cells::commit(){
    auto starttime = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    for (size_t i = 0; i < this->size; i++){
        this->population[i] = this->buffer[i];
    }
    qInfo() << duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() - starttime << " milliseconds for commiting changes.";
}

void Cells::initialPopulation(){
    QRandomGenerator *rnd = QRandomGenerator::system();    
    for (auto &cell : this->population){
        if (rnd->generate() % 3 == 0){
            cell = 1;
        }
    }
}
