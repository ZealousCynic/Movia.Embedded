using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Controllers
{
    public class GPS
    {
        float longitude;
        float latitude;

        public GPS() { }

        public GPS(float longitude, float latitude)
        {
            Longitude = longitude;
            Latitude = latitude;
        }

        public float Longitude { get => longitude; set => longitude = value; }
        public float Latitude { get => latitude; set => latitude = value; }
    }
}
