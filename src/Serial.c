#include <avr/io.h>
#include <avr/interrupt.h>

#define BUFF_SIZE 32

unsigned char buffer[BUFF_SIZE];
int write_ptr;
int read_ptr;

void uart_write_buff(unsigned char data);

void uart_init(unsigned int baudrate)
{
	cli();

	DDRD |= (1<<PD1);
	
	UBRR0H = (unsigned char)(baudrate>>8);
	UBRR0L = (unsigned char)baudrate;
	
	UCSR0A = (1<<U2X0);
	UCSR0B = (1<<RXEN0)|(1<<RXCIE0)|(1<<TXEN0);		//enable rx and tx
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);	//8 data bits, 2 stop bits
	
	sei();
}

void uart_tx(unsigned char data)
{
	while ( !(UCSR0A & (1<<UDRE0)) );
	UDR0 = data;
}

void uart_tx_str(char* addr)
{
	char c;
	while((c=*addr))
	{
		uart_tx(c);
		addr++;
	}
}

void uart_flush(void)
{
	read_ptr = write_ptr;
}

char uart_available(void)
{
	return !(write_ptr==read_ptr);
}

ISR(USART_RX_vect)
{
	cli();
	uart_write_buff(UDR0);
	sei();
}

unsigned char uart_read_buff(void)
{
	if(write_ptr==read_ptr) { return 0; }
	
	char data = buffer[read_ptr];
	
	read_ptr++;
	if(read_ptr>=BUFF_SIZE)
	{
		read_ptr = 0;
	}
	
	return data;
}

void uart_write_buff(unsigned char data)
{
	buffer[write_ptr] = data;
	
	write_ptr++;
	if(write_ptr>=BUFF_SIZE)
	{
		write_ptr = 0;
	}
	
	if(write_ptr==read_ptr)
	{
		read_ptr++;
		if(read_ptr>=BUFF_SIZE)
		{
			read_ptr = 0;
		}
	}
}
