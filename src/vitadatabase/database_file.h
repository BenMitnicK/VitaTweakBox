#pragma once

#include "../main.h"

int exists(const char *path);
int touchFile(const char *path);
int isDir(const char *path);
//int mkDir(const char *path, int mode);
int copyFiles(const char *src, const char *dest);
int delete(const char *path);
