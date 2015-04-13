#include "usuario.h"

Usuario::Usuario(){}
Usuario::Usuario(string login)
{
	this->login = login;
}

string Usuario::getLogin() const
{
	return login;
}
void Usuario::setLogin(string value)
{
	login = value;
}
string Usuario::getPassword() const
{
	return password;
}
void Usuario::setPassword(string value)
{
	password = value;
}
string Usuario::getNome() const
{
	return nome;
}
void Usuario::setNome(string value)
{
	nome = value;
}
string Usuario::getEmail() const
{
	return email;
}
void Usuario::setEmail(string value)
{
	email = value;
}
tm Usuario::getCreate_time() const
{
	return create_time;
}
void Usuario::setCreate_time(tm value)
{
	create_time = value;
}

