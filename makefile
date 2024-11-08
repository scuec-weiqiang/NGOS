DIR_SOURCE = ./source
DIR_INLCUDE = ./include
DIR_OUT = ./out
TARGET = $(DIR_OUT)/os.elf

#********************************************************************************
#gcc编译选项
CC = riscv64-unknown-elf-gcc
CFLAGS = 	-nostdlib -fno-builtin 		\
			-g -Wall -I$(DIR_INLCUDE) \
		 	-march=rv32g -mabi=ilp32    \


#qemu模拟器
QEMU = qemu-system-riscv32
QFLAGS = -nographic -smp 1 -machine virt -bios none

#gdb
GDB = gdb-multiarch


#********************************************************************************
# SRC_ASM = 	$(DIR_SOURCE)/start.S \
# 			$(DIR_SOURCE)/mem.S \
# 			$(DIR_SOURCE)/switch.S\

SRC_ASM = $(wildcard $(DIR_SOURCE)/*.S)

SRC_C =  $(wildcard $(DIR_SOURCE)/*.c)

OBJ =  $(addprefix $(DIR_OUT)/,$(patsubst %.S,%.o,$(notdir $(SRC_ASM))))
OBJ += $(addprefix $(DIR_OUT)/,$(patsubst %.c,%.o,$(notdir $(SRC_C))))

all : $(DIR_OUT) $(TARGET)

$(DIR_OUT):
	@echo "创建输出目录: ./out"
	mkdir -p $@

$(TARGET):$(OBJ) #目标文件生成可执行文件
	@echo "\033[32m链接中......\033[0m"
	$(CC) $(CFLAGS) -Tos.ld $^ -o $@
	@echo "\033[32m已生成可执行程序:$(TARGET)\033[0m"

$(DIR_OUT)/%.o : $(DIR_SOURCE)/%.c#源文件生成目标文件
	@echo "\033[32m正在编译 $< ：\033[0m"
	$(CC) $(CFLAGS) -o0 -c $< -o $@

$(DIR_OUT)/%.o : $(DIR_SOURCE)/%.S#源文件生成目标文件
	@echo "\033[32m正在编译 $< ：\033[0m"
	$(CC) $(CFLAGS) -o0 -c $< -o $@
#********************************************************************************

.PHONY: clean
clean:
	@echo "正在删除所有输出文件："
	-rm -rf $(DIR_OUT)/*
	@echo "正在删除输出目录："
	-rmdir $(DIR_OUT)
	@echo "删除成功！"


.PHONY:run
run: all
	@${QEMU} -M ? | grep virt >/dev/null || exit
	@echo "\033[32m先按 Ctrl+A 再按 X 退出 QEMU"
	@echo "------------------------------------\033[0m"
	@${QEMU} ${QFLAGS} -kernel $(TARGET)


.PHONY:debug
debug:all	
	@${QEMU} ${QFLAGS} -kernel $(TARGET) -s -S &
	@${GDB}  ${TARGET} -tui -q -x ./gdbinit 
