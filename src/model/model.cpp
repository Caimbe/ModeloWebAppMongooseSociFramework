#include "model.h"

Repository Model::repository;

Model::Model()
{
}
void Model::open(string urlConnectDB)
{
    cout << "abrindo DB: " << urlConnectDB << endl;
    repository.open(urlConnectDB);
}
