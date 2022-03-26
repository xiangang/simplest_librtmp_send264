/**
 * Simplest Librtmp Send 264
 *
 * 雷霄骅，张晖
 * leixiaohua1020@126.com
 * zhanghuicuc@gmail.com
 * 中国传媒大学/数字电视技术
 * Communication University of China / Digital TV Technology
 * http://blog.csdn.net/leixiaohua1020
 *
 * 本程序用于将内存中的H.264数据推送至RTMP流媒体服务器。
 * This program can send local h264 stream to net server as rtmp live stream.
 */

#include <stdio.h>
#include "librtmp_send264.h"
#include <unistd.h>

FILE *fp_send1;
int fd = -1;

//读文件的回调函数
//we use this callback function to read data from buffer
int read_buffer1(unsigned char *buf, int buf_size)
{
	if (!feof(fp_send1))
	{
		int true_size = fread(buf, 1, buf_size, fp_send1);
		printf("!feof read_buffer1 %d\n", true_size);
		return true_size;
	}
	else
	{
		// lseek(fd, 0, SEEK_SET); //移动到以文件的开头偏移0个字节的位置
		// int true_size = fread(buf, 1, buf_size, fp_send1);
		// printf("loop read_buffer1 %d\n", true_size);
		// return true_size;
		return -1;
	}
}

int main(int argc, char *argv[])
{
	fp_send1 = fopen("./resources/cuc_ieschool.h264", "rb");
	fd = fileno(fp_send1);
	const char *eurl = "rtmp://127.0.0.1/live/livestream";
	printf("%s:%d %s --<", __FILE__, __LINE__, __func__);
	printf("%s", eurl);
	printf(">--[end] \n");

	//初始化并连接到服务器
	RTMP264_Connect(eurl);

	printf("%s:%d %s --<", __FILE__, __LINE__, __func__);
	printf(">--[end] \n");
	//发送
	while (1)
	{
		RTMP264_Send(read_buffer1);
		printf("%s:%d %s --<", __FILE__, __LINE__, __func__);
		printf(">--[end] \n");
	}
	printf("%s:%d %s --<", __FILE__, __LINE__, __func__);
	printf(">--[end] \n");
	//断开连接并释放相关资源
	RTMP264_Close();

	printf("%s:%d %s --<", __FILE__, __LINE__, __func__);
	printf(">--[end] \n");
	return 0;
}
