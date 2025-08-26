LIBFT		= libft/
LIB_A		=${LIBFT}/libft.a
MLX_COMMIT	= ee35297
LIBMLX		= MLX42/

#Sources
SRCS_DIR 	= srcs/
SRC_DIR_BON	= srcs_bonus/

SRC			= main.c \
			  renderer.c \
			  camera.c \
			  ray.c \
			  light.c

DIR_MOV		= moves/
SRC_MOV		= cam_move.c \
			  light_move.c \
			  my_keyhook.c \
			  object_move.c \
			  rotation.c \
			  object_move_utils.c

DIR_PAR		= parsing/
SRC_PAR		= ft_ambient.c \
			  ft_atof.c \
			  ft_cam.c \
			  ft_cylinder.c \
			  ft_free.c \
			  ft_light.c \
			  ft_parsing.c \
			  ft_plane.c \
			  ft_sphere.c \
			  ft_parsing_utils.c \

DIR_SHAPE	= shape/
SRC_SHAPE	= plane.c \
			  sphere.c \
			  cylinder.c \
			  cylinder_utils.c \
			  object.c

SRC_SHAPE_BONUS = plane.c \
				cylinder.c \
				cylinder_utils.c

DIR_UTILS	= utils/
SRC_UTILS	= color.c

DIR_VEC		= vec3/
SRC_VEC		= vec3_operator_scalar.c \
			  vec3_operator.c \
			  vec3_math.c \
			  vec3_math_2.c

SRC			+= $(addprefix ${DIR_MOV}, ${SRC_MOV})
SRC			+= $(addprefix ${DIR_PAR}, ${SRC_PAR})
SRC			+= $(addprefix ${DIR_SHAPE}, ${SRC_SHAPE})
SRC			+= $(addprefix ${DIR_UTILS}, ${SRC_UTILS})
SRC			+= $(addprefix ${DIR_VEC}, ${SRC_VEC})

SRCS		= $(addprefix ${SRCS_DIR}, ${SRC})

#Bonus

SRC_BONUS_2	= main_bonus.c \
			  renderer_utils.c \
			  renderer.c \
			  perlin_noise.c \
			  checker_bump.c \
			  light.c \
			  cone.c \
			  moves/main_loop.c \
			  moves/object_move_bonus.c \
			  sphere_bonus.c \
			  object.c

SRC_PAR_B	= ft_ambient.c \
			  ft_atof.c \
			  ft_cam.c \
			  ft_free.c
SRC_PAR_B2	= ft_cone.c \
			  ft_parsing_utils.c \
			  ft_parsing.c \
			  ft_sphere.c \
			  ft_cylinder.c \
			  ft_plane.c \
			  ft_light.c \
			  ft_objet_utils.c

SRC_BONUS	= camera.c \
			  ray.c

SRC_BONUS	+= $(addprefix ${SRC_DIR_BON}, ${SRC_BONUS_2})
SRC_BONUS	+= $(addprefix ${SRC_DIR_BON}, $(addprefix ${DIR_MOV}, ${SRC_MOV}))
SRC_BONUS	+= $(addprefix ${SRC_DIR_BON}, $(addprefix ${DIR_PAR}, ${SRC_PAR_B2})) 
SRC_BONUS	+= $(addprefix ${DIR_PAR}, ${SRC_PAR_B})
SRC_BONUS	+= $(addprefix ${DIR_SHAPE}, ${SRC_SHAPE_BONUS})
SRC_BONUS	+= $(addprefix ${DIR_UTILS}, ${SRC_UTILS})
SRC_BONUS	+= $(addprefix ${DIR_VEC}, ${SRC_VEC})

