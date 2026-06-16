// created by corn on June 6, 2026

#include "../include/Sex.h"

std::ostream& operator<<(std::ostream& out, const Sex& sex)
{
    if (sex == Sex::FEMALE)
    {
        out << "female";
    }
    else // if (sex == Sex::MALE)
    {
        out << "male";
    }
    return out;
}