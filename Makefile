# I have literally no idea how to write a makefile

# making sure devkitARM exists and is set up
ifeq ($(strip $(DEVKITARM)),)
	$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

# including devkitARM tool definitions
include $(DEVKITARM)/base_tools

TARGET		:=	$(shell basename $(CURDIR))
SRC_DIR		:=	src
LIB_DIR		:= 	lib
OBJ_DIR		:=	obj
INCLUDES	:=	include

ROM_IN 		:= 	rom.gba
ROM_OUT 	:= 	out_$(TARGET).gba
LIB_OUT 	= 	$(LIB_DIR)/lib$(TARGET).a

PREFIX 		:= 	arm-none-eabi
CC			:= 	$(PREFIX)-gcc
LD 			:= 	$(PREFIX)-gcc

AS			:= 	tools/armips.exe

LIBDIRS		:= 	$(DEVKITPRO)/libgba
LIBS		:= 	-lgba
LIBPATHS 	:=  $(foreach dir,$(LIBDIRS),-L$(dir)/lib)

INCLUDE		:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
					$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
					-I$(CURDIR)/$(BUILD)

ARCH   		:= 	-mthumb -mthumb-interwork
CFLAGS 		:= 	$(ARCH) -Os -g -Wall -mtune=arm7tdmi -mcpu=arm7tdmi -fomit-frame-pointer -ffast-math -mlong-calls $(INCLUDE)
LDFLAGS 	:= 	-r -g $(ARCH)
ASFLAGS 	:=  -strequ ROM_IN "$(ROM_IN)" -strequ ROM_OUT "$(ROM_OUT)" -strequ LIB_IN "$(LIB_OUT)" -root $(CURDIR)

ASM_LINK	= 	link.asm

C_FILES		=	$(wildcard $(SRC_DIR)/*.c)
O_FILES		=	$(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(C_FILES))

.PHONY: rom
rom: $(ROM_OUT)

.PHONY: clean
clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIB_DIR)
	rm -f $(ROM_OUT)

# Link and hook final ROM
$(ROM_OUT): $(LIB_OUT) $(ROM_IN) $(ASM_LINK)
	$(AS) $(ASM_LINK) $(ASFLAGS)

# Objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Library
$(LIB_OUT): $(O_FILES) | $(LIB_DIR)
	$(LD) $(LDFLAGS) $(O_FILES) $(LIBPATHS) $(LIBS) -o $(LIB_OUT)

# Folders
$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(LIB_DIR):
	mkdir $(LIB_DIR)

