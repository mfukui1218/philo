# 実行ファイル名
NAME = philo

# コンパイラとフラグ
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pthread

# ソースファイル
SRCS = main.c \
       philo.c \
       actions.c \
       utils.c

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
