#ifndef CELLS_H
#define CELLS_H

#include <QDebug>
#include <QRandomGenerator>

#include <chrono>
#include <mutex>
#include <vector>

using std::lock_guard;
using std::mutex;
using std::vector;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class Cells
{
public:
    Cells(const size_t, const size_t);
    void update();
    //uint_fast8_t getCell(const size_t column, const size_t row) const { return this->population.at(column + row * this->columns); }
    uint_fast8_t getCell(const size_t column, const size_t row) const { return this->population.at(row).at(column); }

private:
    void commit();
    void initialPopulation();

    const size_t rows;
    const size_t columns;
    const size_t size;
    //vector<uint_fast8_t> population;
    //vector<uint_fast8_t> buffer;

    vector<vector<uint_fast8_t>> population;
    vector<vector<uint_fast8_t>> buffer;
};

#endif // CELLS_H
