using RaspberryPiAPI.Interfaces;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace RaspberryPiAPI.Threads
{
    public class ThreadHttpService : IHttpService
    {
        private Queue<IHttpRequest> httpBuffer;
        private static readonly int ThreadUpdateTimer = 5000;
        private static object __lockObj = new object();
        private HttpClient client;

        internal Queue<IHttpRequest> HttpBuffer { get => httpBuffer; set => httpBuffer = value; }
        internal HttpClient Client { get => client; set => client = value; }

        public ThreadHttpService()
        {
            HttpBuffer = new Queue<IHttpRequest>();
            Client = new HttpClient();

            Thread thread = new Thread(ThreadStart);
            thread.Name = "Http Sender Thread";
            thread.Priority = ThreadPriority.Normal;
            thread.IsBackground = false;
            thread.Start();
        }

        private void ThreadStart()
        {
            ThreadRun();
        }

        private void ThreadRun()
        {
            while (true)
            {
                lock (__lockObj)
                {
                    try
                    {
                        for (int i = 0; i < HttpBuffer.Count; i++)
                        {
                            IHttpRequest request = HttpBuffer.Dequeue();

                            SendRequest(request);
                        }
                    }
                    catch (Exception e)
                    {
                        Debug.WriteLine(e);
                    }
                }
                Debug.WriteLine("Test run every 5 seconds");
                Thread.Sleep(ThreadUpdateTimer);
            }
        }

        public bool BufferAdd(IHttpRequest t)
        {
            try
            {
                lock (__lockObj)
                {
                    HttpBuffer.Enqueue(t);
                }
                return true;
            }
            catch (Exception e)
            {
                Debug.WriteLine(e);
                return false;
            }
        }

        public void SendRequest(IHttpRequest request)
        {
            switch (request.HttpType)
            {
                case Enum.HttpType.POST:
                    var content = new StringContent(request.Body, Encoding.UTF8, "application/json");
                    
                    var a = Task.Run(() => Client.PostAsync(request.URL, content));

                    a.Wait();
                    break;

                case Enum.HttpType.GET:
                    throw new NotImplementedException();

                case Enum.HttpType.PUT:
                    throw new NotImplementedException();

                case Enum.HttpType.PATCH:
                    throw new NotImplementedException();

                case Enum.HttpType.DELETE:
                    throw new NotImplementedException();

                default:
                    throw new NotImplementedException();
            }
        }
    }
}
