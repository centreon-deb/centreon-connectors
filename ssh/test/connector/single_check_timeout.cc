/*
** Copyright 2012-2013 Centreon
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

#include <cstring>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string>
#include "com/centreon/clib.hh"
#include "com/centreon/concurrency/thread.hh"
#include "com/centreon/exceptions/basic.hh"
#include "com/centreon/process.hh"
#include "test/connector/binary.hh"

using namespace com::centreon;

#define CMD1 "2\0" \
             "4242\0" \
             "3\0" \
             "123456789\0" \
             "check_by_ssh " \
             "-H localhost " \
             " -C 'sleep 30'\0\0\0\0"
#define RESULT "3\0" \
               "4242\0" \
               "0\0" \
               "-1\0" \
               " \0" \
               " \0\0\0\0"

/**
 *  The process killing task.
 */
class      kill_connector : public concurrency::thread {
public:
  /**
   *  Constructor.
   */
           kill_connector(process* p, time_t when)
    : _p(p), _when(when) {}

  /**
   *  Run thread.
   */
  void     _run() {
    time_t now(time(NULL));
    if (now < _when)
      sleep(_when - now);
    _p->terminate();
    return ;
  }

private:
  process* _p;
  time_t   _when;
};

/**
 *  Check that connector set timeout on commands.
 *
 *  @return 0 on success.
 */
int main() {
  clib::load();
  // Process.
  process p;
  p.enable_stream(process::in, true);
  p.enable_stream(process::out, true);
  p.exec(CONNECTOR_SSH_BINARY);

  // Write command.
  std::ostringstream oss;
  oss.write(CMD1, sizeof(CMD1) - 1);
  std::string cmd(oss.str());
  char const* ptr(cmd.c_str());
  unsigned int size(cmd.size());
  while (size > 0) {
    unsigned int rb(p.write(ptr, size));
    size -= rb;
    ptr += rb;
  }
  p.enable_stream(process::in, false);

  // Schedule process termination.
  kill_connector killer(&p, time(NULL) + 4);
  killer.exec();

  // Read reply.
  std::string output;
  while (true) {
    std::string buffer;
    p.read(buffer);
    if (buffer.empty())
      break;
    output.append(buffer);
  }

  // Wait for process termination.
  p.wait();
  int retval(p.exit_code() != 0);

  clib::unload();

  try {
    if (retval)
      throw (basic_error() << "invalid return code: " << retval);
    if (output.size() != (sizeof(RESULT) - 1)
        || memcmp(output.c_str(), RESULT, sizeof(RESULT) - 1))
      throw (basic_error()
             << "invalid output: size=" << output.size()
             << ", output=" << output);
  }
  catch (std::exception const& e) {
    retval = 1;
    std::cerr << "error: " << e.what() << std::endl;
  }

  return (retval);
}
