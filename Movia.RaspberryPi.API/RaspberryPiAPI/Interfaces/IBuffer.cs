using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Interfaces
{
    public interface IBuffer<T>
    {
        bool BufferAdd(T t);

    }
}
