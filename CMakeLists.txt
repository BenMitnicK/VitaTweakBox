cmake_minimum_required(VERSION 2.8...3.25.1)

# VitaSDK defines
if( NOT DEFINED CMAKE_TOOLCHAIN_FILE )
  if( DEFINED ENV{VITASDK} )
  set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
  message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

# Project start
project(VitaTweakBox)
include("${VITASDK}/share/vita.cmake" REQUIRED)
set(VITA_APP_NAME "VitaTweakBox")
set(VITA_TITLEID  "VITATWEAK")
set(VITA_VERSION  "02.10")

# Flags and includes
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3 -Wno-unused-variable -Wno-unused-but-set-variable -Wno-format-truncation -fno-lto")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c+ + 11 -fno-rtti -fno-exceptions")
set(VITA_MKSFOEX_FLAGS "${VITA_MKSFOEX_FLAGS} -d PARENTAL_LEVEL=1")
set(VITA_MAKE_FSELF_FLAGS "${VITA_MAKE_FSELF_FLAGS} -a 0x2808000000000000")

add_subdirectory(src/modules/kernel)
add_subdirectory(src/modules/user)
add_subdirectory(src/modules/patch)
add_subdirectory(src/modules/usbdevice)

include_directories(
  src/modules/kernel
  src/modules/user
)

link_directories(
  ${CMAKE_CURRENT_BINARY_DIR}
)

# Builds
FUNCTION(ADD_RESOURCES out_var)
  SET(result)
  FOREACH(ref_f ${ARGN})
  if (IS_ABSOLUTE "${ref_f}")
    SET(out_f "${ref_f}.o")
    STRING(REPLACE "${CMAKE_CURRENT_BINARY_DIR}/" "" in_f "${ref_f}")
    SET(work_dir "${CMAKE_CURRENT_BINARY_DIR}")
  else()
    SET(out_f "${CMAKE_CURRENT_BINARY_DIR}/${ref_f}.o")
    SET(in_f "${ref_f}")
    SET(work_dir "${CMAKE_SOURCE_DIR}")
  endif()
  GET_FILENAME_COMPONENT(out_dir ${out_f} DIRECTORY)
  ADD_CUSTOM_COMMAND(OUTPUT ${out_f}
    COMMAND ${CMAKE_COMMAND} -E make_directory ${out_dir}
    COMMAND ${CMAKE_LINKER} -r -b binary -o ${out_f} ${in_f}
    DEPENDS ${ref_f}
    WORKING_DIRECTORY ${work_dir}
    COMMENT "Building resource ${out_f}"
    VERBATIM
    )
  LIST(APPEND result ${out_f})
  ENDFOREACH()
  SET(${out_var} "${result}" PARENT_SCOPE)
ENDFUNCTION()

