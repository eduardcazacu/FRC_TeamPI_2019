var chart = new SmoothieChart({millisPerPixel:18,grid:{verticalSections:8}}),
    canvas = document.getElementById('chart'),
    series = new TimeSeries();


// Add a random value to each line every second
setInterval(function() {
  series.append(new Date().getTime(), Math.random());
}, 500);

// Add to SmoothieChart
chart.addTimeSeries(series);
chart.streamTo(canvas, 500);