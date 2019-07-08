NAME			=	libspxengine.a

OBJDIR			=	obj

CXX				=	g++

AR				=	ar

ARFLAGS			=	rc

INDEXER			=	ranlib

DEBUGFLAGS		=	-g

RELEASEFLAGS	=	-O3 -D _NO_TEST_

WARNINGS		=	-Wall -Wshadow -Wswitch-enum -Wundef	\
					-Wredundant-decls -Wcast-align -Winline	\
					-Wzero-as-null-pointer-constant			\
					-Wnon-virtual-dtor -Wpedantic	 		\
					-Wmissing-include-dirs -Winvalid-pch

EXTRAWFLAGS		=	-Wextra -Wfloat-equal -Weffc++			\
					-Wunreachable-code -Wswitch-default		\
					-Wmissing-declarations

DEFAULTFLAGS	=	-std=c++11 -fexceptions $(WARNINGS)

# the file Makefile.eng contains:
# ENGINEDIRS variable
# ENGINEDEPEND variable
include Makefile.eng

SRDIRS			+=	$(ENGINEDIRS)

INCLUDEPFLAGS	:=	$(addprefix -I, $(SRDIRS))

CXXFLAGS		=	$(DEFAULTFLAGS) $(INCLUDEPFLAGS)

LDLIBS			=	$(ENGINEDEPEND)

LDFLAGS			=	

SRC				:=	$(wildcard $(addsuffix /*.cpp, $(SRDIRS)))

OBJ				:=	$(addprefix $(OBJDIR)/, $(SRC:.cpp=.o))

RM				=	/bin/rm -f

MKDIR			=	/bin/mkdir -p

.PHONY: all clean fclean re debug release extrawarnings

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(INDEXER) $(NAME)

all: $(NAME)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(NAME)

extrawarnings: CXXFLAGS += $(EXTRAWFLAGS)
extrawarnings: debug

release: CXXFLAGS += $(RELEASEFLAGS)
release: $(NAME)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
