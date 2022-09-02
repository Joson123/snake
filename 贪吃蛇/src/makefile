TARGET:=main
CC:=arm-linux-gcc

CSRCS := $(wildcard *.c)  
#CSRCS保存了当前目录下的所有.c文件

#CSRCS+= $(wildcard dir/*.c) 
#CSRCS增加了当前目录的子目录dir下的所有.c文件


OBJS:=$(patsubst %.c, %.o, $(CSRCS))
#OBJS保存了当前目录下的所有.c文件对应的.o文件

INC := -I ../inc

#INC += -I ./include
#根据实际的情况增加头文件的搜索路径


#LIBS是保存了实际需要的库的搜索路径和库的名字
#LIBS := -L ../lib -ltest
#LIBS += -L ./libs -l YYY
#按需增加

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(INC) $(LIBS) -lpthread

			
%.o : %.c
	$(CC) -c $^ -o $@	$(INC)

clean:
	rm $(OBJS)
	rm $(TARGET)

#$@	目标文件的完整名称
#$+ 	所有的依赖文件的文件名，以空格隔开，可能会重复包含所依赖的文件
#$^	所有不重复的依赖文件的文件名，以空格隔开
#$<	第一个依赖文件的文件名
#$?	所有比目标文件更 新 的依赖文件