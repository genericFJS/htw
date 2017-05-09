using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace prakt8 {
    class BlinkLabel : Label {
        Timer timer = new Timer();


        public BlinkLabel() {
            timer.Interval = 500;
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, EventArgs e) {
            Visible = !Visible;
        }
    }
}
