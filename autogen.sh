#! /bin/sh -e

# Copyright (c) 2009 Openismus GmbH
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License VERSION 2 as
# published by the Free Software Foundation.  You are not allowed to
# use any other version of the license; unless you got the explicit
# permission from the author to do so.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
# 02110-1301, USA.

test -n "$srcdir" || srcdir=`dirname "$0"`
test -n "$srcdir" || srcdir=.

mm-common-prepare --force --copy "$srcdir"
autoreconf --force --install "$srcdir"
test -n "$NOCONFIGURE" || "$srcdir/configure" "$@"
