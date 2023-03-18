//
// Created by Marian Mutu on 25.04.2022.
//

#ifndef LAB9_10_REPOSITORYGENERIC_H
#define LAB9_10_REPOSITORYGENERIC_H
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

template<class Entity>
class RepositoryGeneric {
private:
    vector<Entity> entities;
    string filename;
public:
    explicit RepositoryGeneric(const string& filename);
    RepositoryGeneric();
    void addElem(Entity entity);
    vector<Entity> getAll();
    void deleteElem(const Entity& entity);
    void updateElem(const Entity& oldEntity, const Entity& newEntity);
    void saveToFile();
    void loadFromFile();

};

template<class Entity>
RepositoryGeneric<Entity>::RepositoryGeneric(const string &filename) {
    if(!filename.empty())
        this->filename = filename;
    loadFromFile();
}

template<class Entity>
RepositoryGeneric<Entity>::RepositoryGeneric() {
    this->filename = "";
}


template<class Entity>
void RepositoryGeneric<Entity>::addElem(Entity entity) {
    this->entities.push_back(entity);
    this->saveToFile();
}

template<class Entity>
vector<Entity> RepositoryGeneric<Entity>::getAll() {
    return this->entities;
}

template<class Entity>
void RepositoryGeneric<Entity>::deleteElem(const Entity &entity) {
    typename std:: vector<Entity>::iterator it;
    it = find(this->entities.begin(), this->entities.end(), entity);
    if(it != this->entities.end())
        this->entities.erase(it);
    this->saveToFile();
}

template<class Entity>
void RepositoryGeneric<Entity>::updateElem(const Entity &oldEntity, const Entity &newEntity) {
    typename std::vector<Entity>::iterator it;
    it = find(this->entities.begin(), this->entities.end(), oldEntity);
    if(it == this->entities.end())
        return;
    else
        *it = newEntity;
    this->saveToFile();
}

template <class T>
void RepositoryGeneric<T>::saveToFile()
{
    if (!filename.empty())
    {
        ofstream fo(this->filename);
        for (int i = 0; i < this->entities.size();i++)
        {
            fo << this->entities[i] << endl;
        }
        fo.close();

    }
    else
        return;
}

template <class Entity>
void RepositoryGeneric<Entity>::loadFromFile()
{
    Entity entity;
    if (!this->filename.empty())
    {
        ifstream fi(this->filename);
        while (fi>>entity)
        {
                this->addElem(entity);
        }
        fi.close();
    }
}
#endif //LAB9_10_REPOSITORYGENERIC_H
