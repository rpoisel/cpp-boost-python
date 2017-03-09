#include "mymodule.h"

#include <boost/python.hpp>

#include <cstdlib>

using namespace boost::python;

int main(void)
{
    try
    {
	::setenv("PYTHONPATH", ".", 1);

	Py_Initialize();

	object main_module = import("__main__");
	dict main_namespace = extract<dict>(main_module.attr("__dict__"));
	object embedding = import("embedding");
	object myfunc = embedding.attr("myfunc");
	myfunc("R2D2");
    }
    catch (error_already_set& e)
    {
	PyErr_PrintEx(0);
	return 1;
    }
    return 0;
}
