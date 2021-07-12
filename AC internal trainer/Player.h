#pragma once

#include "memo_tools.h"
#include "vector3.h"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}

class Entity
{
public:
    union
    {
        DEFINE_MEMBER_N(Vector3, HeadCoord, 0x4);
        DEFINE_MEMBER_N(Vector3, BodyPos, 0x34);
        DEFINE_MEMBER_N(Vector3, ViewAngles, 0x40);
        DEFINE_MEMBER_N(int32_t, health, 0xf8);
        DEFINE_MEMBER_N(char, name[17], 0x225);
        DEFINE_MEMBER_N(int32_t, ammo, 0x150);
    };

    void SetviewAngles(Vector3* angles)
    {
        this->HeadCoord.x = angles->x;
        this->HeadCoord.y = angles->y;
        this->HeadCoord.z = angles->z;
    }
};

class EntityList
{
public:
    union {
        DEFINE_MEMBER_N(Entity*, content[30], 0x4);
    };
};;