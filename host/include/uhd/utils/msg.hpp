//
// Copyright 2011-2013 Ettus Research LLC
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef INCLUDED_UHD_UTILS_MSG_HPP
#define INCLUDED_UHD_UTILS_MSG_HPP

#include <uhd/config.hpp>
#include <uhd/utils/pimpl.hpp>
#include <ostream>
#include <iomanip>
#include <string>

/*!
 * A UHD message macro with configurable type.
 * Usage: UHD_MSG(warning) << "some warning message" << std::endl;
 */
#define UHD_MSG(type) \
    uhd::msg::_msg(uhd::msg::type)()

//! Helpful debug tool to print site info
#define UHD_HERE() \
    UHD_MSG(status) << __FILE__ << ":" << __LINE__ << std::endl

//! Helpful debug tool to print a variable
#define UHD_VAR(var) \
    UHD_MSG(status) << #var << " = " << var << std::endl;

//! Helpful debug tool to print a variable in hex
#define UHD_HEX(var) \
    UHD_MSG(status) << #var << " = 0x" << std::hex << std::setfill('0') << std::setw(8) << var << std::dec << std::endl;

namespace uhd{ namespace msg{

    //! Possible message types
    enum type_t{
        status  = 's',
        warning = 'w',
        error   = 'e',
        fastpath= 'f'
    };

    //! Typedef for a user-registered message handler
    typedef void (*handler_t)(type_t, const std::string &);

    /*!
     * Default message handler for printing uhd system messages
     * \param type message type, such as status, warning, or error
     * \param msg contents of the system message as a string
     */
    void default_msg_handler(type_t type, const std::string &msg);

    /*!
     * Register the handler for uhd system messages.
     * Only one handler can be registered at once.
     * This replaces the default std::cout/cerr handler.
     * \param handler a new handler callback function
     */
    UHD_API void register_handler(const handler_t &handler);

    /*!
     * Returns the current message handler for uhd system messages
     * \returns the current message handler
     */
    UHD_API const handler_t& get_handler();

    //! Internal message object (called by UHD_MSG macro)
    class UHD_API _msg{
    public:
        _msg(const type_t type);
        ~_msg(void);
        std::ostream &operator()(void);
    private:
        UHD_PIMPL_DECL(impl) _impl;
    };

}} //namespace uhd::msg

#endif /* INCLUDED_UHD_UTILS_MSG_HPP */
