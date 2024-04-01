#include "../main.h"

#include "database_utils.h"
#include "../sqlite3.h"

static char logFile[255] = {0};

int init() {
	SceDateTime time;
	FILE *log;
	int ret;

	sceRtcGetCurrentClockLocalTime(&time);
	snprintf(logFile, sizeof(logFile), LOG_PATH"/%d-%d-%d-database.txt", time.month, time.day, time.year);

	return 1;
}

int manageDb(char cmd) {
	const char *sqlCountPages = "SELECT COUNT(*) FROM tbl_appinfo_page WHERE pageNo >= 0";
	const char *sqlSaveAppsPos = "SELECT pageId, pos, title, titleId, reserved01, quote(reserved05) FROM tbl_appinfo_icon";
	const char *sqlSavePageId = "SELECT pageId, pageNo, reserved01 FROM tbl_appinfo_page";
	char *pathToCheck[] = { ICO_PATH, PID_PATH, "ux0:iconlayout.ini.bak" };
	FILE *log = NULL, *iconsPosBak = NULL, *pageIdBak = NULL;
	sqlite3 *db = NULL;
	sqlite3_stmt *stmt = NULL;
	int ret = 0;

	log = fopen(logFile, "a");
	if (log == NULL)
		return 0;

	for (int i=0; i<3; ++i) {
		if (!exists(pathToCheck[i]))
			continue;

		ret = delete(pathToCheck[i]);
		if (!ret)
			goto exit;
	}

	iconsPosBak = fopen(ICO_PATH, "w");
	pageIdBak = fopen(PID_PATH, "w");

	if (iconsPosBak == NULL || pageIdBak == NULL) {
		fprintf(log, "export: cannot create files\n");
		goto exit;
	}

	ret = sqlite3_open(APPDB, &db);
	if (ret != SQLITE_OK) {
		fprintf(log, "export: cannot open app.db\n");
		goto exit;
	}

	// Pages Count
	ret = sqlite3_prepare_v2(db, sqlCountPages, -1, &stmt, 0);
	if (ret != SQLITE_OK) {
		fprintf(log, "export: sqlite error [pages]\n");
		goto exit;
	}

	if (sqlite3_step(stmt) == SQLITE_ROW)
		fprintf(iconsPosBak, "%s %d %d %s %d %s\n", "pg", sqlite3_column_int(stmt, 0), -1, "(null)", -1, "(null)");

	sqlite3_finalize(stmt);

	// Save positions
	ret = sqlite3_prepare_v2(db, sqlSaveAppsPos, -1, &stmt, 0);
	if (ret != SQLITE_OK) {
		fprintf(log, "export: sqlite error [positions]\n");
		goto exit;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW) {
		char title[250] = {0};
		char *fixed = NULL;
		int len;
		size_t sz;

		sqlite3_snprintf(sizeof(title), title, "%s", sqlite3_column_text(stmt, 2));

		len = strlen(title);
		sz = sizeof(char) * (len + 5);
		fixed = malloc(sz);

		fixed[0] = 0;
		for (int i=0; i<len; ++i) {
			if (title[i] == '\n') {
				snprintf(fixed, sz, "%s\\n", fixed);
				continue;
			}

			snprintf(fixed, sz, "%s%c", fixed, title[i]);
		}

		fprintf(iconsPosBak, "%s %d %d %s %d %s\n", sqlite3_column_text(stmt, 3), sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), fixed, sqlite3_column_int(stmt, 4), sqlite3_column_blob(stmt, 5));
		free(fixed);
	}

	sqlite3_finalize(stmt);

	// Save Page IDs
	ret = sqlite3_prepare_v2(db, sqlSavePageId, -1, &stmt, 0);
	if (ret != SQLITE_OK) {
		fprintf(log, "export: sqlite error [IDs]\n");
		goto exit;
	}

	while (sqlite3_step(stmt) == SQLITE_ROW)
		fprintf(pageIdBak, "%d %d %d\n", sqlite3_column_int(stmt, 0), sqlite3_column_int(stmt, 1), sqlite3_column_int(stmt, 2));

	sqlite3_finalize(stmt);

	ret = copyFiles("ux0:iconlayout.ini", "ux0:iconlayout.ini.bak");
	if (!ret) {
		fprintf(log, "export: iconlayout.ini error\n");
		goto exit;
	}

	fprintf(log, "success.");

	sqlite3_close(db);
	fclose(iconsPosBak);
	fclose(pageIdBak);
	fclose(log);

	return 1;

exit:
	sqlite3_close(db);
	fclose(iconsPosBak);
	fclose(pageIdBak);
	fclose(log);

	return 0;
}

