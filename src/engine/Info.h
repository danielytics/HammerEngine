#ifndef INFO_H
#define INFO_H

class Logger;

class Info
{
private:
    int numProcessors;
    bool flagMMX, flag3DNow, flagSSE, flagSSE2, flagSSE3;

public:
    Info();

    inline int numberOfProcessors () const  {return numProcessors;}
    inline bool hasMMX () const             {return flagMMX;}
    inline bool has3DNow () const           {return flag3DNow;}
    inline bool hasSSE () const             {return flagSSE;}
    inline bool hasSSE2 () const            {return flagSSE2;}
    inline bool hasSSE3 () const            {return flagSSE3;}

    void writeToLog (Logger* logger) const;
};

#endif // INFO_H
