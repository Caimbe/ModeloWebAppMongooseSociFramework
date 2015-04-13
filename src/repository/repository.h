#ifndef REPOSITORY_H
#define REPOSITORY_H
#include <soci/soci.h>
#include <typeinfo>
#include "usuariorepository.h"

class Repository
{
	soci::session dataBase;
	UsuarioRepository usuario;
public:
	Repository();

	void open(std::string& connectStringDataBase);
	template<class T> T select(const string& where="");
	template<class T> int insert(const T& obj);
	template<class T> void update(const T& obj);
	template<class T> void remove(const T& obj);

};

#endif // REPOSITORY_H