int importLASett() {
	const char *sqlP0[] = {
			"PRAGMA foreign_keys = off",
			"create table tbl_appinfo_icon_n as select * from tbl_appinfo_icon",
			"create table tbl_appinfo_page_n as select * from tbl_appinfo_page",
			"drop table tbl_appinfo_icon",
			"drop table tbl_appinfo_page"
	};
	const char *sqlP1[] = {
			"CREATE TABLE tbl_appinfo_page(pageId INTEGER PRIMARY KEY NOT NULL ,pageNo INT NOT NULL,themeFile TEXT,bgColor INT,texWidth INT,texHeight INT,imageWidth INT,imageHeight INT,reserved01,reserved02,reserved03,reserved04,reserved05)",
			"CREATE INDEX idx_page_no ON tbl_appinfo_page ( pageNo )",
			"insert into tbl_appinfo_page select * from tbl_appinfo_page_n",
			"drop table tbl_appinfo_page_n",
			"CREATE TABLE tbl_appinfo_icon(pageId REFERENCES tbl_appinfo_page(pageId) ON DELETE RESTRICT NOT NULL,pos INT NOT NULL,iconPath TEXT,title TEXT COLLATE NOCASE,type NOT NULL,command TEXT, titleId TEXT,icon0Type NOT NULL,parentalLockLv INT,status INT,reserved01,reserved02,reserved03,reserved04,reserved05,PRIMARY KEY(pageId, pos))",
			"CREATE INDEX idx_icon_pos ON tbl_appinfo_icon ( pos, pageId )",
			"CREATE INDEX idx_icon_title ON tbl_appinfo_icon (title, titleId, type)",
			"insert into tbl_appinfo_icon select * from tbl_appinfo_icon_n",
			"drop table tbl_appinfo_icon_n",
			"CREATE TRIGGER tgr_deletePage2 AFTER DELETE ON tbl_appinfo_page WHEN OLD.pageNo >= 0 BEGIN UPDATE tbl_appinfo_page SET pageNo = pageNo - 1 WHERE tbl_appinfo_page.pageNo > OLD.pageNo; END",
			"CREATE TRIGGER tgr_insertPage2 BEFORE INSERT ON tbl_appinfo_page WHEN NEW.pageNo >= 0 BEGIN UPDATE tbl_appinfo_page SET pageNo = pageNo + 1 WHERE tbl_appinfo_page.pageNo >= NEW.pageNo; END",
			"PRAGMA foreign_keys = on"
	};
	FILE *log = NULL, *iconsPosBak = NULL, *pageIdBak = NULL;
	char buff[40000] = {0}, sqlPgNum[256] = {0}, *error = NULL;
	sqlite3 *db = NULL;
	int pgNumb, ret;

	log = fopen(logFile, "a");
	if (log == NULL)
		return 0;

	if (!exists(ICO_PATH) || !exists(PID_PATH)) {
		fprintf(log, "import: no live area settings found!\ndone.\n");
		fclose(log);
		return 2;
	}

	ret = delete(ADB_PATH);
	if (!ret) {
		fprintf(log, "import: cannot delete old files\n");
		fclose(log);
		return 0;
	}

	iconsPosBak = fopen(ICO_PATH, "r");
	pageIdBak = fopen(PID_PATH, "r");

	if (iconsPosBak == NULL || pageIdBak == NULL) {
		fprintf(log, "import: cannot create files\n");
		goto exit;
	}

	ret = sqlite3_open(APPDB, &db);
	if (ret != SQLITE_OK) {
		fprintf(log, "import: cannot open app.db\n");
		goto exit;
	}

	// Prepare the database
	for (int i=0; i<5; ++i) {
		ret = sqlite3_exec(db, sqlP0[i], NULL, NULL, &error);
		if (ret != SQLITE_OK) {
			fprintf(log, "import: sql: %s\nerror: %s\n", sqlP0[i], error);
			sqlite3_free(error);
			goto exit;
		}

	}

	while (fgets(buff, 40000, iconsPosBak) != NULL) {
		char id[11] = {0};
		char title[200] = {0};
		char reserved05[40000] = {0};
		int pageId, pos, reserved01;
		char sql[40500] = {0};

		sscanf(buff, "%s %d %d %s %d %s", id, &pageId, &pos, title, &reserved01, reserved05);

		if (!strcmp(id, "pg")) {
			pgNumb = pageId;
			fprintf(log, "import: found page: %d pages\n", pgNumb);
			continue;
		}

		if (!strcmp(id, "(null)")) {
			sqlite3_stmt *stmt = NULL;
			char sqlCountFold[256] = {0};
			int exists = 0;

			fprintf(log, "import: found folder\n");
			snprintf(sqlCountFold, sizeof(sqlCountFold), "SELECT COUNT(*) FROM tbl_appinfo_icon_n WHERE reserved01 = %d", reserved01);

			ret = sqlite3_prepare_v2(db, sqlCountFold, -1, &stmt, 0);
			if (ret != SQLITE_OK)
				continue;

			if (sqlite3_step(stmt) == SQLITE_ROW)
				exists = sqlite3_column_int(stmt, 0);

			sqlite3_finalize(stmt);

			if (!exists) {
				sqlite3_snprintf(sizeof(sql), sql,
				         "INSERT INTO tbl_appinfo_icon_n (reserved05, reserved04, reserved03, reserved02, reserved01, status, parentalLockLv, icon0Type, titleId, command, type, title, iconPath, pos, pageId ) VALUES (%s, NULL, NULL, NULL, %d, 0, 0, 7, NULL, NULL, 5, '%q', NULL, %d, %d)",
				         reserved05, reserved01, title, pos, pageId);
			} else {
				snprintf(sql, sizeof(sql),
				         "UPDATE tbl_appinfo_icon_n SET pos = %d, pageId = %d WHERE reserved01 = %d",
				         pos, pageId, reserved01);
			}
		} else {
			fprintf(log, "import: found icon\n");

			snprintf(sql, sizeof(sql),
			         "UPDATE tbl_appinfo_icon_n SET pageId = %d, pos = %d WHERE titleId = '%s'",
			         pageId, pos, id);
		}

		ret = sqlite3_exec(db, sql, NULL, NULL, &error);
		if (ret != SQLITE_OK) {
			fprintf(log, "import: sql: %s\nerror: %s\n", sql, error);
			sqlite3_free(error);
			goto exit;
		}
	}

	while (fgets(buff, 255, pageIdBak) != NULL) {
		int pageId, pgNo, reserved01;
		char sql[500] = {0};

		sscanf(buff, "%d %d %d", &pageId, &pgNo, &reserved01);

		if (pgNo != -100000000 && pgNo < 0) {
			sqlite3_stmt *stmt = NULL;
			char sqlCountFold[256] = {0};
			int exists = 0;

			fprintf(log, "import: found folder: tbl_appinfo_page\n");
			snprintf(sqlCountFold, sizeof(sqlCountFold), "SELECT COUNT(*) FROM tbl_appinfo_page_n WHERE pageNo = %d", pgNo);

			ret = sqlite3_prepare_v2(db, sqlCountFold, -1, &stmt, 0);
			if (ret != SQLITE_OK)
				continue;

			if (sqlite3_step(stmt) == SQLITE_ROW)
				exists = sqlite3_column_int(stmt, 0);

			sqlite3_finalize(stmt);

			if (!exists) {
				snprintf(sql, sizeof(sql),
				         "INSERT INTO tbl_appinfo_page_n (reserved05, reserved04, reserved03, reserved02, reserved01, imageHeight, imageWidth, texHeight, texWidth, bgColor, themeFile, pageNo, pageId ) VALUES (NULL, NULL, NULL, NULL, %d, 0, 0, 0, 0, 0, NULL, %d, %d)",
				         reserved01, pgNo, pageId);
			} else {
				snprintf(sql, sizeof(sql),
				         "UPDATE tbl_appinfo_page_n SET pageId = %d WHERE pageNo = %d",
				         pageId, pgNo);
			}
		} else {
			fprintf(log, "import: found icon: tbl_appinfo_page\n");
			snprintf(sql, sizeof(sql), "UPDATE tbl_appinfo_page_n SET pageId = %d WHERE pageNo = %d", pageId, pgNo);
		}

		ret = sqlite3_exec(db, sql, NULL, NULL, &error);
		if (ret != SQLITE_OK) {
			fprintf(log, "import: sql: %s\nerror: %s\n", sql, error);
			sqlite3_free(error);
			goto exit;
		}
	}

	snprintf(sqlPgNum, sizeof(sqlPgNum), "DELETE FROM tbl_appinfo_page_n WHERE pageNo > %d", (pgNumb-1));

	ret = sqlite3_exec(db, sqlPgNum, NULL, NULL, &error);
	if (ret != SQLITE_OK) {
		fprintf(log, "import: sql: %s\nerror: %s\n", sqlPgNum, error);
		sqlite3_free(error);
		goto exit;
	}

	// Apply all the changes
	for (int j=0; j<12; ++j) {
		ret = sqlite3_exec(db, sqlP1[j], NULL, NULL, &error);
		if (ret != SQLITE_OK) {
			fprintf(log, "import: sql:\n%s\nerror:\n%s\n", sqlP1[j], error);
			sqlite3_free(error);
			goto exit;
		}
	}

	ret = copyFiles("ux0:iconlayout.ini.bak", "ux0:iconlayout.ini");
	if (!ret)
		fprintf(log, "import: cannot restore iconlayout.ini\n");

	fprintf(log, "success.");

	fclose(log);
	fclose(iconsPosBak);
	fclose(pageIdBak);
	sqlite3_close(db);

	copyFiles(APPDB, ADB_PATH);
	delete("ux0:iconlayout.ini.bak");

	return 1;

exit:
	fclose(iconsPosBak);
	fclose(pageIdBak);
	copyFiles(APPDB, ADB_PATH);

	if (db != NULL) {
		ret = sqlite3_exec(db, "ROLLBACK", NULL, NULL, &error);
		if (ret != SQLITE_OK) {
			fprintf(log, "exit: rollback fail: %s\n", error);
			sqlite3_free(error);
		}

		sqlite3_close(db);
	}

	fclose(log);

	return 0;
}
