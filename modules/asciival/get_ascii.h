
// -*- mode: c++; c-basic-offset:4 -*-

// Copyright (c) 2006 OPeNDAP, Inc.
// Author: James Gallagher <jgallagher@opendap.org>
//
// This is free software; you can redistribute it and/or modify it under the
// terms of the GNU Lesser General Public License as published by the Free
// Software Foundation; either version 2.1 of the License, or (at your
// option) any later version.
//
// This is distributed in the hope that it will be useful, but WITHOUT ANY
// WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for
// more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.

#ifndef E_get_ascii_h
#define E_get_ascii_h 1

#include <libdap/DDS.h>

namespace libdap {
    class BaseType ;
}

namespace dap_asciival {

    void get_data_values_as_ascii(libdap::DDS *dds, FILE *dest);
    void get_data_values_as_ascii(libdap::DDS *dds, std::ostream &strm);

    libdap::DDS *datadds_to_ascii_datadds(libdap::DDS *dds);

    libdap::BaseType *basetype_to_asciitype(libdap::BaseType *bt);
}

#endif // E_get_ascii_h

