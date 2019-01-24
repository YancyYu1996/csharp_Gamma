using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using MyDll;
using System.Windows.Forms;
namespace WindowsFormsApp
{

    class Gamma
    {

        /*****声明自动调试Gamma的变量****/
        //声明灰阶的全局变量（需要每次模式切换后清零）
        private static byte GrayNumber;
        //声明当前Gamma值的全局变量
        private static float CurreGamma;
        //声明测量的Gamma数组     GammaLV-gray
        private static byte UP_Flag = new byte ();
        private static double[] MsurGammaValue = new double[256];
        private static double[] BaseGammaValue = new double[256];


        private static double[] MsurLV_Value = new double[256];

        public static bool GammaAdjust_Flag = false;

        //声明一个储存默认值的枚举
        private static byte[] DefValue = new byte[256];
        private static byte[] NeedGray = new byte[19] { 0, 4, 8, 12, 16, 24, 40, 60, 96, 128, 160, 188, 208, 224, 232, 243, 247, 251, 255 };
        public static byte[] DefTNValue = new byte[19] { 0x7F, 0x60, 0x4e, 0x3e, 0x37, 0x29, 0x2c, 0x16, 0x34, 0x38, 0x3a, 0x58, 0x49, 0x55, 0x45, 0x46, 0x39, 0x21, 0x00 };
        public static byte[] DefIPSValue = new byte[19] { 0x00, 0x21, 0x39, 0x46, 0x45, 0x55, 0x49, 0x16, 0x34, 0x58, 0x3a, 0x38, 0x2c, 0x29, 0x37, 0x3e, 0x4e, 0x60, 0x7F };
        //     page1 gray  0     4    8   12   16   24   40   60   96   128  160 188  208  224  232  243  247  251  255
        //TN                    V0    V4   V8  V12  V16  V18  V22  V27  V36  V44  V52  V59  V54  V68  V70  V75  V79  V83  V87
        //U16 F1[20] = { 0xF1, 0x7F, 0x60, 0x4e, 0x3e, 0x37, 0x29, 0x2c, 0x16, 0x34, 0x38, 0x3a, 0x58, 0x49, 0x55, 0x45, 0x46, 0x39, 0x21, 0x00 };
        //U16 F2[20] = { 0xF2, 0x7F, 0x60, 0x4e, 0x3e, 0x37, 0x29, 0x2c, 0x16, 0x34, 0x38, 0x3a, 0x58, 0x49, 0x55, 0x45, 0x46, 0x39, 0x21, 0x00 };
        //ips           V87  V83  V79  V75  V70  V68  V64  V59  V52  V44  V36  V27  V22  V18  V16  V12  V8   V4    V0

        public static short Graynumber
        {
            get { return GrayNumber;}
            set {
                if(value < 256 && value >= 0)
                {
                    GrayNumber = Convert.ToByte(value);
                }

            }
        }
        public static float Curregamma
        {
            get { return CurreGamma; }
            set { CurreGamma = value;}            
        }

