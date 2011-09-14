# Copyright 2009 Evan McLean
# http://evanmclean.com/
#
# This file is part of BDay.
#
# BDay is free software: you can redistribute it and/or modify it under the
# terms of the GNU General Public License as published by the Free Software
# Foundation, either version 3 of the License, or (at your option) any later
# version.
#
# BDay is distributed in the hope that it will be useful, but WITHOUT ANY
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
# A PARTICULAR PURPOSE.  See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along with
# BDay.  If not, see <http://www.gnu.org/licenses/>.

CPP_SRCS = \
../src/AboutDialogue.cpp \
../src/BdayFrame.cpp \
../src/EditorFrame.cpp \
../src/HelpFrame.cpp \
../src/GeneratedGui.cpp \
../src/bday.cpp \
../src/events.cpp \
../src/tokeniser.cpp

OBJS = \
AboutDialogue.o \
BdayFrame.o \
EditorFrame.o \
HelpFrame.o \
GeneratedGui.o \
bday.o \
events.o \
tokeniser.o

CPPFLAGS += -O3 -Wall -fmessage-length=0 -fno-rtti -fno-exceptions

%.o: ../src/%.cpp
	@echo 'Building file: $<'
	g++ $(CPPFLAGS) -c `wx-config --cppflags` -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo ' '

all: bday

bday: $(OBJS)
	@echo 'Building target: $@'
	g++ $(CPPFLAGS) -o bday $(OBJS) `wx-config --libs --static`
	strip bday

clean:
	-rm *.o *.d

clobber: clean
	-rm bday
