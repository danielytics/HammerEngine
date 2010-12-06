#include "Logger.h"

#include <iostream>

Logger::Logger()
{
}

void Logger::write (const LoggerLevel level)
{

}

LogStream::LogStream ()
{

}

LogStream& LogStream::operator << (const std::string& output)
{
    std::clog << output;
    return *this;
}

LogStream& LogStream::operator << (const unsigned int output)
{
    std::clog << output;
    return *this;
}

LogStream& LogStream::operator << (const double output)
{
    std::clog << output;
    return *this;
}

LogStream& LogStream::operator << (const char output)
{
    std::clog << output;
    return *this;
}