srcs_bonus	= $(addprefix ${${SRCS_DIR, SRC_BONUS})

#Object
OBJS_DIR	= objects/
OBJS		= $(addprefix ${OBJS_DIR}, ${SRC:.c=.o})

OBJS_BONUS	= $(addprefix ${OBJS_DIR}, ${SRC_BONUS:.c=.o})

INCLUDES	= includes
NAME		= miniRT
NAME_2		= miniRT_bonus
RM			= rm -f
CFLAGS		= -Wall -Wextra -Werror -I ${INCLUDES} -g3 -O3
DEBUG		= -fsanitize=address -g3
CC			= cc

#Colors
LIGHT_GRAY	= \033[2m
ORANGE		= \033[1;33m
DARK_GRAY	= \033[0;90m
RED			= \033[0;91m
GREEN		= \033[0;92m
YELLOW		= \033[0;93m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
RESET		= \033[0m

#Forme
BOLD		= \033[1m
ITALIC		= \033[3m
UNDERLINE	= \033[4m
CROSS		= \033[9m
FLASH		= \033[5m
NEGATIF		= \033[7m

all:			${LIBMLX} libmlx ${NAME} head

${OBJS_DIR}%.o: ${SRCS_DIR}%.c | ${OBJS_DIR}
				@${CC} ${CFLAGS} -c $< -o $@

${NAME}:		${OBJS} ${LIB_A}
				@${CC} ${CFLAGS} ${OBJS} -L${LIBFT} -lft -L${LIBMLX}/build -lmlx42 -ldl -lglfw -pthread -lm -o $@
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

libmlx:
				@cmake ${LIBMLX} -B ${LIBMLX}/build && make -sC ${LIBMLX}/build -j4

${OBJS_DIR}:
				@mkdir -p ${OBJS_DIR}
				@mkdir -p ${OBJS_DIR}${DIR_MOV}
				@mkdir -p ${OBJS_DIR}${DIR_PAR}
				@mkdir -p ${OBJS_DIR}${DIR_SHAPE}
				@mkdir -p ${OBJS_DIR}${DIR_UTILS}
				@mkdir -p ${OBJS_DIR}${DIR_VEC}
				@mkdir -p ${OBJS_DIR}${SRC_DIR_BON}
				@mkdir -p ${OBJS_DIR}${SRC_DIR_BON}${DIR_MOV}
				@mkdir -p ${OBJS_DIR}${SRC_DIR_BON}${DIR_PAR}

${LIB_A}:
				@echo "${BLUE}'libft.a' is compiling... 🔥${RESET}"
				@make -sC ${LIBFT}

clean:
				@${RM} ${OBJS}
				@${RM} ${OBJS_BONUS}
				@${RM} -r ${OBJS_DIR}
				@make clean -sC ${LIBFT}
				@echo "${RED}'${NAME}' objects are deleted ! 👍${RESET}"

fclean:			clean
				@${RM} ${NAME} ${NAME_2} ${LIBFT}libft.a
				@echo "${RED}'${NAME}', '${NAME_2}' and 'libft.a' are deleted ! 👍${RESET}"

re:				fclean all

head:			
				@echo
				@echo
				@echo "    /|    //| |                                //   ) )  /__  ___/"
				@echo "   //|   // | |    ( )       __       ( )     //___/ /     / /"
				@echo "  // |  //  | |   / /     //   ) )   / /     / ___ (      / /"
				@echo " //  | //   | |  / /     //   / /   / /     //   | |     / /"
				@echo "//   |//    | | / /     //   / /   / /     //    | |    / /"
				@echo
				@echo

bonus:			${LIBMLX} libmlx ${NAME_2} head

rebonus:		fclean bonus

debug:			override CFLAGS += ${DEBUG}
debug:			re

${NAME_2}:		${OBJS_BONUS} ${LIB_A}
				@${CC} ${CFLAGS} ${OBJS_BONUS} -L${LIBFT} -lft -L${LIBMLX}/build -lmlx42 -ldl -lglfw -pthread -lm -o $@
				@echo "${YELLOW}'$@' is compiled ! ✅${RESET}"

${LIBMLX}:
				@echo "${CYAN}${ITALIC}Cloning of MLX42 Codam...${RESET}"
				@git clone https://github.com/codam-coding-college/MLX42.git $@
				@cd $@ && git checkout ${MLX_COMMIT}
				@echo "${CYAN}Clonne is ready !!!${RESET}"

.PHONY:			all clean fclean re libmlx bonus head rebonus

