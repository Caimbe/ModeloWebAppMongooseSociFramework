#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class Usuario;
typedef shared_ptr<Usuario> UsuarioPtr;
typedef vector<UsuarioPtr> UsuarioList;

class Usuario
{
	string login;
	string password;
	string nome;
	string email;
	tm create_time;
public:
	Usuario();
	Usuario(string login);
	string getLogin() const;
	void setLogin(string value);
	string getPassword() const;
	void setPassword(string value);
	string getNome() const;
	void setNome(string value);
	string getEmail() const;
	void setEmail(string value);
	tm getCreate_time() const;
	void setCreate_time(tm value);
};



#endif // USUARIO_H
