// BESCatalog.h

// This file is part of bes, A C++ back-end server implementation framework
// for the OPeNDAP Data Access Protocol.

// Copyright (c) 2004-2009 University Corporation for Atmospheric Research
// Author: Patrick West <pwest@ucar.edu> and Jose Garcia <jgarcia@ucar.edu>
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// You can contact University Corporation for Atmospheric Research at
// 3080 Center Green Drive, Boulder, CO 80301

// (c) COPYRIGHT University Corporation for Atmospheric Research 2004-2005
// Please read the full copyright statement in the file COPYRIGHT_UCAR.
//
// Authors:
//      pwest       Patrick West <pwest@ucar.edu>
//      jgarcia     Jose Garcia <jgarcia@ucar.edu>

#ifndef I_BESCatalog_h
#define I_BESCatalog_h 1

#include <string>

using std::string;

#include "BESObj.h"

class BESCatalogEntry;

/** @brief abstract base class catalog object. Derived classes know how to
 * show nodes and leaves in a catalog.
 */
class BESCatalog: public BESObj {
private:
    string _catalog_name;
    unsigned int _reference;

    BESCatalog()
    {
    }

protected:
    BESCatalog(const string &catalog_name) :
            _catalog_name(catalog_name), _reference(0)
    {
    }

public:
    virtual ~BESCatalog(void)
    {
    }

    virtual void reference_catalog()
    {
        _reference++;
    }

    virtual unsigned int dereference_catalog()
    {
        if (!_reference)
            return _reference;
        return --_reference;
    }

    virtual string get_catalog_name()
    {
        return _catalog_name;
    }

    virtual BESCatalogEntry * show_catalog(const string &container, const string &coi, BESCatalogEntry *entry) = 0;

    virtual void dump(ostream &strm) const = 0;
};

#endif // I_BESCatalog_h