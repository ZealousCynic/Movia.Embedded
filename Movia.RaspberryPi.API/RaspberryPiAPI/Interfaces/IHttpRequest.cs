using RaspberryPiAPI.Enum;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Interfaces
{

    public interface IHttpRequest
    {
        string URL { get; set; }
        string Body { get; set; }
        HttpType HttpType { get; set; }
        
    }
}
