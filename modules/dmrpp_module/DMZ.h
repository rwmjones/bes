
// -*- mode: c++; c-basic-offset:4 -*-

// This file is part of the BES

// Copyright (c) 2021 OPeNDAP, Inc.
// Author: James Gallagher <jgallagher@opendap.org>
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
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
//
// You can contact OPeNDAP, Inc. at PO Box 112, Saunderstown, RI. 02874-0112.

#ifndef h_dmz_h
#define h_dmz_h 1

//#include "config.h"

#include <string>
#include <vector>
#include <set>
#include <stack>
#include <memory>

#define PUGIXML_NO_XPATH
#define PUGIXML_HEADER_ONLY
#include <pugixml.hpp>

#include <libdap/Type.h>

namespace libdap {
class DMR;
class BaseType;
class Array;
class D4Group;
class D4Attributes;
class Constructor;
}

namespace http {
class url;
}

namespace dmrpp {

class DmrppCommon;

/**
 * @brief Interface to hide the DMR++ information storage format.
 *
 * This class uses an XML library that uses the document text for all the
 * string values (tag/element names, attribute names and values, etc.)
 * so the text of the XML document must persist for as long as the xml_document
 * object itself. For files, the class uses the pugixml load function.
 *
 * @note This class holds a pugi::xml_document and a shared_ptr<http::url>
 * but does not define its own copy ctor or assignment operator, so copies
 * of an instance of DMZ will share those objects
 */
class DMZ {

private:
    pugi::xml_document d_xml_doc;
    std::shared_ptr<http::url> d_dataset_elem_href;

    void process_dataset(libdap::DMR *dmr, const pugi::xml_node &xml_root);
    pugi::xml_node get_variable_xml_node(libdap::BaseType *btp) const;
    void process_chunk(dmrpp::DmrppCommon *dc, const pugi::xml_node &chunk) const;
    void process_chunks(dmrpp::DmrppCommon *dc, const pugi::xml_node &chunks);

    static void process_compact(libdap::BaseType *btp, const pugi::xml_node &compact);

    static pugi::xml_node get_variable_xml_node_helper(const pugi::xml_node &var_node, std::stack<libdap::BaseType*> &bt);
    static void build_basetype_chain(libdap::BaseType *btp, std::stack<libdap::BaseType*> &bt);

    static void process_group(libdap::DMR *dmr, libdap::D4Group *parent, const pugi::xml_node &var_node);
    static void  process_dimension(libdap::D4Group *grp, const pugi::xml_node &dimension_node);
    static void process_variable(libdap::DMR *dmr, libdap::D4Group *grp, libdap::Constructor *parent, const pugi::xml_node &var_node);
    static void process_dim(libdap::DMR *dmr, libdap::D4Group *grp, libdap::Array *array, const pugi::xml_node &dim_node);
    static void process_map(libdap::DMR *dmr, libdap::D4Group *grp, libdap::Array *array, const pugi::xml_node &map_node);
    static libdap::BaseType *build_variable(libdap::DMR *dmr, libdap::D4Group *group, libdap::Type t, const pugi::xml_node &var_node);
    static libdap::BaseType *add_scalar_variable(libdap::DMR *dmr, libdap::D4Group *group, libdap::Constructor *parent, libdap::Type t, const pugi::xml_node &var_node);
    static libdap::BaseType *add_array_variable(libdap::DMR *dmr, libdap::D4Group *grp, libdap::Constructor *parent, libdap::Type t, const pugi::xml_node &var_node);
    static void process_attribute(libdap::D4Attributes *attributes, const pugi::xml_node &dap_attr_node);

    static void process_cds_node(dmrpp::DmrppCommon *dc, const pugi::xml_node &chunks);

    void load_attributes(libdap::BaseType *btp, pugi::xml_node var_node) const;

    friend class DMZTest;

public:

    /// @brief Build a DMZ without simultaneously parsing an XML document
    DMZ() = default;

    explicit DMZ(const std::string &file_name);

    virtual ~DMZ() = default;

    // This is not virtual because we call it from a ctor
    void parse_xml_doc(const std::string &filename);

    virtual void build_thin_dmr(libdap::DMR *dmr);

    virtual void load_attributes(libdap::BaseType *btp);
    virtual void load_attributes(libdap::Constructor *constructor);
    virtual void load_attributes(libdap::D4Group *group);

    virtual void load_chunks(libdap::BaseType *btp);

#if 0
    // These were originally part of the design and intended to speed the delivery
    // of the metadata responses, but the pugixml parser is so fast I don't think
    // they are needed. Add them later if we really need them. jhrg 11/22/21
    std::string get_attribute_xml(std::string path);
    std::string get_variable_xml(std::string path);
#endif

    virtual void load_all_attributes(libdap::DMR *dmr);

#if 0
    // This was here because with lazy loading of attributes, the glabal values did
    // not show up. But I've dropped the lazy attr load feature since it provides
    // no measureable benefit for the test data we have. If we need lazy-attrs, the
    // software is still in the handler, just mostly disabled. jhrg 11/22/21
    virtual void load_global_attributes(libdap::DMR *dmr);
#endif
};

} // namespace dmrpp

#endif // h_dmz_h
