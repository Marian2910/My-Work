//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_MONEDE_H
#define LAB9_10_MONEDE_H
using namespace std;

class Monede {
private:
    int cinzeciBani;
    int zeceBani;
public:
    Monede();
    Monede(int cinzeciBani, int zeceBani);
    ~Monede();
    int getCinzeciBani() const;
    int getZeceBani() const;
    void setCinzeciBani(int cinzeciBani);
    void setZeceBani(int zeceBani);
    Monede &operator=(const Monede &monede);
    bool operator==(const Monede &t);
};


#endif //LAB9_10_MONEDE_H
