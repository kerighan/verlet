#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "vec.hpp"
#include "node.hpp"
#include "force.hpp"
#include "universe.hpp"


namespace py = pybind11;


PYBIND11_MODULE(verlet, m)  {
    py::class_<Node>(m, "Node")
        .def(py::init<float, float, float, float, float>(),
             py::arg("x") = 0,
             py::arg("y") = 0,
             py::arg("r") = 1,
             py::arg("m") = 1,
             py::arg("friction") = 0)
        .def("get_position", &Node::get_position)
        .def("get_velocity", &Node::get_velocity)
        .def("get_acceleration", &Node::get_acceleration)
        .def("get_radius", &Node::get_radius);

    py::class_<Force>(m, "Force")
        .def(py::init<>())
        .def("add", &Charge::add);

    py::class_<Charge, Force>(m, "Charge")
        .def(py::init<float, float, float>(),
             py::arg("x") = 0,
             py::arg("y") = 0,
             py::arg("q") = 1)
        .def("interact", &Charge::interact);

    py::class_<Friction, Force>(m, "Friction")
        .def(py::init<float>(),
             py::arg("mu") = 1)
        .def("interact", &Friction::interact);

    py::class_<Link, Force>(m, "Link")
        .def(py::init<Node*, Node*, float>())
        .def("interact", &Link::interact);

    py::class_<Universe>(m, "Universe")
        .def(py::init<float, size_t, size_t>(),
             py::arg("delta") = 0.1,
             py::arg("capacity") = 5,
             py::arg("n_iter") = 3)
        .def("add_nodes", &Universe::add_nodes)
        .def("add_forces", &Universe::add_forces)
        .def("add_force", &Universe::add_force)
        .def("run", &Universe::run)
        .def("history", &Universe::history,
             py::arg("iter"),
             py::arg("steps") = 10);
}
