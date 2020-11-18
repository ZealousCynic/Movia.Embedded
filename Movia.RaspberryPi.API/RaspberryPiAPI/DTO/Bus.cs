using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Controllers
{
    public class Bus
    {
        public int id { get; set; }
        public string registrationNumber { get; set; }
        public int capacityBoundary { get; set; }
        public int seatingPlace { get; set; }
        public int standingPlace { get; set; }
        public BusModel busModel { get; set; }
    }
}
