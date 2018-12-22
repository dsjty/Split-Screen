#include <WinSock2.h>
#include <ws2tcpip.h>
#include <time.h>

#pragma comment( lib, "Ws2_32.lib" )

#define NTP_PORT                123               /*NTP专 用端口号字符串*/
#define TIME_PORT               37                /* TIME/UDP端 口号 */
#define NTP_SERVER_IP           "cn.ntp.org.cn"   /*上海授时中心 IP*/
#define NTP_PORT_STR            "123"             /*NTP专用端口号字 符串*/
#define NTPV1                   "NTP/V1"          /*协议及其版本号*/
#define NTPV2                   "NTP/V2"
#define NTPV3                   "NTP/V3"
#define NTPV4                   "NTP/V4"
#define TIME                    "TIME/UDP"

#define NTP_PCK_LEN 48
#define LI 0
#define VN 3
#define MODE 3
#define STRATUM 0
#define POLL 4
#define PREC -6

#define JAN_1970                0x83aa7e80ul /* 1900年～1970年之间的时间秒数 */
#define NTPFRAC(x)              (4294 * (x) + ((1981 * (x)) >> 11))
#define USEC(x)                 (((x) >> 12) - 759 * ((((x) >> 10) + 32768) >> 16))


typedef struct _ntp_time
{
	unsigned int coarse;

	unsigned int fine;

} ntp_time;

struct ntp_packet
{
	unsigned char leap_ver_mode;

	unsigned char startum;

	char poll;

	char precision;

	int root_delay;
	int root_dispersion;
	int reference_identifier;

	ntp_time reference_timestamp;
	ntp_time originage_timestamp;
	ntp_time receive_timestamp;
	ntp_time transmit_timestamp;

};

char protocol[32];
/*构建NTP协议包*/
int construct_packet(char *packet)
{
	char version = 1;

	long tmp_wrd;

	int port;
	time_t timer;
	strcpy_s(protocol, 32, NTPV4);
	/*判断协议版本*/
	if (!strcmp(protocol, NTPV1) || !strcmp(protocol, NTPV2)
		|| !strcmp(protocol, NTPV3) || !strcmp(protocol, NTPV4))
	{
		memset(packet, 0, NTP_PCK_LEN);
		port = NTP_PORT;
		/*设置16字节的包头*/
		version = protocol[5] - 0x30;
		tmp_wrd = htonl((LI << 30) | (version << 27)
			| (MODE << 24) | (STRATUM << 16) | (POLL << 8) | (PREC & 0xff));

		memcpy(packet, &tmp_wrd, sizeof(tmp_wrd));


		/*设置Root Delay、Root Dispersion和Reference Indentifier */
		tmp_wrd = htonl(1 << 16);

		memcpy(&packet[4], &tmp_wrd, sizeof(tmp_wrd));

		memcpy(&packet[8], &tmp_wrd, sizeof(tmp_wrd));

		/*设置Timestamp部分*/
		time(&timer);
		/*设置Transmit Timestamp coarse*/
		tmp_wrd = htonl(JAN_1970 + (long)timer);

		memcpy(&packet[40], &tmp_wrd, sizeof(tmp_wrd));

		/*设置Transmit Timestamp fine*/
		tmp_wrd = htonl((long)NTPFRAC(timer));

		memcpy(&packet[44], &tmp_wrd, sizeof(tmp_wrd));

		return NTP_PCK_LEN;

	}
	else if (!strcmp(protocol, TIME))/* "TIME/UDP" */

	{
		port = TIME_PORT;
		memset(packet, 0, 4);
		return 4;
	}
	return 0;
}

