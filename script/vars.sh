#!/bin/bash

# Copyright (c) 2016, Codrin-Victor Poienaru <cvpoienaru@gmail.com>.
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# This software is provided by the copyright holders and contributors "as is"
# and any express or implied warranties, including, but not limited to, the
# implied warranties of merchantability and fitness for a particular purpose are
# disclaimed. In no event shall the copyright holder or contributors be liable
# for any direct, indirect, incidental, special, exemplary, or consequential
# damages (including, but not limited to, procurement of substitute goods or
# services; loss of use, data, or profits; or business interruption) however
# caused and on any theory of liability, whether in contract, strict liability,
# or tort (including negligence or otherwise) arising in any way out of the use
# of this software, even if advised of the possibility of such damage.

# Directory structure
export EDS_ROOT=~/Projects/EssentialDS
export EDS_BIN=$EDS_ROOT/bin
export EDS_INCLUDE=$EDS_ROOT/include
export EDS_LIB=$EDS_ROOT/lib
export EDS_SCRIPT=$EDS_ROOT/script
export EDS_SRC=$EDS_ROOT/src

# Environment paths
export C_INCLUDE_PATH=$EDS_INCLUDE
export LIBRARY_PATH=$EDS_LIB
export LD_LIBRARY_PATH=$EDS_LIB

# File system permission mask
export EDS_MASK=0022

# Build options
export EDS_DEBUG=true
export EDS_BUILD_THREADS=16

unset EDS_FLAGS
if $EDS_DEBUG; then
	export EDS_FLAGS=-g
fi
