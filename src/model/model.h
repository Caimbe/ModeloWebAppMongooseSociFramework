#ifndef MODEL_H
#define MODEL_H

#include "repository/repository.h"

class Model
{
protected:
    static Repository repository;
public:
    Model();
    void open(string urlConnectDB);
};

#endif // MODEL_H
