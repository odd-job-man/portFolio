# Copyright (c) 2013, 2018, Oracle and/or its affiliates. All rights reserved.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License, version 2.0,
# as published by the Free Software Foundation.
#
# This program is designed to work with certain software (including
# but not limited to OpenSSL) that is licensed under separate terms, as
# designated in a particular file or component or in included license
# documentation.  The authors of MySQL hereby grant you an additional
# permission to link the program and your derivative works with the
# separately licensed software that they have either included with
# the program or referenced in the documentation.
# This program is distributed in the hope that it will be useful,  but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
# the GNU General Public License, version 2.0, for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

import mforms


def insert_item_to_plugin_context_menu(menu, item):
    bottom = menu.find_item("bottom_plugins_separator")
    if bottom:
        index = menu.get_item_index(bottom)
        if index > 0 and not menu.find_item("top_plugins_separator"):
            sep = mforms.newMenuItem("", mforms.SeparatorMenuItem)
            sep.set_name("Top Plugins Separator")
            sep.setInternalName("top_plugins_separator")
            menu.insert_item(index, sep)
            index += 1
        menu.insert_item(index, item)
