# Makefile for LetsTrust-TPM2Go_rst
# ltt2g_rst

CC=gcc
CFLAGS=-Wall -Wextra -std=c99 -g -D_DEFAULT_SOURCE
LDFLAGS= -lusb-1.0

all: ltt2g_rst

ltt2g_rst: ltt2g_rst.c ltt2g_rst.h
	$(CC) $(CFLAGS) ltt2g_rst.c -o ltt2g_rst $(LDFLAGS)

clean:
	rm -rf ltt2g_rst
