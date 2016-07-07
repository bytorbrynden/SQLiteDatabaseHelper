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

TARGET := ${_BIN}/${NAME}.a

MD := mkdir
MD_FLAGS := -p

RM := rm
RM_FLAGS := -rf

CC := gcc
CC_FLAGS := -c -Wall -Werror -ggdb -I${_INC} -I${_LIB}

CP := cp
CP_FLAGS := -r

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
all: prepare clean objects archive

prepare:
	if [ ! -d ${_OUT} ]; then ${MD} ${MD_FLAGS} ${_OUT}; fi
	if [ ! -d ${_OBJ} ]; then ${MD} ${MD_FLAGS} ${_OBJ}; fi
	if [ ! -d ${_BIN} ]; then ${MD} ${MD_FLAGS} ${_BIN}; fi

clean:
	${RM} ${RM_FLAGS} ${_OBJ}/*
	${RM} ${RM_FLAGS} ${_BIN}/*

objects: ${OBJS} ${LIB_OBJS}

archive:
	${AR} ${AR_FLAGS} ${TARGET} $(shell find ${_OBJ} -type f -name "*.o")
	make ${SRC_HEADERS}
	make ${LIB_HEADERS}

${_OBJ}/srcs/%.o: ${_SRC}/%.c
	${MD} ${MD_FLAGS} $(dir $@)
	${CC} ${CC_FLAGS} $^ -o $@

${_OBJ}/libs/%.o: ${_LIB}/%.c
	${MD} ${MD_FLAGS} $(dir $@)
	${CC} ${CC_FLAGS} $^ -o $@

${_BIN}/Include/%.h: ${_INC}/%.h
	${MD} ${MD_FLAGS} $(dir $@)
	${CP} ${CP_FLAGS} $^ $@

${_BIN}/Include/%.h: ${_LIB}/%.h
	${MD} ${MD_FLAGS} $(dir $@)
	${CP} ${CP_FLAGS} $^ $@