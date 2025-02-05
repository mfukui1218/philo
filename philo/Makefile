# 実行ファイル名
NAME = philo

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread -fsanitize=address

# ソースファイル
SRCS = main.c \
       init.c \
       monitor.c \
       actions.c \
       actions_2.c \
       utils.c \
       error.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# デフォルトターゲット
all: $(NAME)

# 実行ファイルの生成
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

# オブジェクトファイルの生成ルール
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# クリーンアップ
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

# リビルド
re: fclean all
