.PHONY: tests build

tests:
	clang tests/utils.c \
		-D_POSIX_C_SOURCE=199309L \
		tests/test_vec3.c src/vec3.c \
		-std=c99 -Wall -Werror -fsanitize=address -g \
		-Iinclude \
		-o build/test_vec3

build:
	clang src/main.c src/app.c src/platform/platform_rgfw.c external/glad/glad.c src/renderer/shader.c src/arena.c \
		-std=c99 -Wall -Werror -fsanitize=address -g \
		-Iinclude \
		-Iexternal \
		-lGL -lX11 -lXrandr -lXcursor -lXi \
		-o build/main
