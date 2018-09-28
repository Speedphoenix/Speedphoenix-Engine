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

SRDIRS			=	Configurable							\
					Engine									\
					Engine/Non_Classes						\
					Engine/Transform						\
					Engine/Behaviours						\
					Engine/Behaviours/Collider				\
					Engine/Behaviours/Animator				\
					Engine/Behaviours/Animator/Animation	\
					Engine/Behaviours/Animator/Composing

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

.PHONY: all clean fclean re

$(NAME): $(OBJ)
	$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	$(INDEXER) $(NAME)

all: $(NAME)

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: $(NAME)

release: CXXFLAGS += $(RELEASEFLAGS)
release: $(NAME)

$(OBJDIR)/%.o: %.cpp
	$(MKDIR) $(dir $@)
	$(CXX) -c $< -o $@ $(CXXFLAGS) $(LDLIBS)

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean $(NAME)
