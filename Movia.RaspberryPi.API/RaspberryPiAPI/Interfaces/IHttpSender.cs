using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Interfaces
{
    public interface IHttpSender
    {
        void SendRequest(IHttpRequest request);
    }
}
