rfcomm_client.c

#include#include#include#include#include#include

int main( int argc, char **argv )

{intfd ;

unsignedchar buff[64] = "hello";char read_buff[128] = {0};intread_n;intwrite_n;

fd= open( "/dev/rfcomm0",O_RDWR);if( fd<0)

printf("open rfcomm0 error\n");while(1)

{#if 0

//printf( "write hello to rfcomm\n" );

write_n = write( fd, buff, 64);if( write_n<0)

printf("write error\n");else if(write_n==0)

printf("write nothing\n");elseprintf("write %d byte\n",write_n );//sleep(1);

#endif

#if 1memset( read_buff,0, sizeof(read_buff) );

read_n= read( fd, read_buff, sizeof(read_buff) );if( read_n > 0)

{

printf("[receive]:%s\n",read_buff );

}

usleep(50000);#endif}

close(fd);

}