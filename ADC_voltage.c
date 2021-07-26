
#include "io430.h"
unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0����f��16������
#define WCTR BIT3
#define DCTR BIT4
unsigned int temp=0;
unsigned long max,max_s;
int flag=1;

void GPIO_Init()
{

  P4DIR=0xff;//����ܳ�ʼ��
  P4OUT=0;
  P6DIR|=WCTR+DCTR;
  P6OUT&=~(WCTR+DCTR);
  
  P1DIR=0x00;//������ʼ��
  P1IE=BIT4;
  P1IES=BIT4;
  P2DIR=0xff;//LED��ʼ��
  P2SEL|=BIT6;

  
}

void ADC_Init()
{
  /*P6SEL|=0x01;                                    //ѡ��ADCͨ�������ö�ӦIO�ڵĹ���ģʽ
  ADC12CTL0|= ADC12ON + MSC + SHT0_2 + REF2_5V + REFON; //ADC��Դ���ƿ���16��CLK���ڲ���׼2.5V
  ADC12CTL1|= CONSEQ_0; //�Լ���ʱ��Դ
  ADC12MCTL0= SREF_1 + INCH_0;                     //�ο�����λ��ͨ��ѡ��
  ADC12IE|= 0x01;                                 //�ж�����
  ADC12CTL0|= ENC;                           //ʹ��ת����+����ת��*/
  P6SEL|=0x01;                                    //ѡ��ADCͨ�������ö�ӦIO�ڵĹ���ģʽ
  ADC12CTL0|= ADC12ON + MSC + SHT0_2 + REF2_5V + REFON; //ADC��Դ���ƿ���16��CLK���ڲ���׼2.5V
  ADC12CTL1|= SHP + CONSEQ_2 + ADC12SSEL_0; //SMCLK��ʱ��Դ
  ADC12MCTL0= SREF0 + INCH_0;                     //�ο�����λ��ͨ��ѡ��
  ADC12IE|= 0x01;                                 //�ж�����
  ADC12CTL0|= ENC;                                //ʹ��ת����*/
}

void TimerA_Init()//��ʱ����ʼ��
{
  TACTL|=TASSEL_1+ID_2+MC_1+TACLR;//�趨��ʱ����ģʽ
  TACCTL0 |= CCIE;//capture/compare�������ĳ�ʼ��
  TACCR0=32768-1;//����CCR0��ֵ
}

void display()//��ʾ����
{
  unsigned int k,n;
  unsigned int a,b,c;
  if (flag==1)
  { a=max/100;//��λ
  b=(max-a*100)/10;//ʮλ
  c=max-a*100-b*10;//��λ


    n=0x01;//1000 0000
    P4OUT=~n;   //������ʾ��λ������
    P6OUT|=WCTR; //λѡ
    P6OUT&=~WCTR;
    P4OUT=table[a];//��ѡ
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//�ӳ�
        
    n=0x01;//1000 0000
    P4OUT=~n;   //������ʾС����
    P6OUT|=WCTR; //λѡ
    P6OUT&=~WCTR;
    P4OUT=0x80;//��ѡ10000000
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//�ӳ�
        
    n=0x02;//0100 0000
    P4OUT=~n;//������ʾʮλ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//������ʾ��λ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//��λU
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x3E;
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
  }
        else
        {      
  a=max_s/100;//��λ
  b=(max_s-a*100)/10;//ʮλ
  c=max_s-a*100-b*10;//��λ


    n=0x01;//1000 0000
    P4OUT=~n;   //������ʾ��λ������
    P6OUT|=WCTR; //λѡ
    P6OUT&=~WCTR;
    P4OUT=table[a];//��ѡ
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//�ӳ�
        
    n=0x02;//0100 0000
    P4OUT=~n;//������ʾʮλ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//������ʾ��λ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//��λu
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x1c;//0001 1100
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        }
}

/*void display_2()//��ʾ����
{
  unsigned int k,n;
  unsigned int a,b,c;
  a=max_s/100;//��λ
  b=(max_s-a*100)/10;//ʮλ
  c=max_s-a*100-b*10;//��λ


    n=0x01;//1000 0000
    P4OUT=~n;   //������ʾ��λ������
    P6OUT|=WCTR; //λѡ
    P6OUT&=~WCTR;
    P4OUT=table[a];//��ѡ
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//�ӳ�
        
    n=0x02;//0100 0000
    P4OUT=~n;//������ʾʮλ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//������ʾ��λ����
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//��λu
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x1c;//0001 1100
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
    
}*/

#pragma vector = TIMERA0_VECTOR
__interrupt void Timer(void)//������������Զ�����жϱ�־
{
   temp=0;//ÿ��2������һ��
   P2OUT=~P2OUT;//LED��ȡ�����
}

#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void)
{
  ADC12IE= 0x00;//�ж�ʹ�ܹر�
  __enable_interrupt();//���жϴ�
  unsigned long temp1,temp2;
  unsigned int result;
    result=ADC12MEM0;   //��ȡֵ
    if (result>temp)   //�ж��Ƿ������һ��ֵ
      temp=result;
    else temp=temp;
  temp1=(unsigned long)(temp)*250;
  max=temp1/4095;
  temp2=(unsigned long)(temp)*2500;
  max_s=temp2/4095;
   //display();
  /* if(flag==1)
    display();
   else
    display_2();  */
  ADC12IFG=0;
  //ADC12IE|=0x01;
}

#pragma vector = PORT1_VECTOR
__interrupt void P1_ISR(void)
{
  flag=-flag;
  P1IFG=0;
}

int main( void )
{
  // Stop watchdog timer to prevent time out reset
  WDTCTL = WDTPW + WDTHOLD;
  GPIO_Init();
  TimerA_Init();
  ADC_Init();
  __enable_interrupt();//���ж�ʹ��
  ADC12CTL0 |= ADC12SC;
  while(1)
  {
    display();
    ADC12IE|=0x01;
  }
  return 0;
}