        /*********生成标准波形**************/
        public static void BuildStand(USBConnect usbConnect3)       //测试Fliker
        {
            if (GammaAdjust_Flag == false)   //若没有标准曲线
            {
                //先采集0灰阶的GAMMA亮度，以及显示,发送下一灰阶的值
                if (Form1.receivedData[5] == 0)
                {
                   
                    boss(0, GetLV(), 255, usbConnect3);
                }
                else if (Form1.receivedData[5] == 255)
                {
                    Graynumber = 255;    //灰阶为第5个值
                   
                    Curregamma = GetLV();           //当前的gamma值
                    MsurGammaValue[Graynumber] = Curregamma;   //将此时的灰阶此灰阶的gamma值对应
                    
                }
            }
            if (MsurGammaValue[0] != 0 && MsurGammaValue[255] != 0)
            {
                GammaAdjust_Flag = true; //数组255,0都采到样，可以自动开始调试。并且可以绘制出标准曲线
                Form1.receivedData[9] = 01;     //标准曲线模式完成标志位
                Form1.receivedData[5] = 01;     //下个刷第一灰阶
                usbConnect3.send(Form1.receivedData);
                //给上初始值
                if (Form1.isIPS() == true)
                {
                    for (int i = 0; i < 19; i++)
                    {
                        DefValue[NeedGray[i]] = DefIPSValue[i];
                    }

                }
                else
                {
                    for (int i = 0; i < 19; i++)
                    {
                        DefValue[NeedGray[i]] = DefTNValue[i];
                    }

                }
               
                

            }

            

        }
        /*********通信测试**************/
        public static void Muser_test(USBConnect usbConnect3)       //通信测试
        {


        }
        /************自动Fliker**************/
        public static void AUTO_Flicker(USBConnect usbConnect3)       //自动调试Fliker
        {


        }
        /************自动Gamma**************/
        public static void AUTO_Gamma(USBConnect usbConnect3)       //自动调试Gamma
        {
            if (Form1.receivedData[8] == 1)     //'如果寄存器中的值变换
            {
                Form1.receivedData[8] = 0;
            }
            GrayNumber = Form1.receivedData[5];
            if (GrayNumber <= 254)
            {
                Curregamma = GetLV();

                //此时寄存器值下的亮度  放入存亮度值的寄存器 index为寄存器值
                MsurLV_Value[Form1.receivedData[2]] = Curregamma;

                // MsurLV_Value[DefValue[Form1.receivedData[5]]];初始化的默认值的亮度
                if (Form1.isIPS() == true)          //对寄存器的值进行处理
                {
                    //首先判断寻找的方向(如果初始值<标准值)
                    if (MsurLV_Value[DefValue[GrayNumber]] < BaseGammaValue[GrayNumber])
                    {
                        UP_Flag = 1;
                    }
                    else if (MsurLV_Value[DefValue[GrayNumber]] > BaseGammaValue[GrayNumber])
                    {
                        UP_Flag = 0;
                    }
                    else //结束这一灰阶（~ 。 ~）
                    {
                        UP_Flag = 3;
                        Form1.receivedData[8] = 1;  //这是灰阶结束的标志(刷下一灰阶并且值为默认值)
                        boss_Auto(GrayNumber, Curregamma, Convert.ToByte(GrayNumber + 1), DefValue[GrayNumber + 1], usbConnect3);

                    }

                    if (UP_Flag == 1)  //如果应该向上找
                    {
                        UP_Flag = 4;   //方便下一次判断
                        //判断当前值和基准值的区别(如果小 说明还没有找到)
                        if (Curregamma < BaseGammaValue[GrayNumber])
                        {
                            if (Form1.receivedData[2] < 254) //如寄存器的值小于254
                            {
                                Form1.receivedData[2] += 1;
                            }
                            else
                            {
                                MessageBox.Show("遍历完成后，没有找到此灰阶合适值，检查！！！");
                            }


                        }
                        else //说明找到了
                        {
                            Form1.receivedData[8] = 1;  //这是灰阶结束的标志(刷下一灰阶并且值为默认值)
                            boss_Auto(GrayNumber, Curregamma, Convert.ToByte(GrayNumber + 1), DefValue[GrayNumber + 1], usbConnect3);
                        }
                    }
                    else if (UP_Flag == 2)  //如果应该向下找
                    {
                        UP_Flag = 4;   //方便下一次判断
                        //判断当前值和基准值的区别(如果小 说明还没有找到)
                        if (Curregamma > BaseGammaValue[GrayNumber])
                        {
                            if (Form1.receivedData[2] > 0)
                            {
                                Form1.receivedData[2] -= 1;
                            }
                            else
                            {
                                MessageBox.Show("遍历完成后，没有找到此灰阶合适值，检查！！！");
                            }
                        }
                        else //说明找到了
                        {
                            Form1.receivedData[8] = 1;  //这是灰阶结束的标志(刷下一灰阶并且值为默认值)
                            boss_Auto(GrayNumber, Curregamma, Convert.ToByte(GrayNumber + 1), DefValue[GrayNumber + 1], usbConnect3);
                        }


                    }
                    //boss_Auto(GrayNumber, Curregamma, laterGray, byte value, USBConnect usbConnect3)

                }


            }
            else //寻找完毕
            {
                MessageBox.Show("Gamma寻找完毕,总共用时{0}", Convert.ToString(DateTime.Now - Form1.startTime));

            }
        }
        /************测量Filker**************/
        public static void Muser_Flicker(USBConnect usbConnect3)       //测试Fliker
        {


        }
        /************测量Gamma**************/
        public static void Muser_Gamma(USBConnect usbConnect3)       //测试Gamma
        {
            if (Form1.receivedData[8] == 1)     //'如果寄存器中的值变换
            {
                Form1.receivedData[8] = 0;
            }
            if (Form1.receivedData[5] <= 254)
            {
   
                boss(Form1.receivedData[5], GetLV(), Convert.ToByte(Form1.receivedData[5] + 1), usbConnect3);//强制转化为byte类型
            }
            else
            {
                MessageBox.Show("Gamma测试完毕,总共用时{0}",Convert.ToString(DateTime.Now - Form1.startTime));
            }
        }

        //测量并显示Gamma值和灰阶,以及发送下一个需要扫的灰阶的方法 (*****)
        public static void boss(byte Gray , float CurGam, byte laterGray, USBConnect usbConnect3)
        {
            Graynumber = Gray;    //灰阶为第5个值
            Curregamma = CurGam;           //当前的gamma值

            MsurGammaValue[Graynumber] = Curregamma;   //将此时的灰阶此灰阶的gamma值对应
            Form1.receivedData[5] = laterGray;
            

            usbConnect3.send(Form1.receivedData);

        }

        public static void boss_Auto(byte Gray, float CurGam, byte laterGray,byte value, USBConnect usbConnect3)
        {
            Graynumber = Gray;    //灰阶为第5个值
            Curregamma = CurGam;           //当前的gamma值

            MsurGammaValue[Graynumber] = Curregamma;   //将此时的灰阶此灰阶的gamma值对应
            Form1.receivedData[5] = laterGray;
            Form1.receivedData[2] = value;

            usbConnect3.send(Form1.receivedData);

        }


        public static float GetLV()   //从CA310获取亮度的方法
        {
            Form1.objCa.DisplayMode = 0;   //测试亮度
            Form1.objCa.Measure();
            return Form1.objProbe.Lv;
        }

        //返回这些值的方法
        public static short GetGrayNmuber()   
        {
            return Graynumber;
        }
        public static float GetCurreGamma()
        {
            return Curregamma;
        }
        public static double[] GETMsurGammaArray()
        {
            return MsurGammaValue;
        }
        public static double[] GETBaseGammaArray()
        {
            return BaseGammaValue;
        }
        


    }
}
