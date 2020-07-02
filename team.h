#ifndef TEAM_H
#define TEAM_H


class Team
{
    int engineers = 0;

public:
    Team(int engLevel = 0);

    void upgradeEngineers();
    int getEngineers();
};

#endif // TEAM_H
