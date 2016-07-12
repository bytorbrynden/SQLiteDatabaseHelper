#
# SQLiteDatabaseHelper/Makefile
#
NAME := sqlitedatabasehelper
ROOT := ${CURDIR}

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_LIB := ${ROOT}/Libraries
_OUT := ${ROOT}/Build
_OBJ := ${_OUT}/obj
_BIN := ${_OUT}/bin

TARGET := ${_BIN}/lib${NAME}.a

# The path that the library archives should be copied to
COPY_LIBRARY_ARCHIVES_TO := ${HOME}/code/SQLiteDatabaseHelperTest/Libraries/SQLiteDatabaseHelper/

# The path that the library headers should be copied to
COPY_LIBRARY_HEADERS_TO := ${HOME}/code/SQLiteDatabaseHelperTest/Libraries/SQLiteDatabaseHelper/

MD := mkdir
MD_FLAGS := -p

RM := rm
RM_FLAGS := -rf

CP := cp
CP_FLAGS := -r

CC := gcc
CC_FLAGS := -c -Wall -Werror -ggdb -I${_INC} -I${_LIB}

AR := ar
AR_FLAGS := -rsc

SRCS := $(shell find ${_SRC} -type f -name "*.c")
OBJS := $(patsubst ${_SRC}/%.c, ${_OBJ}/srcs/%.o, ${SRCS})

LIB_SRCS := $(shell find ${_LIB} -type f -name "*.c")
LIB_OBJS := $(patsubst ${_LIB}/%.c, ${_OBJ}/libs/%.o, ${LIB_SRCS})

HEADERS := $(shell find ${ROOT} -type f -name "*.h")

SRC_HEADERS := $(patsubst ${_INC}/%.h, ${_BIN}/Include/%.h, ${HEADERS})
LIB_HEADERS := $(patsubst ${_LIB}/%.h, ${_BIN}/Include/%.h, ${HEADERS})

.PHONY: all
all: prepare clean objects archive postbuild

prepare:
	@if [ ! -d ${_OUT} ]; then ${MD} ${MD_FLAGS} ${_OUT}; fi
	@if [ ! -d ${_OBJ} ]; then ${MD} ${MD_FLAGS} ${_OBJ}; fi
	@if [ ! -d ${_BIN} ]; then ${MD} ${MD_FLAGS} ${_BIN}; fi

clean:
	@echo "[PREBUILD] [CLEAN] Cleaning object folder"
	@${RM} ${RM_FLAGS} ${_OBJ}/*
	@echo "[PREBUILD] [CLEAN] Cleaning bin folder"
	@${RM} ${RM_FLAGS} ${_BIN}/*

objects: ${OBJS} ${LIB_OBJS}

archive: ${SRC_HEADERS} ${LIB_HEADERS}
	@echo "[BUILD] [ARCHIVE] Generating archive file out of library objects"
	@${AR} ${AR_FLAGS} ${TARGET} $(shell find ${_OBJ} -type f -name "*.o")

${_OBJ}/srcs/%.o: ${_SRC}/%.c
	@echo "[BUILD] [COMPILE] Creating object file for '$(patsubst ${_SRC}/%.c,%.c, $^)'"
	@${MD} ${MD_FLAGS} $(dir $@)
	@${CC} ${CC_FLAGS} $^ -o $@

${_OBJ}/libs/%.o: ${_LIB}/%.c
	@echo "[BUILD] [COMPILE] Creating object file for '$(patsubst ${_LIB}/%.c,%.c, $^)'"
	@${MD} ${MD_FLAGS} $(dir $@)
	@${CC} ${CC_FLAGS} $^ -o $@

${_BIN}/Include/%.h: ${_INC}/%.h
	@echo "[BUILD] [COPY] Copying $(notdir $^) header file to bin directory"
	@${MD} ${MD_FLAGS} $(dir $@)
	@${CP} ${CP_FLAGS} $^ $@

${_BIN}/Include/%.h: ${_LIB}/%.h
	@echo "[BUILD] [COPY] Copying $(notdir $^) header file to bin directory"
	@${MD} ${MD_FLAGS} $(dir $@)
	@${CP} ${CP_FLAGS} $^ $@

postbuild:
	@make postbuild_copyarchives
	@make postbuild_copyheaders

postbuild_copyarchives:
	@echo "[POSTBUILD] [COPY] Copying library archives to '${COPY_LIBRARY_ARCHIVES_TO}'"
	@${CP} ${CP_FLAGS} ${_BIN}/*.a ${COPY_LIBRARY_ARCHIVES_TO}

postbuild_copyheaders:
	@echo "[POSTBUILD] [COPY] Copying library headers to '${COPY_LIBRARY_HEADERS_TO}'"
	@${CP} ${CP_FLAGS} ${_BIN}/Include/* ${COPY_LIBRARY_HEADERS_TO}