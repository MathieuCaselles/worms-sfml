#pragma once

#include <string>

using Typename = std::string;

class RTTI
{
public:
    RTTI(const Typename& classname, RTTI* parentRtti) : m_classname(classname), m_parentRTTI(parentRtti) {}
    const Typename& getClassname() const { return m_classname; }
    RTTI* getParentRTTI() const { return m_parentRTTI; }

private:
    Typename m_classname;
    RTTI* m_parentRTTI;
};

class HasRTTI
{
public:
    const virtual RTTI* getInstanceRTTI() const = 0;
};

class NoRTTIRoot
{
public:
    static RTTI* getClassRTTI() { return nullptr; }
};

#define DECLARE_RTTI(Classname, ParentType) \
    static RTTI* getClassRTTI() { static RTTI insaneRTTI{#Classname, ParentType::getClassRTTI()}; return &insaneRTTI; } \
    const virtual RTTI* getInstanceRTTI() const { return getClassRTTI(); }