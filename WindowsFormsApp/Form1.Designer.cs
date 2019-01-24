

namespace WindowsFormsApp
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要修改
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.DataVisualization.Charting.ChartArea chartArea4 = new System.Windows.Forms.DataVisualization.Charting.ChartArea();
            System.Windows.Forms.DataVisualization.Charting.Legend legend4 = new System.Windows.Forms.DataVisualization.Charting.Legend();
            System.Windows.Forms.DataVisualization.Charting.Series series7 = new System.Windows.Forms.DataVisualization.Charting.Series();
            System.Windows.Forms.DataVisualization.Charting.Series series8 = new System.Windows.Forms.DataVisualization.Charting.Series();
            this.GammaConnect = new System.Windows.Forms.Button();
            this.GetZero = new System.Windows.Forms.Button();
            this.chart1 = new System.Windows.Forms.DataVisualization.Charting.Chart();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.选项ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.接收数据ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.ReseveStr = new System.Windows.Forms.ToolStripComboBox();
            this.BuildStand = new System.Windows.Forms.Button();
            this.gamma_ad = new System.Windows.Forms.TextBox();
            this.MusrGamma = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.GrayNumber = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.CurtLV = new System.Windows.Forms.TextBox();
            this.ZeroGaryLV = new System.Windows.Forms.TextBox();
            this.LastGaryLV = new System.Windows.Forms.TextBox();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.iC型号ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.玻璃类型ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.bolichoose = new System.Windows.Forms.ToolStripComboBox();
            this.toolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem3 = new System.Windows.Forms.ToolStripMenuItem();
            this.AutoGamma = new System.Windows.Forms.Button();
            this.usbConnect3 = new MyDll.USBConnect();
            this.usbConnect1 = new MyDll.USBConnect();
            this.ICMode = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // GammaConnect
            // 
            this.GammaConnect.Location = new System.Drawing.Point(149, 181);
            this.GammaConnect.Name = "GammaConnect";
            this.GammaConnect.Size = new System.Drawing.Size(85, 42);
            this.GammaConnect.TabIndex = 37;
            this.GammaConnect.Text = "手动连接Gamma";
            this.GammaConnect.UseVisualStyleBackColor = true;
            this.GammaConnect.Click += new System.EventHandler(this.GammaConnect_Click);
            // 
            // GetZero
            // 
            this.GetZero.Enabled = false;
            this.GetZero.Location = new System.Drawing.Point(149, 242);
            this.GetZero.Name = "GetZero";
            this.GetZero.Size = new System.Drawing.Size(84, 42);
            this.GetZero.TabIndex = 38;
            this.GetZero.Text = "校准0";
            this.GetZero.UseVisualStyleBackColor = true;
            this.GetZero.Click += new System.EventHandler(this.Button4_Click);
            // 
            // chart1
            // 
            chartArea4.Name = "ChartArea1";
            this.chart1.ChartAreas.Add(chartArea4);
            legend4.Name = "Legend1";
            this.chart1.Legends.Add(legend4);
            this.chart1.Location = new System.Drawing.Point(446, 28);
            this.chart1.Name = "chart1";
            series7.ChartArea = "ChartArea1";
            series7.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series7.LabelForeColor = System.Drawing.Color.Red;
            series7.Legend = "Legend1";
            series7.Name = "BaseGamma";
            series8.ChartArea = "ChartArea1";
            series8.ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;
            series8.LabelForeColor = System.Drawing.Color.Lime;
            series8.Legend = "Legend1";
            series8.Name = "MuserGamma";
            this.chart1.Series.Add(series7);
            this.chart1.Series.Add(series8);
            this.chart1.Size = new System.Drawing.Size(357, 285);
            this.chart1.TabIndex = 39;
            this.chart1.Text = "chart1";
            // 
            // menuStrip1
            // 
            this.menuStrip1.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.选项ToolStripMenuItem,
            this.iC型号ToolStripMenuItem,
            this.玻璃类型ToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(822, 25);
            this.menuStrip1.TabIndex = 41;
            this.menuStrip1.Text = "menuStrip1";
            this.menuStrip1.ItemClicked += new System.Windows.Forms.ToolStripItemClickedEventHandler(this.menuStrip1_ItemClicked);
            // 
            // 选项ToolStripMenuItem
            // 
            this.选项ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.接收数据ToolStripMenuItem});
            this.选项ToolStripMenuItem.Name = "选项ToolStripMenuItem";
            this.选项ToolStripMenuItem.Size = new System.Drawing.Size(44, 21);
            this.选项ToolStripMenuItem.Text = "选项";
            // 
            // 接收数据ToolStripMenuItem
            // 
            this.接收数据ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.ReseveStr});
            this.接收数据ToolStripMenuItem.Name = "接收数据ToolStripMenuItem";
            this.接收数据ToolStripMenuItem.Size = new System.Drawing.Size(180, 22);
            this.接收数据ToolStripMenuItem.Text = "保存图片";
            // 
            // ReseveStr
            // 
            this.ReseveStr.Name = "ReseveStr";
            this.ReseveStr.Size = new System.Drawing.Size(121, 25);
            // 
            // BuildStand
            // 
            this.BuildStand.Location = new System.Drawing.Point(275, 181);
            this.BuildStand.Name = "BuildStand";
            this.BuildStand.Size = new System.Drawing.Size(85, 42);
            this.BuildStand.TabIndex = 43;
            this.BuildStand.Text = "绘制标准Gamma曲线";
            this.BuildStand.UseVisualStyleBackColor = true;
            this.BuildStand.Click += new System.EventHandler(this.BuildStand_Click);
            // 
            // gamma_ad
            // 
            this.gamma_ad.Location = new System.Drawing.Point(77, 193);
            this.gamma_ad.Name = "gamma_ad";
            this.gamma_ad.Size = new System.Drawing.Size(66, 21);
            this.gamma_ad.TabIndex = 44;
            // 
            // MusrGamma
            // 
            this.MusrGamma.Enabled = false;
            this.MusrGamma.Location = new System.Drawing.Point(275, 242);
            this.MusrGamma.Name = "MusrGamma";
            this.MusrGamma.Size = new System.Drawing.Size(85, 42);
            this.MusrGamma.TabIndex = 45;
            this.MusrGamma.Text = "测量Gamma曲线";
            this.MusrGamma.UseVisualStyleBackColor = true;
            this.MusrGamma.Click += new System.EventHandler(this.MusrGamma_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 196);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(65, 12);
            this.label1.TabIndex = 46;
            this.label1.Text = "Gamma系数:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(30, 235);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(41, 12);
            this.label2.TabIndex = 47;
            this.label2.Text = "灰阶：";
            // 
            // GrayNumber
            // 
            this.GrayNumber.Location = new System.Drawing.Point(77, 232);
            this.GrayNumber.Name = "GrayNumber";
            this.GrayNumber.Size = new System.Drawing.Size(66, 21);
            this.GrayNumber.TabIndex = 48;
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 272);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(59, 12);
            this.label3.TabIndex = 49;
            this.label3.Text = "此时亮度:";
            // 
            // CurtLV
            // 
            this.CurtLV.Location = new System.Drawing.Point(77, 269);
            this.CurtLV.Name = "CurtLV";
            this.CurtLV.Size = new System.Drawing.Size(66, 21);
            this.CurtLV.TabIndex = 50;
            // 
            // ZeroGaryLV
            // 
            this.ZeroGaryLV.Location = new System.Drawing.Point(77, 296);
            this.ZeroGaryLV.Name = "ZeroGaryLV";
            this.ZeroGaryLV.Size = new System.Drawing.Size(66, 21);
            this.ZeroGaryLV.TabIndex = 51;
            // 
            // LastGaryLV
            // 
            this.LastGaryLV.Location = new System.Drawing.Point(77, 323);
            this.LastGaryLV.Name = "LastGaryLV";
            this.LastGaryLV.Size = new System.Drawing.Size(66, 21);
            this.LastGaryLV.TabIndex = 52;
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 301);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(65, 12);
            this.label4.TabIndex = 53;
            this.label4.Text = "0灰阶亮度:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(0, 326);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(77, 12);
            this.label5.TabIndex = 54;
            this.label5.Text = "256灰阶亮度:";
            // 
            // iC型号ToolStripMenuItem
            // 
            this.iC型号ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem2,
            this.toolStripMenuItem3});
            this.iC型号ToolStripMenuItem.Name = "iC型号ToolStripMenuItem";
            this.iC型号ToolStripMenuItem.Size = new System.Drawing.Size(56, 21);
            this.iC型号ToolStripMenuItem.Text = "IC型号";
            // 
            // 玻璃类型ToolStripMenuItem
            // 
            this.玻璃类型ToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.bolichoose});
            this.玻璃类型ToolStripMenuItem.Name = "玻璃类型ToolStripMenuItem";
            this.玻璃类型ToolStripMenuItem.Size = new System.Drawing.Size(68, 21);
            this.玻璃类型ToolStripMenuItem.Text = "玻璃类型";
            // 
            // bolichoose
            // 
            this.bolichoose.Name = "bolichoose";
            this.bolichoose.Size = new System.Drawing.Size(121, 25);
            this.bolichoose.TextChanged += new System.EventHandler(this.bolichoose_TextChanged);
            // 
            // toolStripMenuItem2
            // 
            this.toolStripMenuItem2.Name = "toolStripMenuItem2";
            this.toolStripMenuItem2.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuItem2.Text = "9702";
            this.toolStripMenuItem2.Click += new System.EventHandler(this.toolStripMenuItem2_Click);
            // 
            // toolStripMenuItem3
            // 
            this.toolStripMenuItem3.Name = "toolStripMenuItem3";
            this.toolStripMenuItem3.Size = new System.Drawing.Size(180, 22);
            this.toolStripMenuItem3.Text = "9503";
            this.toolStripMenuItem3.Click += new System.EventHandler(this.toolStripMenuItem3_Click);
            // 
            // AutoGamma
            // 
            this.AutoGamma.Enabled = false;
            this.AutoGamma.Location = new System.Drawing.Point(275, 301);
            this.AutoGamma.Name = "AutoGamma";
            this.AutoGamma.Size = new System.Drawing.Size(85, 42);
            this.AutoGamma.TabIndex = 55;
            this.AutoGamma.Text = "自动Gamma";
            this.AutoGamma.UseVisualStyleBackColor = true;
            this.AutoGamma.Click += new System.EventHandler(this.AutoGamma_Click);
            // 
            // usbConnect3
            // 
            this.usbConnect3.Location = new System.Drawing.Point(12, 28);
            this.usbConnect3.Name = "usbConnect3";
            this.usbConnect3.Size = new System.Drawing.Size(428, 134);
            this.usbConnect3.TabIndex = 42;
            // 
            // usbConnect1
            // 
            this.usbConnect1.Location = new System.Drawing.Point(0, 0);
            this.usbConnect1.Name = "usbConnect1";
            this.usbConnect1.Size = new System.Drawing.Size(210, 134);
            this.usbConnect1.TabIndex = 0;
            // 
            // ICMode
            // 
            this.ICMode.AutoSize = true;
            this.ICMode.Location = new System.Drawing.Point(593, 9);
            this.ICMode.Name = "ICMode";
            this.ICMode.Size = new System.Drawing.Size(41, 12);
            this.ICMode.TabIndex = 56;
            this.ICMode.Text = "IC型号";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.FromArgb(((int)(((byte)(255)))), ((int)(((byte)(255)))), ((int)(((byte)(192)))));
            this.ClientSize = new System.Drawing.Size(822, 391);
            this.Controls.Add(this.ICMode);
            this.Controls.Add(this.AutoGamma);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.LastGaryLV);
            this.Controls.Add(this.ZeroGaryLV);
            this.Controls.Add(this.CurtLV);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.GrayNumber);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.MusrGamma);
            this.Controls.Add(this.gamma_ad);
            this.Controls.Add(this.BuildStand);
            this.Controls.Add(this.usbConnect3);
            this.Controls.Add(this.chart1);
            this.Controls.Add(this.GetZero);
            this.Controls.Add(this.GammaConnect);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.Text = "Form1";
            this.Load += new System.EventHandler(this.Form1_Load);
            ((System.ComponentModel.ISupportInitialize)(this.chart1)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private MyDll.USBConnect usbConnect1;
        private MyDll.USBConnect usbConnect2;
        internal System.Windows.Forms.Button GammaConnect;
        internal System.Windows.Forms.Button GetZero;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem 选项ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 接收数据ToolStripMenuItem;
        private System.Windows.Forms.ToolStripComboBox ReseveStr;
        public MyDll.USBConnect usbConnect3;
        internal System.Windows.Forms.Button BuildStand;
        public System.Windows.Forms.TextBox gamma_ad;
        internal System.Windows.Forms.Button MusrGamma;
        public System.Windows.Forms.DataVisualization.Charting.Chart chart1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        public System.Windows.Forms.TextBox GrayNumber;
        private System.Windows.Forms.Label label3;
        public System.Windows.Forms.TextBox CurtLV;
        public System.Windows.Forms.TextBox ZeroGaryLV;
        public System.Windows.Forms.TextBox LastGaryLV;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.ToolStripMenuItem iC型号ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem3;
        private System.Windows.Forms.ToolStripMenuItem 玻璃类型ToolStripMenuItem;
        public System.Windows.Forms.ToolStripComboBox bolichoose;
        internal System.Windows.Forms.Button AutoGamma;
        private System.Windows.Forms.Label ICMode;
    }
}

