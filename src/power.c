#include "power.h"

int main(int argc, char *argv[])
{
int file;
char *filename = "/dev/i2c-0";
if ((file = open(filename, O_RDWR)) < 0) {
    perror("Failed to open the i2c bus");
    exit(1);
}
if (ioctl(file,I2C_SLAVE_FORCE,0x34) < 0) {
        printf("Failed to acquire bus access and/or talk to slave.\n");
        exit(1);
    }
if(argc >1)
{
	for(int i=1;i<argc;i++)
	{
		switch(argv[i][0])
		{
		case 'P':
    {
      printREG(file,0);
      printREG(file,1);
      printREG(file,2);

    }
    break;
		default:
		break;
		}
	}
}
else{
  //printing usage
  printf("This is a small tool for working with the AXP209\r\n");
  printf("usage power [command\r\n");
  printf("R[0123] - R followed by register number to print out\r\n");
}
close(file);
}

char readReg(int file,char address)
{
char buffer[1]={0};
buffer[0]=address;
if(i2c_smbus_write_byte(file,address)<0)
{

printf("Error writing the address: %d \r\n",(write(file,buffer,1)));
}
	if(read(file,buffer,1)==1)
		return buffer[0];
	else
	{
	printf("Error reading register\r\n");
	return 0;
	}
}


void printREG(int file,int registerNumber)
{
  char reg = readReg(file,registerNumber);
  printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\r\n");
  printf("Register %d - %s\r\n",registerNumber,registerNames[registerNumber]);
  printf("0x%02x \r\n",reg);//print raw for user info
  for(int i=7;i>=0;i--)
  {
      if(reg && (1<<i))
      {
        //The bit is set so we print out the message for that bit
        printf("%d \t %s",i+1,registerMessagesOn[registerNumber][i]);
      }
      else
      {
          printf("%d \t %s",i+1,registerMessagesOff[registerNumber][i]);
      }
      printf("\r\n");
  }
}
