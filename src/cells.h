#ifndef CELLS_H
#define CELLS_H

#include <QRandomGenerator>

#include <vector>

using std::vector;

class Cells
{
public:
    Cells(const size_t, const size_t);

private:
    void initialPopulation();

    const size_t rows;
    const size_t columns;
    const size_t size;
    vector<bool> population;
};

#endif // CELLS_H
