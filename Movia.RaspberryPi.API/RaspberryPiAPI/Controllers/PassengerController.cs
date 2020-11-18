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
    public class PassengerController : ControllerBase
    {
        static int passengerCount = 0;
        private ThreadHttpService httpService;
        private readonly string registrationNumber = "BJ32621";

        private ThreadHttpService HttpService {  get => httpService; set => httpService = value; }

        public PassengerController(IHttpService httpService)
        {
            HttpService = (ThreadHttpService)httpService;
        }

        //API: /passenger
        [HttpGet]
        public IActionResult Get()
        {
            return Content("Passenger Count = " + passengerCount);
        }

        //API: /passenger/increase
        [HttpPut]
        [Route("Increase")]
        public IActionResult PutIncrease()
        {
            passengerCount++;

            try
            {
                SendPassengerCount();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e);
                return BadRequest(e.Message);
            }

            return Ok();
        }

        //API: /passenger/decrease
        [HttpPut]
        [Route("Decrease")]
        public IActionResult PutDecrease()
        {
            passengerCount--;

            try
            {
                SendPassengerCount();
            }
            catch (Exception e)
            {
                Debug.WriteLine(e);
                return BadRequest(e.Message);
            }

            return Ok();
        }

        private void SendPassengerCount()
        {
            Passenger passenger = new Passenger();

            passenger.Total = passengerCount;
            passenger.CreateDT = DateTime.Now;
            // TODO: get last knowen potisition
            // TODO: make comments


            IHttpRequest request = new HttpRequest();
            request.Body = JsonSerializer.Serialize(passenger);
            // get envorment api url
            request.URL = $"http://svendeprove.web-api.eu.ngrok.io/api/v1/runningbusses/{registrationNumber}/currentpassenger";
            request.HttpType = Enum.HttpType.POST;

            HttpService.BufferAdd(request);
        }
    }
}
