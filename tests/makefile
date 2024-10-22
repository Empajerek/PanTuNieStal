CFLAGS = -Wall -Wextra -std=c17 -g
CPPFLAGS = -g -Wall -Wextra -std=c++17 -g
.PHONY: all clean

# Source files
C_SOURCES = strqueue_test_1.c strqueue_test_3.c strqueue_test_5.c strqueue_test_7.c
CPP_SOURCES = strqueue.cpp strqueue_test_2.cpp strqueue_test_4.cpp strqueue_test_6.cpp

# Object files
C_OBJS = $(C_SOURCES:.c=.o)
CPP_OBJS = $(CPP_SOURCES:.cpp=.o)

# Debug and non-debug object files
DBG_OBJS = ../build/strqueue_dbg.o
NODBG_OBJS = ../build/strqueue_nodbg.o

# Pattern rules
%.o: %.c
	gcc -c $(CFLAGS) $< -o $@

%.o: %.cpp
	g++ -c $(CPPFLAGS) $< -o $@

# Linking rules
define LINK_RULE
$1: $2 $(DBG_OBJS)
	g++ $2 $(DBG_OBJS) -o $1

$3: $2 $(NODBG_OBJS)
	g++ $2 $(NODBG_OBJS) -o $3
endef

$(eval $(call LINK_RULE,strqueue_test_1_dbg,strqueue_test_1.o,strqueue_test_1_nodbg))
$(eval $(call LINK_RULE,strqueue_test_2_dbg,strqueue_test_2.o,strqueue_test_2_nodbg))
$(eval $(call LINK_RULE,strqueue_test_3_dbg,strqueue_test_3.o,strqueue_test_3_nodbg))
$(eval $(call LINK_RULE,strqueue_test_4_dbg,strqueue_test_4.o,strqueue_test_4_nodbg))
$(eval $(call LINK_RULE,strqueue_test_5_dbg,strqueue_test_5.o,strqueue_test_5_nodbg))
$(eval $(call LINK_RULE,strqueue_test_6_dbg,strqueue_test_6.o,strqueue_test_6_nodbg))
$(eval $(call LINK_RULE,strqueue_test_7_dbg,strqueue_test_7.o,strqueue_test_7_nodbg))
$(eval $(call LINK_RULE,strqueue_test_8_dbg,strqueue_test_8.o,strqueue_test_8_nodbg))

all: strqueue_test_1_dbg strqueue_test_1_nodbg strqueue_test_2_dbg strqueue_test_2_dbg strqueue_test_2_nodbg strqueue_test_3_dbg strqueue_test_3_nodbg strqueue_test_4_dbg strqueue_test_4_nodbg strqueue_test_5_dbg strqueue_test_5_nodbg strqueue_test_6_dbg strqueue_test_6_nodbg strqueue_test_7_dbg strqueue_test_7_nodbg strqueue_test_8_dbg strqueue_test_8_nodbg

clean:
	rm -rf *.o *_dbg *_nodbg *_dbg_b *_dbg_a