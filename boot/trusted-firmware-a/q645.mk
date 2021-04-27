TOPDIR = ./
MAK_WRAPPER_ENV=Y
#NO_PARALLEL_BUILD=1
#include $(TOPDIR)build/core/config_gemini.mak

TFA_ROOT = $(TOPDIR)/boot/trusted-firmware-a/
TFA_OUT_ROOT = $(TFA_ROOT)build/
BL31_BIN_NAME = bl31.img
BUILD_TOOLS_ROOT_ABS = $(TOPDIR)crossgcc
CONFIG_GLB_GMNCFG_MODEL_TFA_CFG = "q645"
ECHO = echo
MAKE_JOBS = -j 30 -l 24



###################################
#  Define this project parameter  #
###################################
PRJ_NAME               = "TFA"
PRJ_BUILD_ROOT         = $(TFA_ROOT)
PRJ_OUTPUT_FILE        = $(TFA_OUT_ROOT)$(BL31_BIN_NAME)
TARGET_OUTPUT_FILE     = $(GEMINI_BL31_IMAGE)

TARGET_OUTPUT_DEL_FILE = $(TARGET_OUTPUT_FILE)
PRJ_EXT_PARA           =

CROSS     = ../../crossgcc/gcc-arm-9.2-2019.12-x86_64-aarch64-none-linux-gnu/bin/aarch64-none-linux-gnu-

BL31_LADDR = 0x1fffc0
BL31_RADDR = 0x200000

.PHONY: all init build install update clean distclean

all:
	@:

init:
	@echo "Init TFA"
	@$(CROSS)gcc -v 2>/dev/null ; \
	 if [ "$$?" != "0" ];then \
		echo "Not found compiler: $(CROSS)gcc" ; \
		exit 1; \
	 fi
#	@$(ECHO) "sinclude $(GEMINI_PLF_CFG_PATH)" > $(PRJ_EXT_CFG_ROOT)$(PRJ_EXT_CFG_FILE)
#	@$(CALL_WRAPPER_TARGET) update_global_cfg_h
	@$(MAKE) $(PRJ_EXT_PARA) -C $(PRJ_BUILD_ROOT) \
		CROSS_COMPILE=$(CROSS) PLAT=$(CONFIG_GLB_GMNCFG_MODEL_TFA_CFG) DEBUG=0 clean

build:
#	@$(PRJ_SHOWBUILDMESG)
	@echo "Build TFA"
	$(RM) -f $(PRJ_OUTPUT_FILE)
	$(MAKE) ${MAKE_JOBS} $(PRJ_EXT_PARA) -C $(PRJ_BUILD_ROOT) \
		CROSS_COMPILE=$(CROSS) PLAT=$(CONFIG_GLB_GMNCFG_MODEL_TFA_CFG) DEBUG=0 LOG_LEVEL=40
	@cd $(PRJ_BUILD_ROOT) ; \
	 BL31_BIN=build/q645/release/bl31.bin ; \
	 BL31_IMG=build/bl31.img ; \
	 ./tools/add_uhdr.sh "BL31" $$BL31_BIN $$BL31_IMG $(BL31_LADDR) $(BL31_RADDR)
#	@$(PRJ_CHKBUILDRESULT)

install:
	@:
update:
#	@$(PRJ_BUILDUPDTAE)

distclean clean:
	@$(MAKE) ${MAKE_JOBS} $(PRJ_EXT_PARA) -C $(PRJ_BUILD_ROOT) \
		CROSS_COMPILE=$(CROSS) PLAT=q645 DEBUG=0 $@
	@$(RM) -f $(PRJ_OUTPUT_FILE)
#	@$(PRJ_CHKCLEANRESULT)
