/*
** Copyright 2011-2013 Centreon
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** For more information : contact@centreon.com
*/

#include "com/centreon/connector/perl/orders/listener.hh"

using namespace com::centreon::connector::perl::orders;

/**************************************
*                                     *
*           Public Methods            *
*                                     *
**************************************/

/**
 *  Default constructor.
 */
listener::listener() {}

/**
 *  Copy constructor.
 *
 *  @param[in] l Unused.
 */
listener::listener(listener const& l) {
  (void)l;
}

/**
 *  Destructor.
 */
listener::~listener() {}

/**
 *  Assignment operator.
 *
 *  @param[in] l Unused.
 *
 *  @return This object.
 */
listener& listener::operator=(listener const& l) {
  (void)l;
  return (*this);
}
