using RaspberryPiAPI.DTO;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Controllers
{
    public class RunningBus
    {
        public int id { get; set; }
        public int routeID { get; set; }
        public Bus bus { get; set; }
        public Driver busDriver { get; set; }
        public int status { get; set; }
        public float longitude { get; set; }
        public float latitude { get; set; }
    }
}
