#ifndef USUARIOREPOSITORY_H
#define USUARIOREPOSITORY_H

#include <iostream>
#include <memory>
#include <vector>
#include <soci/soci.h>
#include "entity/usuario.h"
using namespace soci;


class UsuarioRepository
{
	soci::session& dataBase;
public:
	UsuarioRepository(soci::session& dataBase);
	int insert(const Usuario& usuario);
	UsuarioList select(const string& where="");
	void update(const Usuario& usuario);
	void remove(const Usuario& usuario);
};

namespace soci
{
template<>
struct type_conversion<Usuario>
{
typedef values base_type;
	template<class T>	static void from_base(const T& v, const indicator& ind, Usuario & p)
	{
		if (v.get_indicator("Usuario_login") != i_null){
			p.setLogin( v.get<string>("Usuario_login" ) );
		}
		if (v.get_indicator("Usuario_password") != i_null){
			p.setPassword( v.get<string>("Usuario_password" ) );
		}
		if (v.get_indicator("Usuario_nome") != i_null){
			p.setNome( v.get<string>("Usuario_nome" ) );
		}
		if (v.get_indicator("Usuario_email") != i_null){
			p.setEmail( v.get<string>("Usuario_email" ) );
		}
		if (v.get_indicator("Usuario_create_time") != i_null){
			p.setCreate_time( v.get<tm>("Usuario_create_time" ) );
		}
	}
	static void to_base(const Usuario & p, values & v, indicator & ind)
	{
		v.set( "Usuario_login", p.getLogin() );
		v.set( "Usuario_password", p.getPassword() );
		v.set( "Usuario_nome", p.getNome() );
		v.set( "Usuario_email", p.getEmail() );
		v.set( "Usuario_create_time", p.getCreate_time() );
		ind = i_ok;
	}
};
}

#endif // USUARIOREPOSITORY_H
