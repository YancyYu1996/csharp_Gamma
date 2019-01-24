using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.IO.Ports;
using MyDll;
namespace WindowsFormsApp
{
    public partial class Form1 : Form
    {


        /**********声明CA310的变量*************/
        public static CA200SRVRLib.Ca200 objCa200;
        public static CA200SRVRLib.Ca objCa;
        public static CA200SRVRLib.Probe objProbe;
        public static CA200SRVRLib.Memory objMemory;
        
        public List<short> listX= new List<short>();   //chart的横坐标灰阶。 

        public static DateTime startTime;
        public static Byte[] receivedData = new Byte[11];
        public static byte receivedData_flag = 0;  //接收是否正确的标志
        public static bool ISIPS;  //玻璃的型号
        public static String ICMODE;  //IC的型号
        public Form1()
        {

            InitializeComponent();
            //给USBConnect中的comport挂起中断时间
            usbConnect3.ComPort.DataReceived += new SerialDataReceivedEventHandler(Comm_DataReceived);
          
        }
        /// <summary>
        /// COM口数据的接收（gamma的自动调试）
        /// </summary>
        /// <param name="sender">基类</param>
        /// <param name="e">中断事件</param>
        private void Comm_DataReceived(object sender, EventArgs e)
        {

            this.usbConnect3.Invoke(new EventHandler(delegate

            {
                if (this.usbConnect3.ComPort.IsOpen)     //此处可能没有必要判断是否打开串口
                {
                    receivedData = new Byte[this.usbConnect3.ComPort.BytesToRead];        //创建接收字节数组
                    this.usbConnect3.ComPort.Read(receivedData, 0, receivedData.Length);         //读取数据                    

                    this.usbConnect3.ComPort.DiscardInBuffer();//清空SerialPort控件的Buffer

                    if (receivedData.Length == 11)  //如果接收到的字节为11个，则说明接收成功
                    {
                        receivedData_flag = 1;
                        try
                        {
                            //这是用以显示字符串
                            string strRcv = null;
                            foreach (byte d in receivedData)
                            {
                                if (ReseveStr.Text == "字符串")     //若字符串接收
                                    strRcv +=d;
                                else
                                    strRcv += " "+ Convert.ToString(d, 16);
                            }
                            /*********如果接受的第一个字节为55，最后一个字节为AA,则接收成功*********/
                            if (Convert.ToString(receivedData[0],16) == "55" && Convert.ToString(receivedData[10], 16) == "AA")
                            {
                                receivedData_flag = 1; 
                                usbConnect3.RecieveArea.Text = strRcv;                 //显示信息
                             }                                                   //strRcv + "\r\n";             //显示信息
                        }
                        catch
                        {
                            MessageBox.Show("请打开某个串口", "错误提示");
                        }
                    }
                    else
                    {
                        receivedData_flag = 0;
                    }
                    if (receivedData_flag == 1)  //若接收成功
                    {
                        switch(receivedData[1])   //判断此时的调试模式
                        {
                            case 1: Gamma.Muser_test(usbConnect3);
                   
                                
                                break;       //通信测试

                            case 2: Gamma.AUTO_Flicker( usbConnect3);break;     //自动调试Fliker
                                 
                            case 3: Gamma.AUTO_Gamma(usbConnect3); break;      //自动调试Gamma

                            case 4: Gamma.Muser_Flicker(usbConnect3); break;    //测试Fliker

                            case 5: 
                                if (Gamma.GammaAdjust_Flag == true)
                                {
                                    Gamma.Muser_Gamma(usbConnect3);
                                    GrayNumber.Text = Convert.ToString(Gamma.GetGrayNmuber());
                                    CurtLV.Text = Convert.ToString(Gamma.GetCurreGamma());
                                }
                                break;      //测试Gamma
                            case 6:
                                Gamma.BuildStand(usbConnect3);
                                GrayNumber.Text = Convert.ToString(Gamma.GetGrayNmuber());
                                CurtLV.Text = Convert.ToString(Gamma.GetCurreGamma());
                                if (Gamma.GammaAdjust_Flag == true)
                                {
                                    ZeroGaryLV.Text = Convert.ToString(Gamma.GETBaseGammaArray()[0]);
                                    LastGaryLV.Text = Convert.ToString(Gamma.GETBaseGammaArray()[255]);
                                    for (int j = 0; j <= 255; j++)
                                {
                                    Gamma.GETBaseGammaArray()[j] = 100 * ((j / 255) ^ Convert.ToByte(gamma_ad.Text));
                                }
                                chart1.Series[0].Points.DataBindXY(listX, Gamma.GETBaseGammaArray());
                                }
                                break;

                        }
                    }
                }

            }));



        }


