NAME			=	SpxEngine.a

OBJDIR			=	obj

CXX				=	g++

AR				=	ar

ARFLAGS			=	rc

INDEXER			=	ranlib

RELEASEFLAGS	=	-O3 -Wnon-virtual-dtor -Wshadow			\
					-Winit-self	-Wredundant-decls 			\
					-Wcast-align -Wundef -Wfloat-equal		\
					-Winline -Wunreachable-code				\
					-Wmissing-declarations					\
					-Wmissing-include-dirs -Weffc++			\
					-Wswitch-enum -Wswitch-default			\
					-Wzero-as-null-pointer-constant			\
					-Wmain -pedantic -Wextra

DEBUGFLAGS		=	-g

DEFAULTFLAGS	=	-std=c++11 -fexceptions -Wall

# the file Makefile.engdirs contains the ENGINEDIRS variable
include Makefile.engdirs

SRDIRS			+=	$(ENGINEDIRS)

INCLUDEPFLAGS	:=	$(addprefix -I, $(SRDIRS))

CXXFLAGS		:=	$(DEFAULTFLAGS) $(INCLUDEPFLAGS)

LDLIBS			=	-lallegro								\
					-lallegro_image							\
					-lallegro_font							\
					-lallegro_primitive						\
					-lallegro_color

SRC				:=	$(wildcard $(addsuffix /*.cpp, $(SRDIRS)))

OBJ				:=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

RM				=	/bin/rm -f

MKDIR			=	/bin/mkdir -p

.PHONY: all clean fclean re debug release

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LDLIBS)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(INDEXER) $(NAME)

all: $(NAME)

debug: $(CXXFLAGS) += $(DEBUGFLAGS)
debug: $(NAME)

release: $(CXXFLAGS) += $(RELEASEFLAGS)
release: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
