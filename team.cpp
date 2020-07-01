#include "team.h"

Team::Team()
{

}

void Team::upgradeEngineers()
{
    engineers++;
}

int Team::getEngineers()
{
    return engineers;
}
