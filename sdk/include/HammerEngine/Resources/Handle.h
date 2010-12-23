#ifndef HAMMER_ENGINE_HANDLE__H_
#define HAMMER_ENGINE_HANDLE__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/Packed.h>

typedef unsigned int Handle; // {type,id}, type = 10bit, id=22bit

// Extract type from handle
#define HANDLE_TYPE(handle)      (((handle) >> 22) & 0x3ff)

// Extract ID from handle
#define HANDLE_ID(handle)        ((handle) & 0x3fffff)

// Pack type and id into a handle
#define HANDLE_MAKE(type, id)    (((id) & 0x3fffff) | (((type) << 22) & 0x3ffc00000))

// Ensure that the handle is of the expected type
#define HANDLE_GUARD(handle, cls) {if (HANDLE_TYPE((handle)) != (cls)::handle_type) {throw InvalidHandleType((cls)::handle_type, HANDLE_TYPE((handle)), __FILE__, __LINE__);}}((void)0)


/**
  * Packed array of handles for use with SIMD stream types.
  */
class PackedHandles
{
private:
    Handle handles[SIMD_NUM];

public:
    PackedHandles () {}
    ~PackedHandles () {}

    Handle& operator() (const unsigned int index) const
    {
        return handles[index];
    }

    PackedHandles& operator= (const PackedHandles& others)
    {
        for (unsigned int index = 0; index < SIMD_NUM; ++index)
        {
            handles[index] = others.handles[index];
        }
        return *this;
    }
};

//////////
// Exceptions dealing with invalid handles

#include <stdexcept>
#include <sstream>

class InvalidHandleType : public std::runtime_error
{
private:
    std::string makeMessage (const unsigned int expected, const unsigned int was, const std::string& file, unsigned int line)
    {
        std::ostringstream sstr;
        sstr << "Invalid Handle type received (" << file << ":" << line << "), expected: " << expected << ", but got: " << was << "\n";
        message = sstr.str();
    }

public:
    InvalidHandleType (const unsigned int expected, const unsigned int was, const std::string& file, unsigned int line) :
            std::runtime_error(makeMessage(expected, what, file, line))
    {}
};

class InvalidHandleId : public std::runtime_error
{
private:
    std::string makeMessage (const unsigned int expected, const unsigned int was, const std::string& file, unsigned int line)
    {
        std::ostringstream sstr;
        sstr << "Invalid Handle ID received (" << file << ":" << line << "), expected: " << expected << ", but got: " << was << "\n";
        message = sstr.str();
    }

public:
    InvalidHandleId (const unsigned int expected, const unsigned int was, const std::string& file, unsigned int line) :
            std::runtime_error(makeMessage(expected, what, file, line))
    {}
};

#endif // HAMMER_ENGINE_HANDLE__H_
