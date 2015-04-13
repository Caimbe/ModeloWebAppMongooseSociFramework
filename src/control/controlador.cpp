#include "controlador.h"

Controlador::Controlador()
{
}


void Controlador::redirecionar(StreamResponse& response, const string& local)
{
	response.setCode(301);
    response.setHeader("Location", local);
}

Page Controlador::createPage(const string &fileName)
{
    Page page;
    ifstream ftemplate(server->getOption("document_root")+server->getOption("template_page"));
    if(ftemplate.is_open())
        page.setContent(ftemplate);
    else
        throw runtime_error("template file not found!");

    ifstream fcontent(server->getOption("document_root")+fileName);
    if(fcontent.is_open())
        page.insertContentId("content", fcontent);
    else
        throw runtime_error("content file not found: "+fileName);

    cout << ftemplate;

    return page;
}
