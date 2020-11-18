using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Controllers
{
    public class BusModel
    {
        public int id { get; set; }
        public string manufacturer { get; set; }
        public string model { get; set; }
        public string length { get; set; }
        public string width { get; set; }
        public string height { get; set; }
        public string powerTrain { get; set; }
    }
}
