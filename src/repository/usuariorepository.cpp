#include "usuariorepository.h"

UsuarioRepository::UsuarioRepository(soci::session& db) : dataBase(db)
{
}

UsuarioList UsuarioRepository::select(const string& where)
{
soci::rowset<row> rs = 	dataBase.prepare << "SELECT  usuario.login as Usuario_login, usuario.password as Usuario_password, usuario.nome as Usuario_nome, usuario.email as Usuario_email, usuario.create_time as Usuario_create_time \
	FROM usuario" \
	<< (where.size()?"WHERE "+where:"");
	UsuarioList usuarioList;
	for(row& r: rs)
	{
		UsuarioPtr usuario(new Usuario);
		type_conversion<Usuario>::from_base(r, i_ok, *usuario);
		usuarioList.push_back(usuario);
	}
	return usuarioList;
}

int UsuarioRepository::insert(const Usuario& usuario)
{
	dataBase << "insert into usuario(login, password, nome, email, create_time)\
values(:Usuario_login, :Usuario_password, :Usuario_nome, :Usuario_email, :Usuario_create_time)", use(usuario);
	int id=0;
	dataBase << "SELECT LAST_INSERT_ID()", soci::into(id);
	return id;
}

void UsuarioRepository::remove(const Usuario& usuario)
{
	dataBase << "DELETE from usuario WHERE login="<<usuario.getLogin();
}

void UsuarioRepository::update(const Usuario& usuario)
{
	dataBase << "update usuario set login=:Usuario_login, password=:Usuario_password, nome=:Usuario_nome, email=:Usuario_email, create_time=:Usuario_create_time WHERE login="<<usuario.getLogin(), use(usuario);
}

