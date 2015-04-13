#include "repository.h"
Repository::Repository() :usuario(dataBase) 
{}
void Repository::open(std::string& connectStringDataBase)
{
	if(connectStringDataBase.size())
		dataBase.open(connectStringDataBase);
}
template<> UsuarioList Repository::select(const string& where)
{
	return usuario.select(where);
}
template<> int Repository::insert(const Usuario& obj)
{
	return usuario.insert(obj);
}
template<> void Repository::update(const Usuario& obj)
{
	usuario.update(obj);
}
template<> void Repository::remove(const Usuario& obj)
{
	usuario.remove(obj);
}
