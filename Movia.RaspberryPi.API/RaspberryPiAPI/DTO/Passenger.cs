using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.DTO
{
    public class Passenger
    {
        int total;
        DateTime createDT;
        float longitude;
        float latitude;

        public int Total { get => total; set => total = value; }
        public DateTime CreateDT { get => createDT; set => createDT = value; }
        public float Longitude { get => longitude; set => longitude = value; }
        public float Latitude { get => latitude; set => latitude = value; }

        public Passenger() { }

        public Passenger(int total, DateTime createDT, float longitude, float latitude)
        {
            Total = total;
            CreateDT = createDT;
            Longitude = longitude;
            Latitude = latitude;
        }

    }
}
