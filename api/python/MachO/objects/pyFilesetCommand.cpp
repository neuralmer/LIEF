/* Copyright 2017 - 2021 R. Thomas
 * Copyright 2017 - 2021 Quarkslab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <algorithm>

#include <string>
#include <sstream>

#include "LIEF/MachO/hash.hpp"
#include "LIEF/MachO/FilesetCommand.hpp"

#include "pyMachO.hpp"

namespace LIEF {
namespace MachO {

template<class T>
using getter_t = T (FilesetCommand::*)(void) const;

template<class T>
using setter_t = void (FilesetCommand::*)(T);

template<class T>
using no_const_getter_t = T (FilesetCommand::*)();



template<>
void create<FilesetCommand>(py::module& m) {

  py::class_<FilesetCommand, LoadCommand>(m, "FilesetCommand")
    .def_property("name",
        static_cast<getter_t<const std::string&>>(&FilesetCommand::name),
        static_cast<setter_t<const std::string&>>(&FilesetCommand::name))

    .def_property("virtual_address",
        static_cast<getter_t<uint64_t>>(&FilesetCommand::virtual_address),
        static_cast<setter_t<uint64_t>>(&FilesetCommand::virtual_address))

    .def_property("file_offset",
        static_cast<getter_t<uint64_t>>(&FilesetCommand::file_offset),
        static_cast<setter_t<uint64_t>>(&FilesetCommand::file_offset))

    .def_property_readonly("binary",
        static_cast<no_const_getter_t<Binary*>>(&FilesetCommand::binary),
        py::return_value_policy::reference)

    .def("__eq__", &FilesetCommand::operator==)
    .def("__ne__", &FilesetCommand::operator!=)
    .def("__hash__",
        [] (const FilesetCommand& main) {
          return Hash::hash(main);
        })


    .def("__str__",
        [] (const FilesetCommand& main)
        {
          std::ostringstream stream;
          stream << main;
          return stream.str();
        });

}

}
}
