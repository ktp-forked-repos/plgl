#export GLFLAGS=/usr/X11/include -L/usr/X11/lib -lGL -lGLU -lglut -lXmu 

TARGET=plgl

CFLAGS+=-DUSE_MACOS_GL -framework OpenGL -framework GLUT
SOBJ=$(PACKSODIR)/$(TARGET).$(SOEXT)
LIBS=-framework OpenGL -framework GLUT

all:	$(SOBJ)

$(SOBJ): c/$(TARGET).o
	mkdir -p $(PACKSODIR)
	$(LD) $(LDSOFLAGS) -o $@ $(SWISOLIB) $< $(LIBS)
	strip -x $@

check::
install::
clean:
	rm -f c/$(TARGET).o

distclean: clean
	rm -f $(SOBJ)

install-me:
	swipl -f none -g "pack_install('file:.',[upgrade(true)]), halt"

publish:
	swipl -f none -g "pack_property(plgl,download(D)), pack_install(D,[upgrade(true),interactive(false)]), halt"


