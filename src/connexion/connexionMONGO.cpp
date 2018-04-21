/*
 * connexionMONGO.cpp
 *
 *  Created on: Mar 31, 2018
 *      Author: andres
 */
#ifdef false
#include <connexion/connexionMONGO.h>


#include <cstdint>
#include <iostream>
#include <vector>

#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_document;



mongocxx::instance inst{};
#endif
