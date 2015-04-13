#include "usuariocontrolador.h"
#include <htmlcxx/html/Page.h>

using namespace htmlcxx::HTML;

UsuarioControlador::UsuarioControlador()
{
}

void UsuarioControlador::setup()
{
    addRoute("GET", "/usuario/novo", UsuarioControlador, novo);
}

void UsuarioControlador::novo(Request &request, StreamResponse &response)
{
    Page page = createPage("/usuario/novo.html");
    response << page;
}