        private void GammaConnect_Click(object sender, EventArgs e)
        {
            try
            { 
                objCa200 = new CA200SRVRLib.Ca200();
                objCa200.AutoConnect(); ;
                objCa = objCa200.SingleCa;
                objProbe = objCa.SingleProbe;
                objMemory = objCa.Memory;
                objCa.DisplayMode = 0;
                GetZero.Enabled = true;
            }
            catch
            {
                MessageBox.Show("检查CA310驱动和连接");
            }

            
            
        }

        private void Button4_Click(object sender, EventArgs e)
        {
            try
            {
                objCa.CalZero(); //校零
            }
            catch
            {
                MessageBox.Show("校零有误，检查CA310");
            }
            
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            chart1.Series[0].XValueMember = "灰阶"; chart1.Series[0].YValueMembers = "实际Gamma亮度";
            chart1.Series[1].XValueMember = "灰阶"; chart1.Series[1].YValueMembers = "标准Gamma亮度";
            for (short i = 0; i <= 255; i++)
            {
                listX.Add(i);
            }
            gamma_ad.Text = Convert.ToString(2.2);

            string[] boliModes = { "IPS","TN"  };
            foreach (string boliMode in boliModes)
            {
                bolichoose.Items.Add(boliMode);
            }
            bolichoose.SelectedIndex = 0;
        }
        public static bool isIPS()
        {
            return ISIPS;
        }
        private void menuStrip1_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
        {

        }

        private void BuildStand_Click(object sender, EventArgs e)
        {
            Gamma.GammaAdjust_Flag = false;
            receivedData[0] = 17;  //11
            receivedData[1] = 05;  //MusrGamma
            receivedData[2] = 00;
            receivedData[3] = 00;
            receivedData[4] = 00;
            receivedData[5] = 00; //gray 0
            receivedData[6] = 01;
            receivedData[7] = 00;
            receivedData[8] = 00;
            receivedData[9] = 00;
            receivedData[10] = 187; //BB
          //  Gamma.BuildStand(usbConnect3);
            //绘制曲线后才可以调试
            MusrGamma.Enabled = true;  
            AutoGamma.Enabled = true; 
        }

        private void MusrGamma_Click(object sender, EventArgs e)
        {

            receivedData[0] = 85;  //11
            receivedData[1] = 05;  //MusrGamma
            receivedData[2] = 00;
            receivedData[3] = 00;
            receivedData[4] = 00;
            receivedData[5] = 01; //gray 1
            receivedData[6] = 00;
            receivedData[7] = 00;
            receivedData[8] = 00;
            receivedData[9] = 00;
            receivedData[10] = 187; //BB
            startTime = DateTime.Now;
            usbConnect3.send(receivedData);
        }

        private void bolichoose_TextChanged(object sender, EventArgs e)
        {
            ISIPS = (bolichoose.Text == "IPS");
        }

        private void AutoGamma_Click(object sender, EventArgs e)
        {
            if (ISIPS == true)
            {
                receivedData[0] = 85;  //55
                receivedData[1] = 03;  //AutoGamma
                receivedData[2] = Gamma.DefIPSValue[1];
                receivedData[3] = 00;
                receivedData[4] = 00;
                receivedData[5] = 04; //gray 4
                receivedData[6] = 00;
                receivedData[7] = 00;
                receivedData[8] = 00;
                receivedData[9] = 00;
                receivedData[10] = 187; //BB
            }
            else
            {
                receivedData[0] = 85;  //55
                receivedData[1] = 03;  //AutoGamma
                receivedData[2] = Gamma.DefTNValue[17];
                receivedData[3] = 00;
                receivedData[4] = 00;
                receivedData[5] = 04; //gray 4
                receivedData[6] = 00;
                receivedData[7] = 00;
                receivedData[8] = 00;
                receivedData[9] = 00;
                receivedData[10] = 187; //BB
            }
            startTime = DateTime.Now;
            usbConnect3.send(receivedData);
        }

        private void toolStripMenuItem2_Click(object sender, EventArgs e)
        {
            ICMode.Text = "9702";
            ICMODE = "9702";
        }

        private void toolStripMenuItem3_Click(object sender, EventArgs e)
        {
            ICMode.Text = "9503";
            ICMODE = "9503";
        }
    }
}
