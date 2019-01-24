using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.IO.Ports;
namespace MyDll
{
    public partial class USBConnect : UserControl
    {

    
        static int beforeS;
        public USBConnect()
        {
            InitializeComponent();
            timer1.Tick += new EventHandler(timer1_Tick); //给timer挂起事件

            timer1.Enabled = true;//使timer可用

            timer1.Interval = 100; //设置时间间隔，以毫秒为单位
            string[] bounds = { "2400", "4800", "9600", "14400", "19200", "38400", "56000", "57600", "115200" };
            foreach (string bound in bounds)
            {
                BoundBox.Items.Add(bound);
            }
            BoundBox.SelectedIndex = 2;
        }
      

        public void USBConBox_TextChanged(object sender, EventArgs e)
        {

        }
        public void Check_USB_Connect()
        {
            
            string[] t = SerialPort.GetPortNames();

           

            if ((beforeS != t.Length) && (!ComPort.IsOpen))
            {
               
                foreach (string com in t)
                {
                  
                        USBConBox.Items.Add(com);
                              
                }
                
            }
            beforeS = t.Length;

            if (beforeS == 0)    //判断是否找到串口
            {
                USBConBox.Text = "";
                OpenBut.Enabled = false;
                OpenBut.ForeColor = Color.Gray;
                FindS.Text = "无串口";
                FindS.ForeColor = Color.Red;

            }
            else
            {
                USBConBox.Text = t[0];
                OpenBut.Enabled = true;
                OpenBut.ForeColor = Color.Black;
                FindS.Text = "找到串口";
                FindS.ForeColor = Color.Green;
                if (ComPort.IsOpen)  //判断是否连接
                {
                    OpenBut.Text = "关闭串口";
                    ComStause.Text = "串口已经连接";
                    ComStause.ForeColor = Color.Green;
                }
                else
                {

                    OpenBut.Text = "打开串口";
                    ComStause.Text = "串口未连接";
                    ComStause.ForeColor = Color.Red;
                }
            }

            



        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            Check_USB_Connect();
        }

        private void OpenBut_Click(object sender, EventArgs e)
        {
            if (ComPort.IsOpen)
            {
                ComPort.Close();
                
            }
            else
            {
                ComPort.PortName = USBConBox.Text;
                while (!ComPort.IsOpen)
                {
                   
                    ComPort.BaudRate =Convert.ToInt32(BoundBox.Text);
                    ComPort.Open();
                    
                }
               
            }

        }
        public void send(string sendstr) //ID发给stm32函数
        {
      
        byte[] databyte = new Byte[11];
        string ExceptStr,Nomalstr,str3 ="";
            Nomalstr = sendstr;
        Int16 i  = 0;
            try
            {
                ExceptStr = Nomalstr.Replace(" ", "");   //去掉空格

                if (Nomalstr.Length % 2 == 0)                 //判断字符串字节数是否为偶数
                {
                    databyte = new Byte[Nomalstr.Length / 2]; //重新定义数组
                    for (i = 0; i < Nomalstr.Length / 2 - 1; i += 2)
                    {
                        databyte[i] = Convert.ToByte((Nomalstr[i] + Nomalstr[i + 1]));    //'两个字符转换为一个16进制字节
                    }
                    ComPort.Write(databyte, 0, databyte.Length - 1);
                    sendbytes.Text = Convert.ToString(Convert.ToInt32(sendbytes.Text) + databyte.Length);//发送的数据每次加一

                }

            }
            catch (Exception)
            {
                MessageBox.Show("发送有误");
            }
        }

        public void send(byte[] databyte) //ID发给stm32函数
        {

            
            Int16 i = 0;
            try
            {

                if (databyte.Length  == 11)                 //判断字符串字节数是否为偶数
                { 
                    for (i = 0; i < 11; i += 1)
                    {
                        SendArea.Text += Convert.ToString(databyte[i],16);    //'两个字符转换为一个16进制字节
                    }
                    ComPort.Write(databyte, 0, databyte.Length - 1);
                    sendbytes.Text = Convert.ToString(Convert.ToInt32(sendbytes.Text) + 11);//发送的数据每次加一

                }

            }
            catch (Exception)
            {
                MessageBox.Show("发送有误");
            }
        }
        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            
        }

        private void USBConBox_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

      
    }
}
