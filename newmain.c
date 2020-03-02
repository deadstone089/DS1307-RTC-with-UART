

#include <pic.h>
#include<stdint.h>
#define _XTAL_FREQ 20000000

__CONFIG (0X20F2);


void i2c_initialize(unsigned long); 
void i2c_write();
unsigned char i2c_read(uint8_t);
uint8_t ones(uint8_t);
uint8_t tens(uint8_t);

void main(void) {
    TRISC=0X80;
    TRISC3=TRISC4=1;
	TXSTA=0X24;
	RCSTA=0X90;
	SPBRG=129;
    i2c_initialize(100000);
    unsigned char data[7]={0x45,0x59,0x71,0x04,0x05,0x10,0x06};
    //for(int i=0;i<7;i++) i2c_write(i,data[i]);
    i2c_write();
    while(1){
    __delay_ms(200);
    __delay_ms(200);
    __delay_ms(200);
    //TXIF=0;
	//TXREG=i2c_read(0);
    //TXREG='A';
	//while(TXIF==0);
    uint8_t secs=i2c_read(0);
    __delay_ms(50);
    ones(secs);
    __delay_ms(50);
    tens(secs);
    __delay_ms(50);
    TXIF=0;
	TXREG='\n';
	while(TXIF==0);
	}
}

void i2c_initialize(unsigned long feq_K){
    SSPSTAT = 0x80;
    SSPCON=0X28;
    SSPADD = 49;
    
    SEN=1;
    while(SEN == 1);
    
    SSPBUF=0XD0;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X07;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X00;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    PEN=1;
    while(PEN==1);
    
}


void i2c_write(){
    SEN=1;
    while(SEN == 1);
    
    SSPBUF=0XD0;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X00;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X05;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X06;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=0X07;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    PEN=1;
    while(PEN == 1);
    
    
}

unsigned char i2c_read(uint8_t addr){
    unsigned char rec;
    
    SEN=1;
    while(SEN == 1);
    
    SSPBUF=0XD0;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    SSPBUF=addr;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    PEN=1;
    while(PEN==1);
    //RSEN=1;
    //while(RSEN == 1);
    SEN=1;
    while(SEN==1);
    SSPBUF=0XD1;
    while(BF==1);
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    
    RCEN=1;
    //while(RCEN==1);
    while(BF==0);
    rec=SSPBUF;
    while ( (SEN == 1) || (RSEN == 1) || (PEN == 1) || (RCEN == 1) || (R_W == 1) );
    __delay_ms(10);
    ACKDT = 1;            /* Acknowledge data bit, 0 = ACK */
	ACKEN = 1;            /* Ack data enabled */
	while(ACKEN == 1); 
    PEN=1;
    while(PEN==1);
    
     return rec;
}

uint8_t ones(uint8_t hex){
    TXIF=0;
	TXREG=(hex & 0X0F)+48;
	while(TXIF==0);
}

uint8_t tens(uint8_t hex){
    TXIF=0;
	TXREG=(hex>>4)+48;
	while(TXIF==0);
}