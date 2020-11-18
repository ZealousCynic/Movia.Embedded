using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Net.Http;
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
    public class DriverController : ControllerBase
    {
        private ThreadHttpService httpService;
        private HttpClient client;
        private readonly string registrationNumber = "BJ32621";

        private ThreadHttpService HttpService { get => httpService; set => httpService = value; }
        internal HttpClient Client { get => client; set => client = value; }

        public DriverController(IHttpService httpService)
        {
            HttpService = (ThreadHttpService)httpService;
            Client = new HttpClient();
        }

        [HttpPut]
        [Route("{driverPersonalNumber}")]
        public IActionResult NewDriver(string driverPersonalNumber)
        {
            Debug.WriteLine($"http://svendeprove.web-api.eu.ngrok.io/api/v1/busdrivers?PersonnelNumber={driverPersonalNumber}");

            try
            {
                // get busdriver id
                var getDriverId = Task.Run(() => Client.GetAsync($"http://svendeprove.web-api.eu.ngrok.io/api/v1/busdrivers?PersonnelNumber={driverPersonalNumber}"));
                getDriverId.Wait();

                var getDriverIdResponce = Task.Run(() => getDriverId.Result.Content.ReadAsStringAsync());
                getDriverIdResponce.Wait();

                Driver[] busDrivers = JsonSerializer.Deserialize<Driver[]>(getDriverIdResponce.Result);

                // get route id
                var getRouteId = Task.Run(() => Client.GetAsync($"http://svendeprove.web-api.eu.ngrok.io/api/v1/runningbusses/{registrationNumber}"));
                getRouteId.Wait();

                var getRouteIdResponce = Task.Run(() => getRouteId.Result.Content.ReadAsStringAsync());
                getRouteIdResponce.Wait();

                RunningBus runningBus = JsonSerializer.Deserialize<RunningBus>(getRouteIdResponce.Result);

                // delete route
                var deleteRoute = Task.Run(() => Client.DeleteAsync($"http://svendeprove.web-api.eu.ngrok.io/api/v1/routes/{runningBus.routeID}/busses/{runningBus.bus.id}"));
                deleteRoute.Wait();

                var deleteRouteResponce = Task.Run(() => deleteRoute.Result.Content.ReadAsStringAsync());
                deleteRouteResponce.Wait();

                Debug.WriteLine(bool.Parse(deleteRouteResponce.Result));
                if (bool.Parse(deleteRouteResponce.Result))
                {
                    
                    IHttpRequest requestSetDriving = new HttpRequest();
                    requestSetDriving.Body = "";
                    requestSetDriving.URL = $"http://svendeprove.web-api.eu.ngrok.io/api/v1/runningbusses/{registrationNumber}/status/1";
                    requestSetDriving.HttpType = Enum.HttpType.POST;

                    Debug.WriteLine(requestSetDriving.URL);

                    HttpService.BufferAdd(requestSetDriving);

                    BusRoute bus = new BusRoute();
                    bus.busDriverID = busDrivers[0].id;
                    bus.busID = runningBus.bus.id;

                    IHttpRequest request = new HttpRequest();
                    request.Body = JsonSerializer.Serialize(bus);
                    request.URL = $"http://svendeprove.web-api.eu.ngrok.io/api/v1/routes/{runningBus.routeID}/busses";

                    Debug.WriteLine(request.URL);

                    HttpService.BufferAdd(request);
                }
            }
            catch (Exception e)
            {
                return BadRequest(e);
            }
            return Ok();
        }
    }
}
