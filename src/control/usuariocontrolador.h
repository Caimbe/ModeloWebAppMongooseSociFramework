#ifndef USUARIOCONTROLADOR_H
#define USUARIOCONTROLADOR_H

#include "controlador.h"

class UsuarioControlador : public Controlador
{
public:
    UsuarioControlador();
    void setup();
    void novo(Request &request, StreamResponse &response);
};

#endif // USUARIOCONTROLADOR_H