/*获取NTP时间*/
int get_ntp_time(int sk, struct addrinfo *addr, struct ntp_packet *ret_time)
{
	fd_set pending_data;
	struct timeval block_time;
	char data[NTP_PCK_LEN * 8];
	int packet_len, data_len = addr->ai_addrlen, count = 0, result; // i, re;

	if (!(packet_len = construct_packet(data)))
	{
		return 0;
	}

	/*客户端给服务器端发送NTP协议数据包*/
	if ((result = sendto(sk, data,

		packet_len, 0, addr->ai_addr, data_len)) < 0)

	{
		//perror("sendto");
		return 0;
	}

	/*调用select()函数，并设定超时时间为1s*/
	FD_ZERO(&pending_data);
	FD_SET(sk, &pending_data);

	block_time.tv_sec = 10;
	block_time.tv_usec = 0;
	if (select(sk + 1, &pending_data, NULL, NULL, &block_time) > 0)

	{
		/*接收服务器端的信息*/
		if ((count = recvfrom(sk, data,

			NTP_PCK_LEN * 8, 0, addr->ai_addr, &data_len)) < 0)

		{
			//perror("recvfrom");
			return 0;
		}

		if (protocol == TIME)
		{
			memcpy(&ret_time->transmit_timestamp, data, 4);

			return 1;
		}
		else if (count < NTP_PCK_LEN)
		{
			return 0;
		}
		/* 设置接收NTP包的数据结构 */
		ret_time->leap_ver_mode = (unsigned char)ntohl(data[0]);

		ret_time->startum = (unsigned char)ntohl(data[1]);
		ret_time->poll = (char)ntohl(data[2]);
		ret_time->precision = (char)ntohl(data[3]);
		ret_time->root_delay = ntohl(*(int*)&(data[4]));
		ret_time->root_dispersion = ntohl(*(int*)&(data[8]));
		ret_time->reference_identifier = ntohl(*(int*)&(data[12]));
		ret_time->reference_timestamp.coarse = ntohl(*(int*)&(data[16]));
		ret_time->reference_timestamp.fine = ntohl(*(int*)&(data[20]));
		ret_time->originage_timestamp.coarse = ntohl(*(int*)&(data[24]));
		ret_time->originage_timestamp.fine = ntohl(*(int*)&(data[28]));
		ret_time->receive_timestamp.coarse = ntohl(*(int*)&(data[32]));
		ret_time->receive_timestamp.fine = ntohl(*(int*)&(data[36]));
		ret_time->transmit_timestamp.coarse = ntohl(*(int*)&(data[40]));
		ret_time->transmit_timestamp.fine = ntohl(*(int*)&(data[44]));

		return 1;

	} /* end of if select */

	return 0;

}

void InitSocket()
{
	static bool blInit = true;

	if (blInit)
	{
		WSADATA wsa = { 0 };
		WSAStartup(MAKEWORD(2, 2), &wsa);
		blInit = false;
	}
}

int QueryNetTime(PCSTR lpHost, PCSTR lpPort, LPSYSTEMTIME lpSysTime)
{
	if (lpSysTime == NULL) return -1;

	InitSocket();

	int sockfd, rc;
	struct addrinfo hints, *res = NULL;
	struct ntp_packet new_time_packet;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	/*调用getaddrinfo()函数，获取地址信息*/
	rc = getaddrinfo(lpHost, lpPort, &hints, &res);

	if (rc != 0)
	{
		//perror("getaddrinfo");
		return -2;
	}
	/* 创建套接字 */
	sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

	if (sockfd < 0)
	{
		//perror("socket");
		return -3;
	}

	/*调用取得NTP时间的函数*/
	if (get_ntp_time(sockfd, res, &new_time_packet))
	{
		int nRet;
		closesocket(sockfd);

		time_t ntp_time = new_time_packet.transmit_timestamp.coarse - JAN_1970;
		tm tmOut;

		nRet = localtime_s(&tmOut, &ntp_time);

		if (nRet == 0)
		{
			lpSysTime->wYear = tmOut.tm_year + 1900;
			lpSysTime->wMonth = tmOut.tm_mon + 1;
			lpSysTime->wDay = tmOut.tm_mday;
			lpSysTime->wDayOfWeek = tmOut.tm_wday;
			lpSysTime->wHour = tmOut.tm_hour;
			lpSysTime->wMinute = tmOut.tm_min;
			lpSysTime->wSecond = tmOut.tm_sec;
			lpSysTime->wMilliseconds = 0;
		}

		return nRet;
	}

	closesocket(sockfd);
	return -4;
}