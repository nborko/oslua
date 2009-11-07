TARGET=oslua

# lua location
LUA_SRC=lua-5.1.4
LUA_LIB=$(LUA_SRC)/src/liblua.a

# oslib mod location
OSLIB_SRC=oslib
OSLIB=$(OSLIB_SRC)/libosl.a

OSLUA_OBJS= osl.o \
            drawing.o \
            images.o \
            math.o \
            audio.o \
            controller.o \
            dialog.o \
            network.o \
            message.o \
            text.o \
            libfs.o

TYPE_OBJS=  enums.o \
            font.o \
            image.o

MAIN_OBJS=  module_info.o \
            main.o \
            callbacks.o \
            userdata.o

OBJS=       $(MAIN_OBJS) $(addprefix types/,$(TYPE_OBJS)) $(addprefix modules/,$(OSLUA_OBJS))

LIBS=-llua -losl -lmikmod -lmmio -lpng -ljpeg -lz -lm -lpspgu -lpspge -lpspaudiolib -lpspaudio -lpspaudiocodec -lpsppower -lpspgum_vfpu -lpspvfpu -lpsphprm -lpsppower -lpsphttp -lpspssl -lpspwlan -lpspnet_adhocmatching -lpspnet_adhoc -lpspnet_adhocctl

PSP_EBOOT_TITLE=OldSchool Lua (1.1.0-0.1-beta1)
PSP_EBOOT_ICON=ICON0.PNG
#PSP_EBOOT_PIC1=PIC1.PNG
EXTRA_TARGETS=EBOOT.PBP
PSP_FW_VERSION=401

INCDIR=$(LUA_SRC)/src $(OSLIB_SRC) $(PSPDEV)/psp/include
LIBDIR=$(LUA_SRC)/src $(OSLIB_SRC)
CFLAGS=-O2 -G0 -Wall -Werror
CXXFLAGS=$(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS=$(CFLAGS)

release: $(LUA_LIB) $(OSLIB) $(OBJS) all

$(TARGET).elf: $(LUA_LIB) $(OSLIB)

$(LUA_SRC):
	wget http://www.lua.org/ftp/$(LUA_SRC).tar.gz
	tar zxf $(LUA_SRC).tar.gz
	rm $(LUA_SRC).tar.gz
	patch -p0 < psplua.patch

$(LUA_LIB): $(LUA_SRC)
	(cd $(LUA_SRC)/src; $(MAKE))


$(OSLIB_SRC):
	svn co http://svn2.assembla.com/svn/oslibmod/trunk/ $(OSLIB_SRC)
	# libosl.a is prebuilt in svn? nuke it
	rm -f $(OSLIB)

$(OSLIB): $(OSLIB_SRC)
	(cd $(OSLIB_SRC); $(MAKE) lib)

$(OBJS): userdata.h oslua.h

install: all
	rm -rf /media/disk/PSP/GAME5XX/OSLua
	mkdir -p /media/disk/PSP/GAME5XX/OSLua
	cp --parents EBOOT.PBP script.lua `find samples -name .svn -prune -o -type f -a -print` /media/disk/PSP/GAME5XX/OSLua

dist:
	(cd ..; rm -f oslua.zip; zip oslua.zip oslua/EBOOT.PBP oslua/script.lua; zip -gr oslua.zip oslua/samples -x \*.svn/\*)

distclean: clean
	rm -rf $(LUA_SRC) $(OSLIB_SRC)

include $(PSPSDK)/lib/build.mak

### OBSOLETE RULES RETAINED FOR REFERENCE ###
PRX_DIRS=   audio \
            controller \
            drawing

PRX_OBJS=   oslua_audio.o \
            oslua_controller.o \
            oslua_drawing.o

prx:
	@for i in $(PRX_DIRS); do echo "make all in $$i..."; (cd modules/prx/$$i; $(MAKE) clean files; cp oslua_$$i.prx ../..); done
