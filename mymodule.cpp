#include "mymodule.h"

#include <boost/python.hpp>

using namespace boost::python;

BOOST_PYTHON_MODULE(mymodule)
{
    class_<Base>("Base")
        .def("__str__", &Base::name)
        ;
}
