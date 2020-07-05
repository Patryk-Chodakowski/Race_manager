#ifndef TEAM_H
#define TEAM_H

/*!
    \brief Klasa zespołu inżynierów
*/

class Team
{
    ///poziom inżynierów
    int engineers = 0;

public:
    /*!
    \brief Konstuktor klasy
    \param poziom inżynierów
    */
    Team(int engLevel = 0);

    ///\brief Zwiększa poziom inżynierów o 1
    void upgradeEngineers();
    ///\brief Zwraca poziom inżynierów
    int getEngineers();
};

#endif // TEAM_H
