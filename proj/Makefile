PROG=proj

SRCS = proj.c utils.c graphic.c sprite.c timer.c keyboard.c mouse.c scenario.c character.c mushroom.c birds_and_crystals.c letters_and_numbers.c scoreboard.c menu.c events.c game.c rtc.c

# __LCOM_OPTIMIZED__ disables most of the LCF's overhead (and functionality!)
CPPFLAGS += -pedantic -D __LCOM_OPTIMIZED__

DPADD += ${LIBLCF}
LDADD += -llcf

.include <minix.lcom.mk>
