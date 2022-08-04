rfcomm_server.c

#include #include#include#include#include

int str2ba(const char *str, bdaddr_t *ba)

{

uint8_t b[6];const char *ptr =str;inti;for (i = 0; i < 6; i++)

{

b[i]= (uint8_t) strtol(ptr, NULL, 16);if (i != 5 && !(ptr = strchr(ptr, ':')))

ptr= ":00:00:00:00:00";

ptr++;

}

}void baswap(bdaddr_t *dst, const bdaddr_t *src)

{

unsignedchar *d = (unsigned char *) dst;const unsigned char *s = (const unsigned char *) src;inti;for (i = 0; i < 6; i++)

d[i]= s[5-i];

}int ba2str(const bdaddr_t *ba, char *str)

{

uint8_t b[6];

baswap((bdaddr_t*) b, ba);return sprintf(str, "%2.2X:%2.2X:%2.2X:%2.2X:%2.2X:%2.2X",

b[0], b[1], b[2], b[3], b[4], b[5]);

}int main(int argc, char **argv)

{struct sockaddr_rc loc_addr = { 0 }, rem_addr = { 0};char buf[1024] = { 0};ints, client, bytes_read;

socklen_t opt= sizeof(rem_addr);char write_buf[1204]="hello world";char flag = 1;char count=0;//allocate socket

s =socket(AF_BLUETOOTH, SOCK_STREAM, BTPROTO_RFCOMM);//bind socket to port 1 of the first available//local bluetooth adapter

loc_addr.rc_family =AF_BLUETOOTH;

loc_addr.rc_bdaddr= *BDADDR_ANY;

loc_addr.rc_channel= (uint8_t) 1;

bind(s, (struct sockaddr *)&loc_addr, sizeof(loc_addr));//put socket into listening mode

listen(s, 1);//accept one connection

client = accept(s, (struct sockaddr *)&rem_addr, &opt);

ba2str(&rem_addr.rc_bdaddr, buf );

fprintf(stderr,"accepted connection from %s\n", buf);while( flag )

{

memset(buf,0, sizeof(buf));#if 0

//read data from the client

bytes_read = read(client, buf, sizeof(buf));if( bytes_read > 0)

{

printf("[rcv]:%s\n", buf);if(!strcmp(buf,"exit"))

{

flag= 0;

}//write( client,write_buf,16 );

}

usleep(5000);#endif

#if 1

//write data to client

strcpy( buf, "abcdefgh");

bytes_read= 9;

write( client,buf,bytes_read );

usleep(50000);#endif}//close connection

close(client);

close(s);return 0;

}