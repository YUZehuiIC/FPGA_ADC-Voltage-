
#include "io430.h"
unsigned char table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,
0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
//0——f的16个段码
#define WCTR BIT3
#define DCTR BIT4
unsigned int temp=0;
unsigned long max,max_s;
int flag=1;

void GPIO_Init()
{

  P4DIR=0xff;//数码管初始化
  P4OUT=0;
  P6DIR|=WCTR+DCTR;
  P6OUT&=~(WCTR+DCTR);
  
  P1DIR=0x00;//按键初始化
  P1IE=BIT4;
  P1IES=BIT4;
  P2DIR=0xff;//LED初始化
  P2SEL|=BIT6;

  
}

void ADC_Init()
{
  /*P6SEL|=0x01;                                    //选择ADC通道，设置对应IO口的功能模式
  ADC12CTL0|= ADC12ON + MSC + SHT0_2 + REF2_5V + REFON; //ADC电源控制开，16个CLK，内部基准2.5V
  ADC12CTL1|= CONSEQ_0; //自己做时钟源
  ADC12MCTL0= SREF_1 + INCH_0;                     //参考控制位及通道选择
  ADC12IE|= 0x01;                                 //中断允许
  ADC12CTL0|= ENC;                           //使能转换器+开启转换*/
  P6SEL|=0x01;                                    //选择ADC通道，设置对应IO口的功能模式
  ADC12CTL0|= ADC12ON + MSC + SHT0_2 + REF2_5V + REFON; //ADC电源控制开，16个CLK，内部基准2.5V
  ADC12CTL1|= SHP + CONSEQ_2 + ADC12SSEL_0; //SMCLK做时钟源
  ADC12MCTL0= SREF0 + INCH_0;                     //参考控制位及通道选择
  ADC12IE|= 0x01;                                 //中断允许
  ADC12CTL0|= ENC;                                //使能转换器*/
}

void TimerA_Init()//计时器初始化
{
  TACTL|=TASSEL_1+ID_2+MC_1+TACLR;//设定计时器的模式
  TACCTL0 |= CCIE;//capture/compare控制器的初始化
  TACCR0=32768-1;//设置CCR0的值
}

void display()//显示函数
{
  unsigned int k,n;
  unsigned int a,b,c;
  if (flag==1)
  { a=max/100;//百位
  b=(max-a*100)/10;//十位
  c=max-a*100-b*10;//个位


    n=0x01;//1000 0000
    P4OUT=~n;   //以下显示百位的数字
    P6OUT|=WCTR; //位选
    P6OUT&=~WCTR;
    P4OUT=table[a];//段选
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//延迟
        
    n=0x01;//1000 0000
    P4OUT=~n;   //以下显示小数点
    P6OUT|=WCTR; //位选
    P6OUT&=~WCTR;
    P4OUT=0x80;//段选10000000
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//延迟
        
    n=0x02;//0100 0000
    P4OUT=~n;//以下显示十位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//以下显示个位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//单位U
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x3E;
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
  }
        else
        {      
  a=max_s/100;//百位
  b=(max_s-a*100)/10;//十位
  c=max_s-a*100-b*10;//个位


    n=0x01;//1000 0000
    P4OUT=~n;   //以下显示百位的数字
    P6OUT|=WCTR; //位选
    P6OUT&=~WCTR;
    P4OUT=table[a];//段选
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//延迟
        
    n=0x02;//0100 0000
    P4OUT=~n;//以下显示十位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//以下显示个位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//单位u
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x1c;//0001 1100
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        }
}

/*void display_2()//显示函数
{
  unsigned int k,n;
  unsigned int a,b,c;
  a=max_s/100;//百位
  b=(max_s-a*100)/10;//十位
  c=max_s-a*100-b*10;//个位


    n=0x01;//1000 0000
    P4OUT=~n;   //以下显示百位的数字
    P6OUT|=WCTR; //位选
    P6OUT&=~WCTR;
    P4OUT=table[a];//段选
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
    
        for (k=0;k<=150;k++);//延迟
        
    n=0x02;//0100 0000
    P4OUT=~n;//以下显示十位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[b];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;
        for (k=0;k<=150;k++);
        
    n=0x04;//0010 0000
    P4OUT=~n;//以下显示个位数字
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=table[c];
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
        
    n=0x08;//0001 0000
    P4OUT=~n;//单位u
    P6OUT|=WCTR;
    P6OUT&=~WCTR;
    P4OUT=0x1c;//0001 1100
    P6OUT|=DCTR;
    P6OUT&=~DCTR;    
        for (k=0;k<=150;k++);
    
}*/

#pragma vector = TIMERA0_VECTOR
__interrupt void Timer(void)//这个函数可以自动清除中断标志
{
   temp=0;//每隔2秒清零一次
   P2OUT=~P2OUT;//LED灯取反标记
}

#pragma vector=ADC_VECTOR
__interrupt void ADC12ISR(void)
{
  ADC12IE= 0x00;//中断使能关闭
  __enable_interrupt();//总中断打开
  unsigned long temp1,temp2;
  unsigned int result;
    result=ADC12MEM0;   //读取值
    if (result>temp)   //判断是否大于上一个值
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
  __enable_interrupt();//总中断使能
  ADC12CTL0 |= ADC12SC;
  while(1)
  {
    display();
    ADC12IE|=0x01;
  }
  return 0;
}


