#ifndef IDGENERATOR_HPP_INCLUDED
#define IDGENERATOR_HPP_INCLUDED

// The IDGenerator class is used to generate IDs for GameObjects (only!).

class IDGenerator
{
public:
    static uint32_t Next()
    {
        return ++NextID;
    }

    void Reset()
    {
        NextID = 0;
    }

private:
    inline static uint32_t NextID = 0;
};

#endif // IDGENERATOR_HPP_INCLUDED
