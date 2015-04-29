#ifndef WIN32
#   define DLL_EXPORT
#	include <unistd.h>
#   include <sys/stat.h>
#else
#   define DLL_EXPORT __declspec(dllexport)
#   include <direct.h>
#endif
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>
#include <signal.h>
#include <iostream>
#include <fstream>
#include <boost/thread.hpp>
#include <boost/program_options.hpp>
#include <mongoose/Server.h>
#include "util.hpp"
#include "model/model.h"

using namespace std;
using namespace Mongoose;
using namespace boost::program_options;


namespace
{
	const size_t SUCCESS = 0;
	const size_t ERROR_IN_COMMAND_LINE = 1;
	const size_t ERROR_IN_FILE_LOCK = 2;
#ifndef _MSC_VER
    const size_t ERROR_UNHANDLED_EXCEPTION = 3;
#endif

#ifdef _WIN32
    const string NAME_LOCK = "/labEstoque.lock";
#   define ARQ_LOCK std::getenv("TMP")+NAME_LOCK
#else
    const string NAME_LOCK = "/labEstoque.lock";
#   define ARQ_LOCK "/tmp"+NAME_LOCK
#endif

    namespace po = boost::program_options;
    volatile static bool running = true;
    extern "C" DLL_EXPORT void handle_signal(int sig);
    bool verificaArqLock();

    struct Opcoes
    {
        int porta;
        string webdir;
        string connectdb;
    };

    Opcoes processaOpcoes(int argc, char** argv);

} // namespace



int main(int argc, char** argv)
{
	signal(SIGINT, handle_signal);
	signal(SIGSEGV, handle_signal);
	signal(SIGABRT, handle_signal);

    Opcoes op = processaOpcoes(argc, argv);
    Server server(op.porta, op.webdir.c_str());
    Model model;
    UsuarioController usuario;

	try
    {
        server.setOption("enable_directory_listing", "false");
        server.registerController(&usuario);        
        server.setOption("template_page", "/template.html");
		server.start();		

        model.open(op.connectdb);

        cout << "Server Up!" << endl;
		while (running) {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
			if (verificaArqLock())
				handle_signal(0);
		}

        server.poll();
        server.stop();
		cout << "Server Down!" << endl;
	}
	catch (po::error& e)
	{
		std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
//		std::cerr << desc << std::endl;
		return ERROR_IN_COMMAND_LINE;
	}
	catch (std::exception& e)
	{
        std::cerr << "Exception reached the top of main: "
			<< e.what() << ", application will now exit" << std::endl;
		return ERROR_UNHANDLED_EXCEPTION;

	}

	return SUCCESS;
}

namespace
{

    extern "C" DLL_EXPORT void handle_signal(int sig)
    {
        running = false;
        cerr << "\nSignal: " << sig << endl << "Exiting..." << endl;

        void *array[10];
        size_t size;

        // get void*'s for all entries on the stack
        size = backtrace(array, 10);

        // print out all the frames to stderr
        fprintf(stderr, "Error: signal %d:\n", sig);
        backtrace_symbols_fd(array, size, STDERR_FILENO);

        boost::this_thread::sleep(boost::posix_time::seconds(2));
        std::exit(sig);
    }

    bool verificaArqLock()
    {
        ifstream arq(ARQ_LOCK);
        return !arq.is_open();
    }

    Opcoes processaOpcoes(int argc, char** argv)
    {
        Opcoes retorno;
        po::options_description desc("Options");
        desc.add_options()
            ("help,h", "Print help messages")
            ("port,p", po::value<int>(), "<PORT> set port to open socket ex.: 8080")
            ("webdir,w", po::value<string>(), "<DIR> set dir to web content ex.: ../WebContent")
            ("conncetdb,c", po::value<string>(), "<URL> string for conection in database ex.: \"mysql://host=localhost db=mydatabase user=root password=123456\"");

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc),
            vm); // can throw
        po::notify(vm); // throws on error, so do after help in case there are any problems

        if (vm.count("help"))
        {
            std::cout << "Basic Command Line Parameter App" << std::endl
                << desc << std::endl;
            exit(SUCCESS);
        }
        retorno.porta = 8080;
        if (vm.count("port"))
        {
            retorno.porta = vm["port"].as<int>();
            std::cerr << "Usando porta: " << retorno.porta << endl;
        }
        retorno.webdir = "../WebContent/";
        if (vm.count("webdir"))
        {
            retorno.webdir = vm["webdir"].as<string>();
        }
        cout << "WebDir: " << retorno.webdir << endl;

        //makedir("tmp"); //mkdir("tmp", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
        cout << ARQ_LOCK << endl;
        ofstream arq(ARQ_LOCK);
        if (!arq.good()){
            cerr << "problemas ao criar o arquivo de trava: " << ARQ_LOCK << endl;
            exit(ERROR_IN_FILE_LOCK);
        }
        arq << "running" << endl;
        arq.close();

        retorno.connectdb = vm.count("conncetdb") ? vm["conncetdb"].as<string>() : "";

        return retorno;
    }

} // namespace




