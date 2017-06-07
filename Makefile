# Ce Makefile compile tous les fichiers .cpp placés dans le dossier src/.
# Un gros défaut : Il ne gère pas les .h ou .hpp, donc si vous les modifiez,
# il faut faire 'make re'.
#
# Il n'y a pas de façon simple de résoudre ce problème, à part investiguer
# 'gcc -M' ou faire des présomptions (du genre "chaque 'foo.cpp'
# a son header 'foo.hpp'").

include make/host.mk
include make/rglob.mk

ifeq ($(host_os),windows)
dot_exe   := .exe
mkdir_p  = if not exist $(subst /,\\,$(1)) ( mkdir $(subst /,\\,$(1)) )
rmdir_rf = if exist $(subst /,\\,$(1)) ( rmdir /q /s $(subst /,\\,$(1)) )
cxxarch  = -m64
else
dot_exe  :=
rmdir_rf = rm -rf $(1)
mkdir_p  = mkdir -p $(1)
cxxarch  :=
endif

cxx      := g++
cxxflags := $(strip \
	$(cxxarch) -std=c++11 -Wall -pedantic -Iinclude -g  \
	-DDM_GL_DEBUG -DGLEW_STATIC \
)
cppfiles := $(call rglob,src,*.cpp)
ofiles   := $(patsubst src/%.cpp,obj/%.o,$(cppfiles))

exe      := bin/rollercoaster$(dot_exe)

ifeq ($(host_os),windows)
SHELL=cmd
SHELLFLAGS=/c 
ldlibs   := -lSDL2 -lopengl32
endif
ifeq ($(host_os),linux)
ldlibs   := -lSDL2 -lGL
endif
ifeq ($(host_os),osx)
ldlibs   := -framework SDL2 -framework OpenGL
endif


.PHONY: all clean re mrproper

all: $(exe)

obj/%.o: src/%.cpp
	@$(call mkdir_p,$(@D))
	$(cxx) $(cxxflags) -c $< -o $@

$(exe): $(ofiles)
	@$(call mkdir_p,$(@D))
	$(cxx) $(cxxflags) $^ -o $@ $(ldlibs)

clean:
	$(call rmdir_rf,obj)
re: clean all
mrproper: re
