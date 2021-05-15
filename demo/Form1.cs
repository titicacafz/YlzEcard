using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;

namespace demo
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            IniFile ini = new IniFile(AppDomain.CurrentDomain.BaseDirectory+"hisCommonService.ini");
            txt_addr.Text = ini.IniReadValue("server", "endpoint");
        }

        private void button1_Click(object sender, EventArgs e)
        {            
            byte[] res = new byte[1024*10];            
            byte[] req = Encoding.GetEncoding("gbk").GetBytes(txt_request.Text);

            DllWrapper.ReadCard(req, res);
            
            txt_response.Text = Encoding.GetEncoding("gbk").GetString(res);
        }
    }
}