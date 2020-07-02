#include "team.h"

Team::Team(int engLevel)
{
    engineers = engLevel;
}

void Team::upgradeEngineers()
{
    engineers++;
}

int Team::getEngineers()
{
    return engineers;
}
