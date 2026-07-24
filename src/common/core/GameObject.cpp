#include "common/core/GameObject.hpp"
#include "common/core/IDGenerator.hpp"

GameObject::GameObject() : m_ID(IDGenerator::Next())
{
    //ctor
}

GameObject::~GameObject()
{
    //dtor
}