file(GLOB res_files RELATIVE
  ${CMAKE_SOURCE_DIR}
  resources/umass.skprx
  resources/default/forecast/*.png
  resources/default/forecast/day/*.png
  resources/default/forecast/night/*.png
  resources/default/vitabackup/*.png
  resources/default/vitaident/*.png
  resources/default/vitashell/*.png
  resources/default/vitashell/*.ini
  resources/default/help/*.png
  resources/default/vtb/*.png
  resources/default/vtb/*.ini
  resources/*.txt
  resources/*.bin
  resources/*.xml
)

# ugly hack
add_resources(vitatweakbox_res
  ${res_files}
  ${CMAKE_CURRENT_BINARY_DIR}/src/modules/kernel/kernel.skprx
  ${CMAKE_CURRENT_BINARY_DIR}/src/modules/user/user.suprx
  ${CMAKE_CURRENT_BINARY_DIR}/src/modules/patch/patch.skprx
  ${CMAKE_CURRENT_BINARY_DIR}/src/modules/usbdevice/usbdevice.skprx
)

add_executable(VitaTweakBox
  ${vitatweakbox_res}
  src/main.c
  src/pfs.c
  src/main_context.c
  src/browser.c
  src/init.c
  src/usb.c
  src/qr.c
  src/io_process.c
  src/makezip.c
  src/package_installer.c
  src/refresh.c
  src/network_update.c
  src/network_download.c
  src/context_menu.c
  src/archive.c
  src/pbp.c
  src/psarc.c
  src/photo.c
  src/audioplayer.c
  src/file.c
  src/text.c
  src/hex.c
  src/sfo.c
  src/rif.c
  src/sqlite3.c
  src/coredump.c
  src/settings.c
  src/adhoc_dialog.c
  src/property_dialog.c
  src/uncommon_dialog.c
  src/message_dialog.c
  src/netcheck_dialog.c
  src/ime_dialog.c
  src/config.c
  src/theme.c
  src/language.c
  src/touch.c
  src/utils.c
  src/elf.c
  src/sha1.c
  src/sha256.c
  src/minizip/zip.c
  src/minizip/ioapi.c
  src/bm.c
  src/strnatcmp.c
  src/audio/vita_audio.c
  src/audio/player.c
  src/audio/id3.c
  src/audio/oggplayer.c
  src/audio/mp3player.c
  src/audio/mp3xing.c
  src/audio/lrcparse.c
  src/libmad/bit.c
  src/libmad/decoder.c
  src/libmad/fixed.c
  src/libmad/frame.c
  src/libmad/huffman.c
  src/libmad/layer12.c
  src/libmad/layer3.c
  src/libmad/stream.c
  src/libmad/synth.c
  src/libmad/timer.c
  src/database.c
  src/credits.c
  src/main_vtb.c
  src/help.c 
  src/vitaforecast/net.c
  src/vitaforecast/clock.c
  src/vitaforecast/weather.c
  src/vitaforecast/forecast.c
  src/vitaident/app.c
  src/vitaident/kernel.c
  src/vitaident/net.c
  src/vitaident/power.c
  src/vitaident/regmgr.c
  src/vitaident/vitaident_utils.c
  src/vitaident/vitaident.c
  src/vitabackup/fs.c
  src/vitabackup/log.c
  src/vitabackup/vitabackup.c
  src/vitabackup/menus/menu_backup.c
  src/vitabackup/menus/menu_options.c
  src/vitabackup/menus/menu_restore.c
  src/vitabackup/microtar/microtar.c
  src/vitabackup/microtar/microtar_read.c
  src/vitabackup/microtar/microtar_write.c
  src/vitabackup/progress_bar.c
  src/vitabackup/vitabackup_utils.c
  src/vitadatabase/database_file.c
  src/vitadatabase/database_utils.c
  src/loadimages.c
  src/book/book.c
  src/book/book_images.c
  src/book/images_menu.c
)

add_dependencies(VitaTweakBox vitashell_user_stubs)
add_dependencies(VitaTweakBox kernel.skprx)
add_dependencies(VitaTweakBox user.suprx)
add_dependencies(VitaTweakBox patch.skprx)
add_dependencies(VitaTweakBox usbdevice.skprx)
#add_dependencies(VitaTweakBox kernel.skprx-self)
#add_dependencies(VitaTweakBox user.suprx-self)
#add_dependencies(VitaTweakBox patch.skprx-self)
#add_dependencies(VitaTweakBox usbdevice.skprx-self)

target_link_libraries(VitaTweakBox
  ${CMAKE_CURRENT_BINARY_DIR}/src/modules/user/libVitaShellUser_stub_weak.a
  freetype #BMK
  ftpvita
  vita2d
  vorbisfile
  vorbis
  ogg
  png
  png16 #BMK
  jpeg
  z
  m
  c
  quirc
  onigmo
  archive
  bz2
  lzma
  crypto
  expat
  taihen_stub
  SceAppMgr_stub
  SceAppUtil_stub
  #SceAtrac_stub
  SceAudio_stub
  SceAudiodec_stub
  SceAVConfig_stub #BMK
  SceBtForDriver_stub #BMK
  SceCamera_stub
  SceCommonDialog_stub
  SceCompat_stub #BMK
  SceCtrl_stub
  SceDisplay_stub
  SceDriverUser_stub
  SceFios2_stub
  SceGxm_stub
  SceHid_stub #BMK
  SceIme_stub
  SceIofilemgr_stub #BMK
  SceHttp_stub
  SceLibKernel_stub
  SceMtpIfDriver_stub
  SceMusicExport_stub
  SceNet_stub
  SceNetCtl_stub
  SceNpDrm_stub
  ScePgf_stub
  ScePhotoExport_stub
  ScePower_stub
  ScePromoterUtil_stub
  ScePspnetAdhoc_stub
  SceRegistryMgr_stub
  SceShellSvc_stub
  SceSqlite_stub
  SceSsl_stub
  SceSysconForDriver_stub #BMK
  SceSysmodule_stub
  SceTouch_stub
  SceUdcd_stub
  SceUsbstorVStorDriver_stub
  SceVideoExport_stub
  SceVshBridge_stub
)

# Create Vita artifacts
vita_create_self(eboot.bin VitaTweakBox UNSAFE)
vita_create_vpk(VitaTweakBox.vpk ${VITA_TITLEID} eboot.bin
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE pkg/sce_sys/icon0.png sce_sys/icon0.png
	   pkg/sce_sys/pic0.png sce_sys/pic0.png
       pkg/sce_sys/livearea/contents/LiveArea_BG.png sce_sys/livearea/contents/LiveArea_BG.png
	   pkg/sce_sys/livearea/contents/LiveArea_Frame3.png sce_sys/livearea/contents/LiveArea_Frame3.png
	   pkg/sce_sys/livearea/contents/LiveArea_Frame4.png sce_sys/livearea/contents/LiveArea_Frame4.png
	   pkg/sce_sys/livearea/contents/ber3.png sce_sys/livearea/contents/ber3.png
       pkg/sce_sys/livearea/contents/LiveArea_Gate.png sce_sys/livearea/contents/LiveArea_Gate.png
       pkg/sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
	   pkg/sce_sys/manual/001.png sce_sys/manual/001.png
	   pkg/sce_sys/manual/002.png sce_sys/manual/002.png
	   pkg/sce_sys/manual/003.png sce_sys/manual/003.png
	   pkg/sce_sys/manual/004.png sce_sys/manual/004.png
	   pkg/sce_sys/manual/005.png sce_sys/manual/005.png
	   pkg/sce_sys/manual/006.png sce_sys/manual/006.png
	   pkg/sce_sys/manual/007.png sce_sys/manual/007.png
	   pkg/sce_sys/manual/008.png sce_sys/manual/008.png
	   pkg/sce_sys/manual/009.png sce_sys/manual/009.png
	   pkg/sce_sys/manual/010.png sce_sys/manual/010.png
	   pkg/sce_sys/manual/011.png sce_sys/manual/011.png
	   pkg/sce_sys/manual/012.png sce_sys/manual/012.png
	   pkg/sce_sys/manual/013.png sce_sys/manual/013.png
	   pkg/sce_sys/manual/014.png sce_sys/manual/014.png
	   pkg/sce_sys/manual/015.png sce_sys/manual/015.png  
	   pkg/sce_sys/manual/016.png sce_sys/manual/016.png  
	   pkg/sce_sys/manual/017.png sce_sys/manual/017.png  
	   pkg/sce_sys/manual/02/001.png sce_sys/manual/02/001.png
	   pkg/sce_sys/manual/02/002.png sce_sys/manual/02/002.png
	   pkg/sce_sys/manual/02/003.png sce_sys/manual/02/003.png
	   pkg/sce_sys/manual/02/004.png sce_sys/manual/02/004.png
	   pkg/sce_sys/manual/02/005.png sce_sys/manual/02/005.png
	   pkg/sce_sys/manual/02/006.png sce_sys/manual/02/006.png
	   pkg/sce_sys/manual/02/007.png sce_sys/manual/02/007.png
	   pkg/sce_sys/manual/02/008.png sce_sys/manual/02/008.png
	   pkg/sce_sys/manual/02/009.png sce_sys/manual/02/009.png
	   pkg/sce_sys/manual/02/010.png sce_sys/manual/02/010.png
	   pkg/sce_sys/manual/02/011.png sce_sys/manual/02/011.png
	   pkg/sce_sys/manual/02/012.png sce_sys/manual/02/012.png
	   pkg/sce_sys/manual/02/013.png sce_sys/manual/02/013.png
	   pkg/sce_sys/manual/02/014.png sce_sys/manual/02/014.png
	   pkg/sce_sys/manual/02/015.png sce_sys/manual/02/015.png
	   pkg/sce_sys/manual/02/016.png sce_sys/manual/02/016.png
	   pkg/sce_sys/manual/02/017.png sce_sys/manual/02/017.png
)

# for network update
add_custom_target(release
  COMMAND cp eboot.bin ../release/eboot.bin
  COMMAND cp VitaTweakBox.vpk_param.sfo ../release/param.sfo
  COMMAND cp VitaTweakBox.vpk ../release/VitaTweakBox.vpk
  COMMAND cp ../pkg/sce_sys/livearea/contents/template.xml ../release/template.xml
  DEPENDS eboot.bin
  DEPENDS VitaTweakBox.vpk
  DEPENDS VitaTweakBox.vpk_param.sfo
)

add_custom_target(send
  COMMAND curl -T eboot.bin ftp://$(PSVITAIP):1337/ux0:/app/${VITA_TITLEID}/
  DEPENDS eboot.bin
)

add_custom_target(copy
  COMMAND cp eboot.bin G:/app/${VITA_TITLEID}/eboot.bin
  DEPENDS eboot.bin
)
