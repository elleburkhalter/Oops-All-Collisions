
#ifndef STATISTICSINTERFACE_H
#define STATISTICSINTERFACE_H

// This will be the abstract base class responsible for providing
// an interface for a statistics callback (i.e. track the program
// statistics with LoggingStatistics or use a NullStatistics to turn it off).

class StatisticsInterface
{
public:
    virtual ~StatisticsInterface() = default;

    // I haven't decided what to put in here yet. ~L
};

#endif //STATISTICSINTERFACE_H
