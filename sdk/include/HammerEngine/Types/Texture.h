#ifndef HAMMER_ENGINE_TEXTURE__H_
#define HAMMER_ENGINE_TEXTURE__H_
/**
  * Hammer Engine
  * Copyright © Hammer Engine Team
  *
  * This file is part of the Hammer Engine Software Development Kit.
  *
  */

#include <HammerEngine/SIMD/GenericVector.h>
#include <HammerEngine/Resources/Handle.h>
#include <HammerEngine/Memory/StreamPool.h>

class Texture : public GenericVector<Texture, 2>
{
private:
    static const unsigned int U=0;
    static const unsigned int V=1;
    PackedHandles packedHandles;

public:

    Packed& u () const
    {
        return get(U);
    }

    Packed& v () const
    {
        return get(V);
    }

    void stream (Stream& s) const
    {
        return s.pack(get(U), get(V))
    }

    PackedHandles& handles () const
    {
        return packedHandles;
    }
};

#endif // HAMMER_ENGINE_TEXTURE__H_
