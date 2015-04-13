#ifndef Controlador_H
#define Controlador_H

#include <mongoose/WebController.h>
#include <mongoose/Server.h>
#include <htmlcxx/html/Page.h>

using namespace std;
using namespace Mongoose;
using namespace htmlcxx::HTML;

class Controlador : public WebController
{
public:
    Controlador();
    void redirecionar(StreamResponse& response, const string& local);
    Page createPage(const string& fileName);
};

#endif // Controlador_H
