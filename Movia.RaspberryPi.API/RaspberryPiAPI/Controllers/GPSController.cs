using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text.Json;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RaspberryPiAPI.DTO;
using RaspberryPiAPI.Interfaces;
using RaspberryPiAPI.Threads;

namespace RaspberryPiAPI.Controllers
{
    [ApiController]
    [Route("[controller]")]
    public class GPSController : ControllerBase
    {
        private ThreadHttpService httpService;
        // TODO: Get registration number from redis
        private readonly string registrationNumber = "BJ32621";

        private ThreadHttpService HttpService { get => httpService; set => httpService = value; }

        public GPSController(IHttpService httpService)
        {
            HttpService = (ThreadHttpService)httpService;
        }

        [HttpPut]
        [Route("{longitude}/{latitude}")]
        public IActionResult NewGPSCoordinates(float longitude, float latitude)
        {
            GPS gps = new GPS(longitude,latitude);

            // TODO: set last knowen potisition
            // TODO: make comments


            IHttpRequest request = new HttpRequest();
            request.Body = JsonSerializer.Serialize(gps);
            request.URL = $"http://svendeprove.web-api.eu.ngrok.io/api/v1/runningbusses/{registrationNumber}/gps";
            request.HttpType = Enum.HttpType.POST;

            HttpService.BufferAdd(request);

            //TODO: Do Stuff
            Debug.WriteLine($"longitude: {longitude},   latitude:{latitude}");
            return Ok();
        }
    }
}
