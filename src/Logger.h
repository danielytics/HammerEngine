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
        LOG_INFO=0,
        LOG_WARN,
        LOG_ERROR,
        LOG_FATAL,
        LOG_DEBUG
    };

    void write (const LoggerLevel level, const LogStream& stream);
};

#endif // LOGGER_H
