const char _index[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.7.1/jquery.min.js"></script>
    <script src="https://code.highcharts.com/highcharts.js"></script>
    <title>DHT 11 Stream</title>
</head>

<body>
    <div style="display: flex; justify-content: center;align-items: center;height: 100vh; flex-direction: column;">
        <div style="display: flex; justify-content: center;align-items: center;   width: 700px;">
            <div style="margin: 20px; border: 1px solid black; width: 350px; text-align: center;">
                Suhu <span class="suhu">00</span>
                <script>
                   
                </script>
            </div>
            <div style="margin: 20px; border: 1px solid black; width: 350px; text-align: center;">
                Kelembapan <span class="kelembapan">00 </span>
                <script>
                  

                </script>
            </div>
        </div>
    

    <div id="chart-temperature" class="container"></div>

    <script>
        var chartT = new Highcharts.Chart({
            chart: { renderTo: 'chart-temperature' },
            title: { text: 'DHT 11 Temperature' },
            series: [{
                showInLegend: false,
                data: []
            }],
            plotOptions: {
                line: {
                    animation: false,
                    dataLabels: { enabled: true }
                },
                series: { color: '#059e8a' }
            },
            xAxis: {
                type: 'datetime',
                dateTimeLabelFormats: { second: '%H:%M:%S' }
            },
            yAxis: {
                title: { text: 'Temperature (Celsius)' }
                //title: { text: 'Temperature (Fahrenheit)' }
            },
            credits: { enabled: false }
        });
        setInterval(function () {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function () {
                if (this.readyState == 4 && this.status == 200) {
                    var x = (new Date()).getTime(),
                        y = parseFloat(this.responseText);
                    //console.log(this.responseText);
                    if (chartT.series[0].data.length > 40) {
                        chartT.series[0].addPoint([x, y], true, true, true);
                    } else {
                        chartT.series[0].addPoint([x, y], true, false, true);
                    }
                }
            };
            xhttp.open("GET", "/suhu", true);
            xhttp.send();
             $.get("suhu", function (data, status) {

                        $(".suhu").text(data);
                    });
  $.get("kelembapan", function (data, status) {
                        $(".kelembapan").text(data);
                    });
        }, 3000);
        
    </script>
    </div>
</body>

</html>
)rawliteral";
