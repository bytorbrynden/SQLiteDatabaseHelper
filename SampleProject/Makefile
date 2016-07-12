#
# SQLiteDatabaseHelperTest/Makefile
#
NAME := testsqlitedatabasehelper
ROOT := ${CURDIR}

_SRC := ${ROOT}/Source
_INC := ${ROOT}/Include
_LIB := ${ROOT}/Libraries
_OUT := ${ROOT}/Build
_OBJ := ${_OUT}/obj
_BIN := ${_OUT}/bin
TEST := ${ROOT}/Test

TARGET := ${_BIN}/${NAME}
TARGET_FLAGS := $(shell find ${TEST} -type f -name "*.db")

MD := mkdir
MD_FLAGS := -p

RM := rm
RM_FLAGS := -rf

CC := gcc
CC_FLAGS := -Wall -Werror -ggdb -I${_INC} -I${_LIB}/SQLiteDatabaseHelper
LD_FLAGS := -L${_LIB}/SQLiteDatabaseHelper/ -lsqlitedatabasehelper

VAL := valgrind
VAL_FLAGS := --leak-check=yes --track-origins=yes

CP := cp
CP_FLAGS := -r

SRCS := $(shell find ${_SRC} -type f -name "*.c")
OBJS := $(patsubst ${_SRC}/%.c, ${_OBJ}/srcs/%.o, ${SRCS})

.PHONY: all
all: prepare clean objects compile

prepare:
	@if [ ! -d ${_OUT} ]; then ${MD} ${MD_FLAGS} ${_OUT}; fi
	@if [ ! -d ${_OBJ} ]; then ${MD} ${MD_FLAGS} ${_OBJ}; fi
	@if [ ! -d ${_BIN} ]; then ${MD} ${MD_FLAGS} ${_BIN}; fi

clean:
	@${RM} ${RM_FLAGS} ${_OBJ}/*
	@${RM} ${RM_FLAGS} ${_BIN}/*

objects: ${OBJS}

compile:
	@${CC} ${CC_FLAGS} ${LD_FLAGS} -o ${TARGET} $(shell find ${_OBJ} -type f -name "*.o")
	@chmod +x ${TARGET}

launch:
	@${TARGET} ${TARGET_FLAGS}

${VAL}:
	@$@ ${VAL_FLAGS} ${TARGET} ${TARGET_FLAGS}

${_OBJ}/srcs/%.o: ${_SRC}/%.c
	@${MD} ${MD_FLAGS} $(dir $@)
	@${CC} -c ${CC_FLAGS} $^ -o $@