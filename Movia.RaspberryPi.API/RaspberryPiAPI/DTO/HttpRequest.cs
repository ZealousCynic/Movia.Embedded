using RaspberryPiAPI.Enum;
using RaspberryPiAPI.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.DTO
{
    public class HttpRequest : IHttpRequest
    {
        public HttpRequest() { }

        public HttpRequest(string url, string body, HttpType httpType)
        {
            URL = url;
            Body = body;
            HttpType = httpType;
        }

        public string URL { get; set; }
        public string Body { get; set; }
        public HttpType HttpType { get; set; }
    }
}
