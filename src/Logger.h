#ifndef LOGGER_H
#define LOGGER_H

#include <string>

class LogStream
{
public:
    LogStream ();

    LogStream& operator << (const std::string& output);
    LogStream& operator << (const unsigned int output);
    LogStream& operator << (const signed int output);
    LogStream& operator << (const double output);
    LogStream& operator << (const char output);
};

class Logger
{
public:
    Logger();

    enum LoggerLevel {
        INFO=0,
        WARN,
        ERROR,
        FATAL,
        DEBUG
    };

    void write (const LoggerLevel level, const LogStream& stream);
};

#endif // LOGGER_H
