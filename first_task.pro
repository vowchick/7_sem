QMAKE_CXXFLAGS += -Og -ggdb3 -mfpmath=sse -fstack-protector-all -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
QMAKE_CXXFLAGS += -O0 -ggdb3

SOURCES += \
        funcs.cpp \
        gas_one.cpp \
        io.cpp \
        main.cpp

HEADERS += \
    header.h \
    structs.h
