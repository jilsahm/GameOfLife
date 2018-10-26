#include "cells.h"

Cells::Cells(const size_t rows, const size_t columns)
    : rows       {rows},
      columns    {columns},
      size       {rows * columns},
      population (size, false)
{
    this->initialPopulation();
}

void Cells::initialPopulation(){
    QRandomGenerator *rnd = QRandomGenerator::system();

    std::for_each(this->population.begin(), this->population.end(), [&rnd](bool & cell){
        if (rnd->generate() < 1000000000u){
            cell = true;
        }
    });
}
