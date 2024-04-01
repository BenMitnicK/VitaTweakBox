#include "../main.h"

#include "database_file.h"

int exists(const char *path) {
	SceIoStat stat = {0};

	return sceIoGetstat(path, &stat) >= 0;
}

int touchFile(const char *path) {
	int ret;

	ret = sceIoOpen(path, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	sceIoClose(ret);

	return (ret >= 0);
}

int isDir(const char *path) {
	SceIoStat stat = {0};

	if (sceIoGetstat(path, &stat) < 0)
		return 0;

	return SCE_S_ISDIR(stat.st_mode);
}

/*int mkDir(const char *path, int mode) {
	if (isDir(path))
		return 1;

	int len = strlen(path);
	char npath[len];
	int start = 0;
	int ret;

	memset(npath, 0, len);

	for (int i=0; i<len; ++i) {
		npath[i] = path[i];

		if (!start < 2 && path[i] == ':')
			start = 1;

		if (path[i] != '/' || !start || isDir(npath))
			continue;

		ret = sceIoMkdir(npath, mode);
		if (ret < 0)
			return 0;
	}

	ret = sceIoMkdir(path, mode);
	if (ret < 0)
		return 0;

	return 1;
}*/

int copyFiles(const char *src, const char *dest) {
	if (!strcasecmp(src, dest))
		return 1;
	else if (!exists(src))
		return 0;

	void *buf = memalign(4096, 128 * 1024);
	int fsrc = sceIoOpen(src, SCE_O_RDONLY, 0);
	int fdst  = sceIoOpen(dest, SCE_O_WRONLY | SCE_O_CREAT, 0777);
	int read = 0, written = 0;
	SceIoStat stat;

	if (fsrc < 0 || fdst < 0) {
		free(buf);
		sceIoClose(fsrc);
		sceIoClose(fdst);
		return 0;
	}

	while (1) {
		read = sceIoRead(fsrc, buf, 128 * 1024);
		if (read < 0) {
			free(buf);
			sceIoClose(fsrc);
			sceIoClose(fdst);
			sceIoRemove(dest);
			return 0;

		} else if (!read) {
			break;
		}

		written = sceIoWrite(fdst, buf, read);
		if (written < 0) {
			free(buf);
			sceIoClose(fsrc);
			sceIoClose(fdst);
			sceIoRemove(dest);
			return 0;
		}
	}

	free(buf);

	// Inherit file stat
  	memset(&stat, 0, sizeof(SceIoStat));
  	sceIoGetstatByFd(fsrc, &stat);
	sceIoChstatByFd(fdst, &stat, 0x3B);

	sceIoClose(fsrc);
	sceIoClose(fdst);

	return 1;
}

int delete(const char *path) {
	if (!exists(path))
		return 1;

	SceUID dfd = sceIoDopen(path);
	int res = 0;

	if (dfd < 0) { // not a folder, file?
		if (exists(path) && sceIoRemove(path) >= 0) // file
			return 1;

		return 0;
	}

	do {
		SceIoDirent dir;
		char *newPath = NULL;
		size_t pLen = 0;
		int ret;

		memset(&dir, 0, sizeof(SceIoDirent));

		res = sceIoDread(dfd, &dir);

		if (res <= 0 || !strcmp(dir.d_name, ".") || !strcmp(dir.d_name, ".."))
			continue;

		pLen = sizeof(char) * (strlen(path) + strlen(dir.d_name) + 2);
		newPath = malloc(pLen);

		snprintf(newPath, pLen, "%s/%s", path, dir.d_name);

		if (SCE_S_ISDIR(dir.d_stat.st_mode))
			ret = delete(newPath) == 0 ? -1:1;
		else
			ret = sceIoRemove(newPath);

		free(newPath);
		if (ret < 0) {
			sceIoDclose(dfd);
			return 0;
		}
	} while (res > 0);

	sceIoDclose(dfd);

	if (sceIoRmdir(path) < 0)
		return 0;

	return 1;
}
