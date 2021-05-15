namespace demo
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
            this.label1 = new System.Windows.Forms.Label();
            this.txt_request = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.txt_response = new System.Windows.Forms.TextBox();
            this.button1 = new System.Windows.Forms.Button();
            this.label3 = new System.Windows.Forms.Label();
            this.txt_addr = new System.Windows.Forms.TextBox();
            this.SuspendLayout();
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(73, 127);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(70, 24);
            this.label1.TabIndex = 0;
            this.label1.Text = "请求:";
            // 
            // txt_request
            // 
            this.txt_request.Location = new System.Drawing.Point(77, 181);
            this.txt_request.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txt_request.Multiline = true;
            this.txt_request.Name = "txt_request";
            this.txt_request.Size = new System.Drawing.Size(1308, 321);
            this.txt_request.TabIndex = 1;
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(77, 508);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(82, 24);
            this.label2.TabIndex = 2;
            this.label2.Text = "返回：";
            // 
            // txt_response
            // 
            this.txt_response.Location = new System.Drawing.Point(77, 536);
            this.txt_response.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txt_response.Multiline = true;
            this.txt_response.Name = "txt_response";
            this.txt_response.Size = new System.Drawing.Size(1308, 249);
            this.txt_response.TabIndex = 3;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(77, 815);
            this.button1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(100, 47);
            this.button1.TabIndex = 4;
            this.button1.Text = "请求";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(77, 17);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(154, 24);
            this.label3.TabIndex = 5;
            this.label3.Text = "服务器地址：";
            // 
            // txt_addr
            // 
            this.txt_addr.Location = new System.Drawing.Point(81, 69);
            this.txt_addr.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txt_addr.Name = "txt_addr";
            this.txt_addr.Size = new System.Drawing.Size(1144, 35);
            this.txt_addr.TabIndex = 6;
            this.txt_addr.Text = "http://10.16.110.201:8087/ybhk/medicalCheck";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 24F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1427, 888);
            this.Controls.Add(this.txt_addr);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.txt_response);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.txt_request);
            this.Controls.Add(this.label1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "Form1";
            this.Text = "处方审核";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox txt_request;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txt_response;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txt_addr;
    }
}

