#ifndef INFO_H
#define INFO_H

class Logger;

class Info
{
private:
    int numProcessors;

public:
    Info();

    int numberOfProcessors () const;
    bool hasMMX () const;
    bool has3DNow () const;
    bool hasSSE () const;
    bool hasSSE2 () const;

    void writeToLog (Logger* logger) const;
};

#endif // INFO_H
